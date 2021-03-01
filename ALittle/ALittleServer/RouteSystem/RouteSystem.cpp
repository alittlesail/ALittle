
#include "RouteSystem.h"
#include "SessionConnection.h"
#include "../ServerSystem/ServerSchedule.h"

#include "Carp/carp_log.hpp"

#include "ConnectClient.h"
#include "ConnectServer.h"
#include "RouteMessage.h"
#include "ConnectMessage.h"
#include "RouteDefine.h"

namespace ALittle
{

RouteSystem::RouteSystem()
	: m_route_id(0), m_heartbeat_interval(30), m_reconnect_interval(5), m_schedule(nullptr)
{
}

void RouteSystem::Start(ROUTE_ID route_id, int heartbeat_interval, int reconnect_interval, ServerSchedule* schedule)
{
	m_route_id = route_id;
	m_heartbeat_interval = heartbeat_interval;
	if (m_heartbeat_interval <= 0) m_heartbeat_interval = 30;
	m_reconnect_interval = reconnect_interval;
	if (m_reconnect_interval <= 0) m_reconnect_interval = 5;
	m_schedule = schedule;
}

void RouteSystem::Close()
{
	// 清理节点
	m_endpoint_map.clear();
	// 清理本地创建的客户端连接点
	for (auto it = m_connect_client_map.begin(); it != m_connect_client_map.end(); ++it)
		it->second->Close(u8"RouteSystem:Close调用");
	m_connect_client_map.clear();
	// 清理本地创建的服务端
	for (auto it = m_connect_server_map.begin(); it != m_connect_server_map.end(); ++it)
		it->second->Close();
	m_connect_server_map.clear();
}

// 创建服务端
bool RouteSystem::CreateConnectServer(const std::string& yun_ip, const std::string& ip, unsigned int port)
{
	ConnectServerPtr server = ConnectServerPtr(new ConnectServer);
	bool result = server->Start(m_route_id, yun_ip, ip, port, m_heartbeat_interval, this);
	if (result == false) return false;
	
	std::string key = ip + ":" + std::to_string(port);
	m_connect_server_map[key] = server;
	return true;
}

// 关闭服务端
void RouteSystem::ReleaseConnectServer(const std::string& ip, unsigned int port)
{
	std::string key = ip + ":" + std::to_string(port);
	auto it = m_connect_server_map.find(key);
	if (it == m_connect_server_map.end()) return;

	it->second->Close();
	m_connect_server_map.erase(it);
}

// 创建客户端连接点
bool RouteSystem::CreateConnectClient(const std::string& ip, unsigned int port)
{
	ConnectClientPtr client = ConnectClientPtr(new ConnectClient(this));
	client->Connect(m_route_id, ip, port, m_heartbeat_interval, m_reconnect_interval);
	
	std::string key = ip + ":" + std::to_string(port);
	m_connect_client_map[key] = client;
	
	return true;
}

// 释放客户端连接点
void RouteSystem::ReleaseConnectClient(const std::string& ip, unsigned int port)
{
	std::string key = ip + ":" + std::to_string(port);
	auto it = m_connect_client_map.find(key);
	if (it == m_connect_client_map.end()) return;

	it->second->Close(u8"RouteSystem::ReleaseConnectClient调用");
	m_connect_client_map.erase(it);
}

// 出现新的连接点（当连接点对方发送了合法的route_id才会调用这个）
bool RouteSystem::AddConnectEndpoint(ConnectEndpointPtr endpoint, ROUTE_ID target_route_id)
{
	// 如果已经存在了，那么就返回false
	auto it = m_endpoint_map.find(target_route_id);
	if (it != m_endpoint_map.end()) return it->second == endpoint;

	// 打印一下，表示有新的连接点
	CARP_INFO("cur_route_id:" << ROUTE2S(m_route_id) << " RouteSystem::AddConnectEndpoint route_id:" << ROUTE2S(target_route_id));
	endpoint->m_target_route_id = target_route_id;
	m_endpoint_map[target_route_id] = endpoint;

	return true;
}

// 连接点断开连接
void RouteSystem::RemoveConnectEndpoint(ConnectEndpointPtr endpoint)
{
	// 移除掉连接点
	auto it = m_endpoint_map.find(endpoint->GetTargetRouteId());
	if (it != m_endpoint_map.end() && it->second == endpoint)
	{
		CARP_INFO("RouteSystem::RemoveConnectEndpoint:" << ROUTE2S(endpoint->GetTargetRouteId()));
		m_endpoint_map.erase(it);
	}

	// 检查会话连接，如果已经连接成功，检查一下上下游的连接点，并发送断开连接的消息
	std::list<SessionConnectionPtr> session_list;
	for (auto connect_it = m_connect_route_map.begin(); connect_it != m_connect_route_map.end();)
	{
		// 如果还没连接成功的就跳过，这里不处理时因为正在连接的会话机制自己会处理好
		if (connect_it->second->m_status != SessionConnection::Status::SCS_CONNECTED)
		{
			++ connect_it;
			continue;
		}

		ConnectEndpointPtr pre_endpoint = connect_it->second->m_pre_endpoint.lock();
		ConnectEndpointPtr next_endpoint = connect_it->second->m_next_endpoint.lock();
		// 如果当前断开的连接就是上游连接点，那么就要通知下游连接点断开的消息
		if (pre_endpoint == endpoint)
		{
			// 判断下游连接点存在并且处于连接状态
			if (next_endpoint && next_endpoint->IsConnected())
			{
				ConnectRouteDisconnected msg;
				msg.connect_key = connect_it->first;
				next_endpoint->Send(msg);
			}

			CONNECT_KEY connect_key = RouteIdDefine::CalcConnectKey(connect_it->second->m_vector_route_path.front(), connect_it->second->m_vector_route_path.back());
			ROUTE_ID route_id = 0;
			if (connect_it->second->m_connect_index == 0)
				route_id = connect_it->second->m_vector_route_path.back();
			else if (connect_it->second->m_connect_index + 1 == (int)connect_it->second->m_vector_route_path.size())
				route_id = connect_it->second->m_vector_route_path.front();
			// 移除路由
			SessionConnectionPtr session = connect_it->second;
			connect_it = m_connect_route_map.erase(connect_it);
			if (route_id != 0)
			{
				session->m_status = SessionConnection::Status::SCS_IDLE;
				session_list.push_back(session);
			}
			continue;
		}
		// 如果当前断开的连接就是下游连接点，那么就要通知上游连接点断开的消息
		if (next_endpoint == endpoint)
		{
			if (pre_endpoint && pre_endpoint->IsConnected())
			{
				ConnectRouteDisconnected msg;
				msg.connect_key = connect_it->first;
				pre_endpoint->Send(msg);
			}

			CONNECT_KEY connect_key = RouteIdDefine::CalcConnectKey(connect_it->second->m_vector_route_path.front(), connect_it->second->m_vector_route_path.back());
			ROUTE_ID route_id = 0;
			if (connect_it->second->m_connect_index == 0)
				route_id = connect_it->second->m_vector_route_path.back();
			else if (connect_it->second->m_connect_index + 1 == (int)connect_it->second->m_vector_route_path.size())
				route_id = connect_it->second->m_vector_route_path.front();

			// 移除路由
			SessionConnectionPtr session = connect_it->second;
			connect_it = m_connect_route_map.erase(connect_it);
			if (route_id != 0)
			{
				session->m_status = SessionConnection::Status::SCS_IDLE;
				session_list.push_back(session);
			}
			continue;
		}

		// 检查下一个会话连接
		++ connect_it;
	}

	// 把收集到的session统一在这里调用
	// 避免回调内部间接操作了m_connect_route_map，使正在遍历的迭代器失效
	for (auto it = session_list.begin(); it != session_list.end(); ++it)
        HandleConnectNotify(false, *it);

	// 如果断开的连接点是本地创建的客户端连接点，那么就要重新创建一个
	// 因为当前连接点已经断开连接，这样依赖连接点的流程和数据包会正常结束和终止
	// 重新创建一个之后，新的相关流程会走新创建的对象
	std::string key = endpoint->GetIP() + ":" + std::to_string(endpoint->GetPort());
	auto client_it = m_connect_client_map.find(key);
	if (client_it != m_connect_client_map.end() && client_it->second == endpoint)
	{
		ConnectClientPtr client = ConnectClientPtr(new ConnectClient(this));
		client->Connect(m_route_id, endpoint->GetIP(), endpoint->GetPort(), m_heartbeat_interval, m_reconnect_interval);
		// 替换旧的客户端连接点
		m_connect_client_map[key] = client;
	}
}

void RouteSystem::HandleConnectNotify(bool is_connected, SessionConnectionPtr session)
{
	m_schedule->HandleSessionNotify(is_connected, session);
}

// 处理连接点发来的可靠性请求
void RouteSystem::HandleQConnect2ConnectRPC(ConnectEndpointPtr endpoint, int src_rpcid
	, int message_id, void* message_body, int message_size)
{
	// 处理路由搜索信息
	if (message_id == QSearchRouteInfo::GetStaticID())
	{
		ASearchRouteInfo result_msg;	// 应答包
		QSearchRouteInfo msg;			// 请求包
		if (msg.Deserialize(message_body, message_size) < 0)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QSearchRouteInfo Deserialize 失败!";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path.empty())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QSearchRouteInfo 请求包的route_path是空的!";
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path.front() != m_route_id)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QSearchRouteInfo 请求包的route_path的当前节点不是当前连接点, " + " request_route_id:" + ROUTE2S(msg.route_path.front());
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// 移除掉当前的route_id
		msg.route_path.pop_front();

		// 移除掉后如果路径已经是空的了，说明自己就是目标连接点
		if (msg.route_path.empty())
		{
			// 遍历当前连接点的所有连接对象，排除掉数据包来源连接点
			for (auto it = m_endpoint_map.begin(); it != m_endpoint_map.end(); ++it)
			{
				if (it->second == endpoint) continue;
				result_msg.route_id_list.push_back(it->second->GetTargetRouteId());
			}
			// 然后全部都返回回去
			endpoint->SendResponse(src_rpcid, result_msg);
			return;
		}

		// 如果不是最终节点，那么就寻找下一个节点进行转发
		auto endpoint_it = m_endpoint_map.find(msg.route_path.front());
		if (endpoint_it == m_endpoint_map.end())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8"找不到下一个节点 route_id:" + ROUTE2S(msg.route_path.front());
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// 保存来源连接点，务必要先转成弱引用再bind
		ConnectEndpointWeakPtr src_endpoint = endpoint;
		// 构建一个bind
		ConnectEndpoint::RPCCallback callback = std::bind(&RouteSystem::SearchRouteTransCallback, this
			, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
			, src_endpoint, src_rpcid);
		// 发送确定性请求
		endpoint_it->second->SendWithCallback(msg, callback);
		return;
	}
	
