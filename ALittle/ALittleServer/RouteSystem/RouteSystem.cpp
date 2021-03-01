
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
	// ����ڵ�
	m_endpoint_map.clear();
	// �����ش����Ŀͻ������ӵ�
	for (auto it = m_connect_client_map.begin(); it != m_connect_client_map.end(); ++it)
		it->second->Close(u8"RouteSystem:Close����");
	m_connect_client_map.clear();
	// �����ش����ķ����
	for (auto it = m_connect_server_map.begin(); it != m_connect_server_map.end(); ++it)
		it->second->Close();
	m_connect_server_map.clear();
}

// ���������
bool RouteSystem::CreateConnectServer(const std::string& yun_ip, const std::string& ip, unsigned int port)
{
	ConnectServerPtr server = ConnectServerPtr(new ConnectServer);
	bool result = server->Start(m_route_id, yun_ip, ip, port, m_heartbeat_interval, this);
	if (result == false) return false;
	
	std::string key = ip + ":" + std::to_string(port);
	m_connect_server_map[key] = server;
	return true;
}

// �رշ����
void RouteSystem::ReleaseConnectServer(const std::string& ip, unsigned int port)
{
	std::string key = ip + ":" + std::to_string(port);
	auto it = m_connect_server_map.find(key);
	if (it == m_connect_server_map.end()) return;

	it->second->Close();
	m_connect_server_map.erase(it);
}

// �����ͻ������ӵ�
bool RouteSystem::CreateConnectClient(const std::string& ip, unsigned int port)
{
	ConnectClientPtr client = ConnectClientPtr(new ConnectClient(this));
	client->Connect(m_route_id, ip, port, m_heartbeat_interval, m_reconnect_interval);
	
	std::string key = ip + ":" + std::to_string(port);
	m_connect_client_map[key] = client;
	
	return true;
}

// �ͷſͻ������ӵ�
void RouteSystem::ReleaseConnectClient(const std::string& ip, unsigned int port)
{
	std::string key = ip + ":" + std::to_string(port);
	auto it = m_connect_client_map.find(key);
	if (it == m_connect_client_map.end()) return;

	it->second->Close(u8"RouteSystem::ReleaseConnectClient����");
	m_connect_client_map.erase(it);
}

// �����µ����ӵ㣨�����ӵ�Է������˺Ϸ���route_id�Ż���������
bool RouteSystem::AddConnectEndpoint(ConnectEndpointPtr endpoint, ROUTE_ID target_route_id)
{
	// ����Ѿ������ˣ���ô�ͷ���false
	auto it = m_endpoint_map.find(target_route_id);
	if (it != m_endpoint_map.end()) return it->second == endpoint;

	// ��ӡһ�£���ʾ���µ����ӵ�
	CARP_INFO("cur_route_id:" << ROUTE2S(m_route_id) << " RouteSystem::AddConnectEndpoint route_id:" << ROUTE2S(target_route_id));
	endpoint->m_target_route_id = target_route_id;
	m_endpoint_map[target_route_id] = endpoint;

	return true;
}

