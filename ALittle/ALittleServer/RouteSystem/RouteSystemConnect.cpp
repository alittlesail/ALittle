
#include "RouteSystem.h"
#include "../ServerSystem/ServerSchedule.h"

#include "Carp/carp_log.hpp"

#include "ConnectClient.h"
#include "ConnectServer.h"
#include "RouteMessage.h"
#include "ConnectMessage.h"
#include "RouteDefine.h"

namespace ALittle
{

void RouteSystem::ConnectRoute(ROUTE_ID route_id, SessionConnection::ConnectRouteCallback callback)
{
	// 检查是否已经连接成功
	CONNECT_KEY connect_key = RouteIdDefine::CalcConnectKey(m_route_id, route_id);
	auto it = m_connect_route_map.find(connect_key);
	if (it != m_connect_route_map.end())
	{
		if (callback) callback(nullptr, it->second);
		return;
	}

	// 如果没有连接成功，那么就进行搜索
	SearchRoute(route_id, std::bind(&RouteSystem::ConnectRouteSearchRouteCallback, this
								, std::placeholders::_1, std::placeholders::_2
								, callback));
}

void RouteSystem::ConnectRouteSearchRouteCallback(const std::string* reason
												, const std::list<ROUTE_ID>& route_id_list
												, SessionConnection::ConnectRouteCallback callback)
{
	// 如果没有搜索到路径，那么就返回失败
	if (reason != nullptr)
	{
		if (callback) callback(reason, SessionConnectionPtr());
		return;
	}

	// 开始连接
	ConnectRoute(route_id_list, callback);
}

void RouteSystem::ConnectRoute(const std::list<ROUTE_ID>& route_id_list, SessionConnection::ConnectRouteCallback callback)
{
	if (!callback)
	{
		CARP_ERROR("callback is null");
		return;
	}

	// 检查列表
	if (route_id_list.size() < 2)
	{
		std::string reason = u8"route_id_list 至少要有两个元素，起始点和终点";
		callback(&reason, SessionConnectionPtr());
		return;
	}

	// 起始点必须是自己
	if (route_id_list.front() != m_route_id)
	{
		std::string reason = u8"route_id_list 起始点必须是自己";
		callback(&reason, SessionConnectionPtr());
		return;
	}

	// 连接key
	CONNECT_KEY connect_key = RouteIdDefine::CalcConnectKey(route_id_list.front(), route_id_list.back());

	// 不能出现重复节点
	std::set<ROUTE_ID> route_id_map;
	for (auto route_it = route_id_list.begin(); route_it != route_id_list.end(); ++route_it)
	{
		if (route_id_map.find(*route_it) != route_id_map.end())
		{
			std::string reason = u8"route_id_list 中出现重复节点 route_id:" + ROUTE2S(*route_it);
			callback(&reason, SessionConnectionPtr());
			return;
		}
		route_id_map.insert(*route_it);
	}

	SessionConnectionPtr connect_info;
	auto connect_it = m_connect_route_map.find(connect_key);
	if (connect_it != m_connect_route_map.end())
	{
		// 如果已经是连接成功了，那么直接返回
		if (connect_it->second->m_status == SessionConnection::Status::SCS_CONNECTED)
		{
			callback(nullptr, connect_it->second);
			return;
		}

		// 如果是正在连接，那么添加回调函数再返回
		if (connect_it->second->m_status == SessionConnection::Status::SCS_CONNECTING)
		{
			connect_it->second->callback_list.push_back(callback);
			return;
		}

		// 获取信息内存
		connect_info = connect_it->second;
	}
	else
	{
		// 没有就创建一个
		connect_info = SessionConnectionPtr(new SessionConnection);
		connect_info->m_connect_key = connect_key;
		m_connect_route_map[connect_key] = connect_info;
	}

	// 设置回调
	connect_info->callback_list.push_back(callback);

	// 设置路径，并且初始下标
	connect_info->m_connect_index = 0;
	connect_info->m_vector_route_path.clear();
	connect_info->m_list_route_path = route_id_list;
	for (auto route_it = route_id_list.begin(); route_it != route_id_list.end(); ++route_it)
		connect_info->m_vector_route_path.push_back(*route_it);

	// 发起连接请求
	QConnectRouteInfo msg;
	msg.connect_index = connect_info->m_connect_index + 1;
	msg.route_path = connect_info->m_vector_route_path;

	// 查找对应的端点
	ROUTE_ID route_id = msg.route_path[msg.connect_index];
	auto endpoint_it = m_endpoint_map.find(route_id);
	if (endpoint_it == m_endpoint_map.end())
	{
		std::vector<SessionConnection::ConnectRouteCallback> callback_list = connect_info->callback_list;
		m_connect_route_map.erase(connect_key);
		
		std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8" 找不到route_id:" + ROUTE2S(route_id);
		for (size_t i = 0; i < callback_list.size(); ++i)
			callback_list[i](&reason, SessionConnectionPtr());
		return;
	}

	// 保存状态
	connect_info->m_status = SessionConnection::Status::SCS_CONNECTING;
	// 保存下一个节点
	connect_info->m_next_endpoint = endpoint_it->second;

	// 向下一个节点发送连接请求
	ConnectEndpoint::RPCCallback ce_callback = std::bind(&RouteSystem::ConnectRouteImplCallback, this
		, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
		, connect_key);
	endpoint_it->second->SendWithCallback(msg, ce_callback);
}

void RouteSystem::ConnectRouteImplCallback(const std::string* reason, int message_id, void* memory, int memroy_size, CONNECT_KEY connect_key)
{
	auto it = m_connect_route_map.find(connect_key);
	if (it == m_connect_route_map.end()) return;

	// 如果本身调用就失败，那么就是调用失败了
	if (reason != nullptr)
	{
		std::vector<SessionConnection::ConnectRouteCallback> callback_list = it->second->callback_list;
		m_connect_route_map.erase(it);
		for (size_t i = 0; i < callback_list.size(); ++i)
			callback_list[i](reason, SessionConnectionPtr());
		return;
	}

	// 检查是否是正确的应答包
	if (message_id != AConnectRouteInfo::GetStaticID())
	{
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8" 应答包不是一个AConnectRouteInfo! message_id:" + std::to_string(message_id);
		CARP_ERROR(tmp);
		std::vector<SessionConnection::ConnectRouteCallback> callback_list = it->second->callback_list;
		m_connect_route_map.erase(it);
		for (size_t i = 0; i < callback_list.size(); ++i)
			callback_list[i](&tmp, SessionConnectionPtr());
		return;
	}

	// 解析应答包
	AConnectRouteInfo msg;
	if (msg.Deserialize(memory, memroy_size) < 0)
	{
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8" AConnectRouteInfo Deserialize 失败!";
		CARP_ERROR(tmp);
		std::vector<SessionConnection::ConnectRouteCallback> callback_list = it->second->callback_list;
		m_connect_route_map.erase(it);
		for (size_t i = 0; i < callback_list.size(); ++i)
			callback_list[i](&tmp, SessionConnectionPtr());
		return;
	}
	
	// 能到这里，说明是连接成功了
	SessionConnectionPtr session = it->second;
	session->m_status = SessionConnection::Status::SCS_CONNECTED;
	for (size_t i = 0; i < session->callback_list.size(); ++i)
		session->callback_list[i](nullptr, session);
	session->callback_list.clear();

	// 调用回调
    HandleConnectNotify(true, session);
}

void RouteSystem::ConnectRouteTransCallback(const std::string* reason, int message_id, void* memory, int memroy_size
											, ConnectEndpointWeakPtr src_endpoint, int src_rpcid, CONNECT_KEY connect_key)
{
	// 如果当前的连接不存在了，那么直接返回
	ConnectEndpointPtr endpoint = src_endpoint.lock();
	if (!endpoint)
	{
		m_connect_route_map.erase(connect_key);
		return;
	}

	// 如果已经断开连接了，那么直接返回
	if (endpoint->IsConnected() == false)
	{
		m_connect_route_map.erase(connect_key);
		return;
	}

	if (reason != nullptr)
	{
		m_connect_route_map.erase(connect_key);
		endpoint->SendError(src_rpcid, *reason);
		return;
	}

	if (message_id != AConnectRouteInfo::GetStaticID())
	{
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8"应答包不是一个AConnectRouteInfo! message_id:" + std::to_string(message_id);
		CARP_ERROR(tmp);
		m_connect_route_map.erase(connect_key);
		endpoint->SendError(src_rpcid, tmp);
		return;
	}

	AConnectRouteInfo msg;
	if (msg.Deserialize(memory, memroy_size) < 0)
	{
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8"AConnectRouteInfo Deserialize 失败!";
		CARP_ERROR(tmp);
		m_connect_route_map.erase(connect_key);
		endpoint->SendError(src_rpcid, tmp);
		return;
	}

	// 检查是否存在
	auto it = m_connect_route_map.find(connect_key);
	if (it == m_connect_route_map.end())
	{
		std::string tmp = "route_id:" + ROUTE2S(m_route_id) + u8" connect_key 不存在:" + CONNECT2S(connect_key);
		CARP_ERROR(tmp);
		endpoint->SendError(src_rpcid, tmp);
		return;
	}

	// 把链接标记为链接成功
	it->second->m_status = SessionConnection::Status::SCS_CONNECTED;
	endpoint->SendResponse(src_rpcid, msg);
}

} // ALittle