	// 处理会话连接请求
	if (message_id == QConnectRouteInfo::GetStaticID())
	{
		AConnectRouteInfo result_msg;	// 应答包
		QConnectRouteInfo msg;			// 请求包
		if (msg.Deserialize(message_body, message_size) < 0)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QConnectRouteInfo Deserialize 失败!";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path.empty())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QConnectRouteInfo 请求包的route_path是空的!";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.connect_index < 0 || msg.connect_index >= static_cast<int>(msg.route_path.size()))
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8"连接下标超出了route_path的范围了, ";
			reason += "connect_index:" + std::to_string(msg.connect_index) + "route_path's size:" + std::to_string(msg.route_path.size());
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path[msg.connect_index] != m_route_id)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8" QConnectRouteInfo 请求包的route_path的当前节点不是当前连接点, " + " request_route_id:" + std::to_string(msg.route_path[msg.connect_index]);
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// 检查一下，如果当前已经有这个链接了，那么说明路由网络中已经有这条路径，必须拦截
		CONNECT_KEY connect_key = RouteIdDefine::CalcConnectKey(msg.route_path.front(), msg.route_path.back());
		if (m_connect_route_map.find(connect_key) != m_connect_route_map.end())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8" QConnectRouteInfo 请求的路径当前节点已经存在，不可以再请求";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}
		
		// 检查是否已经是最后一个节点了，如果是说明就连接成功了
		if (msg.connect_index + 1 >= static_cast<int>(msg.route_path.size()))
		{
			// 保存路由信息，并且标记链接成功
			SessionConnectionPtr info = SessionConnectionPtr(new SessionConnection);
			m_connect_route_map[connect_key] = info;
			info->m_connect_key = connect_key;
			info->m_connect_index = msg.connect_index;
			info->m_pre_endpoint = endpoint;
			info->m_vector_route_path = msg.route_path;
			for (size_t route_i = 0; route_i < msg.route_path.size(); ++route_i)
				info->m_list_route_path.push_back(msg.route_path[route_i]);
			info->m_status = SessionConnection::Status::SCS_CONNECTED;
			endpoint->SendResponse(src_rpcid, result_msg);
			// 通知本端连接成功
            HandleConnectNotify(true, info);
			return;
		}

		// 如果不是最后一个节点，那么就要查找下一个节点
		auto endpoint_it = m_endpoint_map.find(msg.route_path[static_cast<size_t>(msg.connect_index) + 1]);
		if (endpoint_it == m_endpoint_map.end())
		{
			std::string reason  = "route_id:" + ROUTE2S(m_route_id) + u8" 找不到下一个节点 route_id:" + std::to_string(msg.route_path[static_cast<size_t>(msg.connect_index) + 1]);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// 保存路由信息，并且标记为正在链接
		SessionConnectionPtr info = SessionConnectionPtr(new SessionConnection);
		m_connect_route_map[connect_key] = info;
		info->m_connect_key = connect_key;
		info->m_connect_index = msg.connect_index;		// 保存当前节点所在位置
		info->m_pre_endpoint = endpoint;				// 保存来源节点
		info->m_next_endpoint = endpoint_it->second;	// 保存下一个节点
		info->m_vector_route_path = msg.route_path;	// 保存路径
		for (size_t route_i = 0; route_i < msg.route_path.size(); ++route_i)
			info->m_list_route_path.push_back(msg.route_path[route_i]);
		info->m_status = SessionConnection::Status::SCS_CONNECTING;

		// 保存来源连接点，务必要先转成弱引用再bind
		ConnectEndpointWeakPtr src_endpoint = endpoint;
		++ msg.connect_index;	// 指向下一个节点，然后发送出去
		// 构建bind
		ConnectEndpoint::RPCCallback callback = std::bind(&RouteSystem::ConnectRouteTransCallback, this
			, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
			, src_endpoint, src_rpcid, connect_key);
		endpoint_it->second->SendWithCallback(msg, callback);

		return;
	}

	// 执行到这里说明框架流程有问题
	endpoint->SendError(src_rpcid, "route_id:" + ROUTE2S(m_route_id) + " unknow message_id:" + std::to_string(message_id));
	CARP_ERROR("unknow message_id:" << message_id);
}

