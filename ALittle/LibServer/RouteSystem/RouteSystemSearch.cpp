
#include "RouteSystem.h"
#include "ALittle/LibServer/ServerSystem/ServerSchedule.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"

#include "ConnectClient.h"
#include "ConnectServer.h"
#include "RouteMessage.h"
#include "ConnectMessage.h"
#include "RouteDefine.h"

namespace ALittle
{

void RouteSystem::SearchRoute(ROUTE_ID route_id, SearchRouteCallback callback)
{
	if (!callback)
	{
		ALITTLE_ERROR("callback is null");
		return;
	}
	
	// 如果目标已经在搜索了，直接添加到列表里面，然后返回
	ROUTE_ID search_key = route_id;
	auto search_it = m_search_route_map.find(search_key);
	if (search_it != m_search_route_map.end())
	{
		search_it->second.callback_list.push_back(callback);
		return;
	}
#ifdef SEARCH_ROUTE_LOG
	ALITTLE_INFO(m_route_id << u8" 发起SearchRoute:" << search_key);
#endif // SEARCH_ROUTE_LOG

	// 创建一个搜索
	SearchRouteInfo& info = m_search_route_map[search_key] = SearchRouteInfo();
	info.callback_list.push_back(callback);
	info.route_id = route_id;

	// 添加直连的节点
	for (auto it = m_endpoint_map.begin(); it != m_endpoint_map.end(); ++it)
	{
#ifdef SEARCH_ROUTE_LOG
		ALITTLE_INFO(search_key << u8" SearchRoute添加第一批节点:" << it->second->GetTargetRouteId());
#endif // SEARCH_ROUTE_LOG
		info.AddRoute(it->second->GetTargetRouteId(), true);
	}

	// 启动广度优先搜索
	std::string tmp;
	SearchRouteImpl(search_key, &tmp);
}

void RouteSystem::SearchRouteImpl(ROUTE_ID search_key, const std::string* reason)
{
	auto search_it = m_search_route_map.find(search_key);
	if (search_it == m_search_route_map.end()) return;

	// 如果已经没有节点可以可以检查了，说明没有路径
	if (search_it->second.cur_index >= static_cast<int>(search_it->second.search_path.size()))
	{
#ifdef SEARCH_ROUTE_LOG
		ALITTLE_INFO(search_key << u8" SearchRoute没有节点可以继续搜索了:");
#endif // SEARCH_ROUTE_LOG

		std::string real_reason;
		if (reason != nullptr) real_reason = u8"上一个搜索失败的原因:" + *reason + ", ";
		real_reason += u8"结果:队列已经没有节点可以继续搜索了，找不到通往目标的路径, route_id:" + ROUTE2S(search_it->second.route_id);

		// 先复制一份回调函数，然后从映射表中移除
		std::vector<SearchRouteCallback> callback_list = search_it->second.callback_list;
		m_search_route_map.erase(search_it);

		// 遍历映射表调用回调
		std::list<ROUTE_ID> temp;
		for (size_t i = 0; i < callback_list.size(); ++i)
			callback_list[i](&real_reason, temp);
		return;
	}

	// 取出当前节点
	SearchPathInfo& info = search_it->second.search_path[search_it->second.cur_index];
	// 检查当前节点是否符合条件，如果符合就返回结果
	if (search_it->second.route_id != 0 && search_it->second.route_id == info.route_id)
	{
#ifdef SEARCH_ROUTE_LOG
		ALITTLE_INFO(search_key << u8" SearchRoute找到符合条件的了:");
#endif // SEARCH_ROUTE_LOG

		std::list<ROUTE_ID> temp;
		int cur_index = search_it->second.cur_index;
		while (cur_index >= 0)
		{
			temp.push_front(search_it->second.search_path[cur_index].route_id);
			cur_index = search_it->second.search_path[cur_index].parent_index;
		}

		// 先复制一份回调函数，然后从映射表中移除
		std::vector<SearchRouteCallback> callback_list = search_it->second.callback_list;
		m_search_route_map.erase(search_it);

		// 遍历映射表调用回调
		temp.push_front(m_route_id);	// 把自己添加在列表头，才是完整的路径
		for (size_t i = 0; i < callback_list.size(); ++i)
			callback_list[i](nullptr, temp);
		return;
	}

	// 向对应的终端发起询问请求
	QSearchRouteInfo msg;
	int cur_index = search_it->second.cur_index;
	while (cur_index >= 0)
	{
		msg.route_path.push_front(search_it->second.search_path[cur_index].route_id);
		cur_index = search_it->second.search_path[cur_index].parent_index;
	}

	// 获取第一个节点，然后发送。如果没找到，那么就跳过这个节点
	auto endpoint_it = m_endpoint_map.find(msg.route_path.front());
	if (endpoint_it == m_endpoint_map.end())
	{
#ifdef SEARCH_ROUTE_LOG
		ALITTLE_INFO(search_key << u8" SearchRoute搜索的初始节点找不到了，跳到下一个");
#endif // SEARCH_ROUTE_LOG
		++ search_it->second.cur_index;
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8" 找不到route_id:" + ROUTE2S(msg.route_path.front());
		SearchRouteImpl(search_key, &tmp);
		return;
	}

#ifdef SEARCH_ROUTE_LOG
	ALITTLE_INFO(search_key << u8" SearchRoute发起可靠性请求向" << endpoint_it->second->m_target_route_id
				<< u8", 路径为:" << StringHelper::JoinString(msg.route_path, "->"));
#endif // SEARCH_ROUTE_LOG
	// 开始询问
	ConnectEndpoint::RPCCallback callback = std::bind(&RouteSystem::SearchRouteImplCallback, this
		, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
		, search_key);
	endpoint_it->second->SendWithCallback(msg, callback);
}

void RouteSystem::SearchRouteImplCallback(const std::string* reason, int message_id, void* memory, int memroy_size
										, ROUTE_ID search_key)
{
#ifdef SEARCH_ROUTE_LOG
	ALITTLE_INFO(search_key << u8" SearchRoute收到可靠性应答");
#endif // SEARCH_ROUTE_LOG

	auto it = m_search_route_map.find(search_key);
	if (it == m_search_route_map.end()) return;

	// 如果本身调用就失败，那么就进行下一个节点
	if (reason != nullptr)
	{
		++ it->second.cur_index;
		SearchRouteImpl(search_key, reason);
		return;
	}

	// 检查是否是正确的应答包
	if (message_id != ASearchRouteInfo::GetStaticID())
	{
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8"应答包不是一个ASearchRouteInfo! message_id:" + X2S(message_id);
		ALITTLE_ERROR(tmp);
		++it->second.cur_index;
		SearchRouteImpl(search_key, &tmp);
		return;
	}

	// 解析应答包
	ASearchRouteInfo msg;
	if (msg.Deserialize(memory, memroy_size) < 0)
	{
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8"ASearchRouteInfo Deserialize 失败!";
		ALITTLE_ERROR(tmp);
		++it->second.cur_index;
		SearchRouteImpl(search_key, &tmp);
		return;
	}

	// 把获得到的新节点添加进去
	auto id_list_it = msg.route_id_list.begin();
	while (id_list_it != msg.route_id_list.end())
	{
#ifdef SEARCH_ROUTE_LOG
		ALITTLE_INFO(search_key << u8" SearchRoute新增节点:" << *id_list_it);
#endif // SEARCH_ROUTE_LOG
		it->second.AddRoute(*id_list_it, false);
		++ id_list_it;
	}

	// 执行下一个节点
	++ it->second.cur_index;
	SearchRouteImpl(search_key, reason);
}

void RouteSystem::SearchRouteTransCallback(const std::string* reason, int message_id, void* memory, int memroy_size
										, ConnectEndpointWeakPtr src_endpoint, int src_rpcid)
{
	// 如果当前的连接不存在了，那么直接返回
	ConnectEndpointPtr endpoint = src_endpoint.lock();
	if (!endpoint)
	{
		ALITTLE_SYSTEM(u8"连接已经不存在了");
		return;
	}

	// 如果已经断开连接了，那么直接返回
	if (endpoint->IsConnected() == false)
	{
		ALITTLE_SYSTEM(u8"连接断开了");
		return;
	}

	ASearchRouteInfo msg;
	// 如果可靠性调用失败，那么把原因直接传回去
	if (reason != nullptr)
	{
		endpoint->SendError(src_rpcid, *reason);
		return;
	}

	if (message_id != ASearchRouteInfo::GetStaticID())
	{
		std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8"应答包不是一个ASearchRouteInfo! message_id:" + X2S(message_id);
		ALITTLE_ERROR(reason);
		endpoint->SendError(src_rpcid, reason);
		return;
	}
	if (msg.Deserialize(memory, memroy_size) < 0)
	{
		std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8"ASearchRouteInfo Deserialize 失败!";
		ALITTLE_ERROR(reason);
		endpoint->SendError(src_rpcid, reason);
		return;
	}

	// 把数据包转发出去
	endpoint->SendResponse(src_rpcid, msg);
}

} // ALittle