// ���ӵ�Ͽ�����
void RouteSystem::RemoveConnectEndpoint(ConnectEndpointPtr endpoint)
{
	// �Ƴ������ӵ�
	auto it = m_endpoint_map.find(endpoint->GetTargetRouteId());
	if (it != m_endpoint_map.end() && it->second == endpoint)
	{
		CARP_INFO("RouteSystem::RemoveConnectEndpoint:" << ROUTE2S(endpoint->GetTargetRouteId()));
		m_endpoint_map.erase(it);
	}

	// ���Ự���ӣ�����Ѿ����ӳɹ������һ�������ε����ӵ㣬�����ͶϿ����ӵ���Ϣ
	std::list<SessionConnectionPtr> session_list;
	for (auto connect_it = m_connect_route_map.begin(); connect_it != m_connect_route_map.end();)
	{
		// �����û���ӳɹ��ľ����������ﲻ����ʱ��Ϊ�������ӵĻỰ�����Լ��ᴦ���
		if (connect_it->second->m_status != SessionConnection::Status::SCS_CONNECTED)
		{
			++ connect_it;
			continue;
		}

		ConnectEndpointPtr pre_endpoint = connect_it->second->m_pre_endpoint.lock();
		ConnectEndpointPtr next_endpoint = connect_it->second->m_next_endpoint.lock();
		// �����ǰ�Ͽ������Ӿ����������ӵ㣬��ô��Ҫ֪ͨ�������ӵ�Ͽ�����Ϣ
		if (pre_endpoint == endpoint)
		{
			// �ж��������ӵ���ڲ��Ҵ�������״̬
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
			// �Ƴ�·��
			SessionConnectionPtr session = connect_it->second;
			connect_it = m_connect_route_map.erase(connect_it);
			if (route_id != 0)
			{
				session->m_status = SessionConnection::Status::SCS_IDLE;
				session_list.push_back(session);
			}
			continue;
		}
		// �����ǰ�Ͽ������Ӿ����������ӵ㣬��ô��Ҫ֪ͨ�������ӵ�Ͽ�����Ϣ
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

			// �Ƴ�·��
			SessionConnectionPtr session = connect_it->second;
			connect_it = m_connect_route_map.erase(connect_it);
			if (route_id != 0)
			{
				session->m_status = SessionConnection::Status::SCS_IDLE;
				session_list.push_back(session);
			}
			continue;
		}

		// �����һ���Ự����
		++ connect_it;
	}

	// ���ռ�����sessionͳһ���������
	// ����ص��ڲ���Ӳ�����m_connect_route_map��ʹ���ڱ����ĵ�����ʧЧ
	for (auto it = session_list.begin(); it != session_list.end(); ++it)
        HandleConnectNotify(false, *it);

	// ����Ͽ������ӵ��Ǳ��ش����Ŀͻ������ӵ㣬��ô��Ҫ���´���һ��
	// ��Ϊ��ǰ���ӵ��Ѿ��Ͽ����ӣ������������ӵ�����̺����ݰ���������������ֹ
	// ���´���һ��֮���µ�������̻����´����Ķ���
	std::string key = endpoint->GetIP() + ":" + std::to_string(endpoint->GetPort());
	auto client_it = m_connect_client_map.find(key);
	if (client_it != m_connect_client_map.end() && client_it->second == endpoint)
	{
		ConnectClientPtr client = ConnectClientPtr(new ConnectClient(this));
		client->Connect(m_route_id, endpoint->GetIP(), endpoint->GetPort(), m_heartbeat_interval, m_reconnect_interval);
		// �滻�ɵĿͻ������ӵ�
		m_connect_client_map[key] = client;
	}
}

void RouteSystem::HandleConnectNotify(bool is_connected, SessionConnectionPtr session)
{
	m_schedule->HandleSessionNotify(is_connected, session);
}