void RouteSystem::HandleConnectRouteDisconnected(ConnectEndpointPtr endpoint, const ConnectRouteDisconnected& msg)
{
	// 检查路由是否存在
	auto it = m_connect_route_map.find(msg.connect_key);
	if (it == m_connect_route_map.end()) return;

	// 如果有上游节点，那么就转发这个数据包
	ConnectEndpointPtr pre_endpoint = it->second->m_pre_endpoint.lock();
	if (pre_endpoint && pre_endpoint != endpoint && pre_endpoint->IsConnected())
		pre_endpoint->Send(msg);
	it->second->m_pre_endpoint = ConnectEndpointPtr();

	// 如果有下游节点，那么就转发这个数据包
	ConnectEndpointPtr next_endpoint = it->second->m_next_endpoint.lock();
	if (next_endpoint && next_endpoint != endpoint && next_endpoint->IsConnected())
		next_endpoint->Send(msg);
	it->second->m_next_endpoint = ConnectEndpointPtr();

	// 如果自己是会话连接两端中的一端，那么就调用连接断开的回调
	ROUTE_ID route_id = 0;
	if (it->second->m_vector_route_path.front() == m_route_id)
		route_id = it->second->m_vector_route_path.back();
	else if (it->second->m_vector_route_path.back() == m_route_id)
		route_id = it->second->m_vector_route_path.front();

	// 把状态标记为空闲
	SessionConnectionPtr session = it->second;
	m_connect_route_map.erase(it);
	if (route_id != 0)
	{
		session->m_status = SessionConnection::Status::SCS_IDLE;
        HandleConnectNotify(false, session);
	}
}