// �������ӵ㷢���Ŀɿ�������
void RouteSystem::HandleQConnect2ConnectRPC(ConnectEndpointPtr endpoint, int src_rpcid
	, int message_id, void* message_body, int message_size)
{
	// ����·��������Ϣ
	if (message_id == QSearchRouteInfo::GetStaticID())
	{
		ASearchRouteInfo result_msg;	// Ӧ���
		QSearchRouteInfo msg;			// �����
		if (msg.Deserialize(message_body, message_size) < 0)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QSearchRouteInfo Deserialize ʧ��!";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path.empty())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QSearchRouteInfo �������route_path�ǿյ�!";
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path.front() != m_route_id)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QSearchRouteInfo �������route_path�ĵ�ǰ�ڵ㲻�ǵ�ǰ���ӵ�, " + " request_route_id:" + ROUTE2S(msg.route_path.front());
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// �Ƴ�����ǰ��route_id
		msg.route_path.pop_front();

		// �Ƴ��������·���Ѿ��ǿյ��ˣ�˵���Լ�����Ŀ�����ӵ�
		if (msg.route_path.empty())
		{
			// ������ǰ���ӵ���������Ӷ����ų������ݰ���Դ���ӵ�
			for (auto it = m_endpoint_map.begin(); it != m_endpoint_map.end(); ++it)
			{
				if (it->second == endpoint) continue;
				result_msg.route_id_list.push_back(it->second->GetTargetRouteId());
			}
			// Ȼ��ȫ�������ػ�ȥ
			endpoint->SendResponse(src_rpcid, result_msg);
			return;
		}

		// ����������սڵ㣬��ô��Ѱ����һ���ڵ����ת��
		auto endpoint_it = m_endpoint_map.find(msg.route_path.front());
		if (endpoint_it == m_endpoint_map.end())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8"�Ҳ�����һ���ڵ� route_id:" + ROUTE2S(msg.route_path.front());
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// ������Դ���ӵ㣬���Ҫ��ת����������bind
		ConnectEndpointWeakPtr src_endpoint = endpoint;
		// ����һ��bind
		ConnectEndpoint::RPCCallback callback = std::bind(&RouteSystem::SearchRouteTransCallback, this
			, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
			, src_endpoint, src_rpcid);
		// ����ȷ��������
		endpoint_it->second->SendWithCallback(msg, callback);
		return;
	}
	
	// ����Ự��������
	if (message_id == QConnectRouteInfo::GetStaticID())
	{
		AConnectRouteInfo result_msg;	// Ӧ���
		QConnectRouteInfo msg;			// �����
		if (msg.Deserialize(message_body, message_size) < 0)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QConnectRouteInfo Deserialize ʧ��!";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path.empty())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8":QConnectRouteInfo �������route_path�ǿյ�!";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.connect_index < 0 || msg.connect_index >= static_cast<int>(msg.route_path.size()))
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8"�����±곬����route_path�ķ�Χ��, ";
			reason += "connect_index:" + std::to_string(msg.connect_index) + "route_path's size:" + std::to_string(msg.route_path.size());
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		if (msg.route_path[msg.connect_index] != m_route_id)
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8" QConnectRouteInfo �������route_path�ĵ�ǰ�ڵ㲻�ǵ�ǰ���ӵ�, " + " request_route_id:" + std::to_string(msg.route_path[msg.connect_index]);
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// ���һ�£������ǰ�Ѿ�����������ˣ���ô˵��·���������Ѿ�������·������������
		CONNECT_KEY connect_key = RouteIdDefine::CalcConnectKey(msg.route_path.front(), msg.route_path.back());
		if (m_connect_route_map.find(connect_key) != m_connect_route_map.end())
		{
			std::string reason = "route_id:" + ROUTE2S(m_route_id) + u8" QConnectRouteInfo �����·����ǰ�ڵ��Ѿ����ڣ�������������";
			CARP_ERROR(reason);
			endpoint->SendError(src_rpcid, reason);
			return;
		}
		
		// ����Ƿ��Ѿ������һ���ڵ��ˣ������˵�������ӳɹ���
		if (msg.connect_index + 1 >= static_cast<int>(msg.route_path.size()))
		{
			// ����·����Ϣ�����ұ�����ӳɹ�
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
			// ֪ͨ�������ӳɹ�
            HandleConnectNotify(true, info);
			return;
		}

		// ����������һ���ڵ㣬��ô��Ҫ������һ���ڵ�
		auto endpoint_it = m_endpoint_map.find(msg.route_path[static_cast<size_t>(msg.connect_index) + 1]);
		if (endpoint_it == m_endpoint_map.end())
		{
			std::string reason  = "route_id:" + ROUTE2S(m_route_id) + u8" �Ҳ�����һ���ڵ� route_id:" + std::to_string(msg.route_path[static_cast<size_t>(msg.connect_index) + 1]);
			endpoint->SendError(src_rpcid, reason);
			return;
		}

		// ����·����Ϣ�����ұ��Ϊ��������
		SessionConnectionPtr info = SessionConnectionPtr(new SessionConnection);
		m_connect_route_map[connect_key] = info;
		info->m_connect_key = connect_key;
		info->m_connect_index = msg.connect_index;		// ���浱ǰ�ڵ�����λ��
		info->m_pre_endpoint = endpoint;				// ������Դ�ڵ�
		info->m_next_endpoint = endpoint_it->second;	// ������һ���ڵ�
		info->m_vector_route_path = msg.route_path;	// ����·��
		for (size_t route_i = 0; route_i < msg.route_path.size(); ++route_i)
			info->m_list_route_path.push_back(msg.route_path[route_i]);
		info->m_status = SessionConnection::Status::SCS_CONNECTING;

		// ������Դ���ӵ㣬���Ҫ��ת����������bind
		ConnectEndpointWeakPtr src_endpoint = endpoint;
		++ msg.connect_index;	// ָ����һ���ڵ㣬Ȼ���ͳ�ȥ
		// ����bind
		ConnectEndpoint::RPCCallback callback = std::bind(&RouteSystem::ConnectRouteTransCallback, this
			, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
			, src_endpoint, src_rpcid, connect_key);
		endpoint_it->second->SendWithCallback(msg, callback);

		return;
	}

	// ִ�е�����˵���������������
	endpoint->SendError(src_rpcid, "route_id:" + ROUTE2S(m_route_id) + " unknow message_id:" + std::to_string(message_id));
	CARP_ERROR("unknow message_id:" << message_id);
}