void RouteSystem::HandleConnectRouteMessage(ConnectEndpointPtr endpoint, CONNECT_KEY connect_key, int src_rpcid
											, int message_id, int message_rpcid, void* message_body, int message_size
											, void* memory, int memory_size, bool& need_free)
{
	// 查询路径，并判断是不是endpoint自己
	auto it = m_connect_route_map.find(connect_key);
	if (it == m_connect_route_map.end())
	{
		CARP_WARN(u8"unknow connect key 可能是由于数据发送过程中会话连接正好断开了:" << connect_key);
		return;
	}

	// 如果当前不是最终节点，那么就需要转发
	if (it->second->m_connect_index > 0 && it->second->m_connect_index + 1 < (int)it->second->m_vector_route_path.size())
	{
		ConnectEndpointPtr pre_endpoint = it->second->m_pre_endpoint.lock();
		ConnectEndpointPtr next_endpoint = it->second->m_next_endpoint.lock();
		if (pre_endpoint == endpoint)
		{
			if (next_endpoint && next_endpoint->IsConnected())
			{
				need_free = false; // 直接使用内存转发，效率高
				next_endpoint->SendPocket(memory, memory_size);
			}
		}
		else if (next_endpoint == endpoint)
		{
			if (pre_endpoint && pre_endpoint->IsConnected())
			{
				need_free = false; // 直接使用内存转发，效率高
				pre_endpoint->SendPocket(memory, memory_size);
			}
		}
		return;
	}

	m_schedule->HandleSessionMessage(connect_key, message_id, message_rpcid, message_body, message_size);
}

bool RouteSystem::CloseConnect(SessionConnectionPtr session)
{
	if (!session) return true;
	if (!session->Close()) return false;
	m_connect_route_map.erase(session->GetConnectKey());
	return true;
}

} // ALittle