void RouteSystem::HandleConnectRouteDisconnected(ConnectEndpointPtr endpoint, const ConnectRouteDisconnected& msg)
{
	// ���·���Ƿ����
	auto it = m_connect_route_map.find(msg.connect_key);
	if (it == m_connect_route_map.end()) return;

	// ��������νڵ㣬��ô��ת��������ݰ�
	ConnectEndpointPtr pre_endpoint = it->second->m_pre_endpoint.lock();
	if (pre_endpoint && pre_endpoint != endpoint && pre_endpoint->IsConnected())
		pre_endpoint->Send(msg);
	it->second->m_pre_endpoint = ConnectEndpointPtr();

	// ��������νڵ㣬��ô��ת��������ݰ�
	ConnectEndpointPtr next_endpoint = it->second->m_next_endpoint.lock();
	if (next_endpoint && next_endpoint != endpoint && next_endpoint->IsConnected())
		next_endpoint->Send(msg);
	it->second->m_next_endpoint = ConnectEndpointPtr();

	// ����Լ��ǻỰ���������е�һ�ˣ���ô�͵������ӶϿ��Ļص�
	ROUTE_ID route_id = 0;
	if (it->second->m_vector_route_path.front() == m_route_id)
		route_id = it->second->m_vector_route_path.back();
	else if (it->second->m_vector_route_path.back() == m_route_id)
		route_id = it->second->m_vector_route_path.front();

	// ��״̬���Ϊ����
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
	// ��ѯ·�������ж��ǲ���endpoint�Լ�
	auto it = m_connect_route_map.find(connect_key);
	if (it == m_connect_route_map.end())
	{
		CARP_WARN(u8"unknow connect key �������������ݷ��͹����лỰ�������öϿ���:" << connect_key);
		return;
	}

	// �����ǰ�������սڵ㣬��ô����Ҫת��
	if (it->second->m_connect_index > 0 && it->second->m_connect_index + 1 < (int)it->second->m_vector_route_path.size())
	{
		ConnectEndpointPtr pre_endpoint = it->second->m_pre_endpoint.lock();
		ConnectEndpointPtr next_endpoint = it->second->m_next_endpoint.lock();
		if (pre_endpoint == endpoint)
		{
			if (next_endpoint && next_endpoint->IsConnected())
			{
				need_free = false; // ֱ��ʹ���ڴ�ת����Ч�ʸ�
				next_endpoint->SendPocket(memory, memory_size);
			}
		}
		else if (next_endpoint == endpoint)
		{
			if (pre_endpoint && pre_endpoint->IsConnected())
			{
				need_free = false; // ֱ��ʹ���ڴ�ת����Ч�ʸ�
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
