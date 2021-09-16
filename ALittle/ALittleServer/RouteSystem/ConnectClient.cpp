
#include "ConnectClient.h"
#include "ConnectMessage.h"
#include "RouteDefine.h"
#include "RouteSystem.h"
#include "../ServerSystem/ServerSchedule.h"

#include "Carp/carp_log.hpp"

namespace ALittle
{
	 
ConnectClient::ConnectClient(RouteSystem* route_system)
: ConnectEndpoint(route_system)
, m_port(0), m_memory(0), m_excuting(false), m_is_connecting(false)
, m_reconnect_interval(0), m_heartbeat_interval(0), m_message_head()
{
}

ConnectClient::~ConnectClient()
{
	// �ر�
	CloseImpl("route_id:" + ROUTE2S(m_route_id) + u8":ConnectClient��������������ʱ�򴥷�ClearRPC");
	// �ͷ��ڴ�
	if (m_memory) { free(m_memory); m_memory = 0; }
}

void ConnectClient::Connect(ROUTE_ID route_id
							, const std::string& ip, unsigned int port
							, int heartbeat_interval
							, int reconnect_interval)
{
	// ����Ƿ���������
	if (m_is_connecting)
	{
		CARP_ERROR(u8"ConnectClient:Connect �������ӵ�ʱ�򣬲����ٽ������ӣ�" << "ip:" << ip << ", port:" << port);
		return;
	}

	// �ȹر�
	Close(u8"ConnectClient:Connect ʱ����Close����ClearRPC");

	// ���Ϊ��������
	m_is_connecting = true;
	// ����Ͽ������ļ��ʱ��
	m_reconnect_interval = reconnect_interval;
	// �����������ļ��ʱ��
	m_heartbeat_interval = heartbeat_interval;
	// ����һ��socket����
	m_socket = SocketPtr(new asio::ip::tcp::socket(m_route_system->GetSchedule()->GetIOService()));
	// ����һ��Ŀ������������ӵ�
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::from_string(ip), port);

	// ���沢��ʼ��
	m_ip = ip;
	m_port = port;
	m_route_id = route_id;
	m_target_route_id = 0;

	// ��ʼ�첽����
	m_socket->async_connect(ep, std::bind(&ConnectEndpoint::HandleAsyncConnect, this->shared_from_this(), std::placeholders::_1));
}

void ConnectClient::HandleAsyncConnect(const asio::error_code& ec)
{
	if (ec)
	{
		// �����־����ӡ����Ϊ�����̫�࣬�ֲ���Ҫ
		// CARP_SYSTEM(u8"ConnectClient ����ʧ��: " << SUTF8(asio::system_error(ec).what()) << ", ip:" << m_ip << ", port:" << m_port);
		
		// ��������ʧ��
		HandleConnectFailed();

		// ��������ʱ��
		m_reconnect_timer = AsioTimerPtr(new AsioTimer(m_route_system->GetSchedule()->GetIOService(), std::chrono::seconds(m_reconnect_interval)));
		m_reconnect_timer->async_wait(std::bind(&ConnectEndpoint::HandleReconnectTimer, this->shared_from_this(), std::placeholders::_1));
		return;
	}
	// ���� nodelay
	m_socket->set_option(asio::ip::tcp::no_delay(true));
	
	// ���Ϊ�������ڷ���
	m_excuting = false;
	// ���Ϊ������������
	m_is_connecting = false;

	// ���ͱ������ݣ�����ע������
	QConnectRegister msg;
	msg.route_id = m_route_id;
	Send(msg);

	// ��ʼ������Ϣ��
	NextReadHead();

	// ����������ʱ��
	m_heartbeat_timer = AsioTimerPtr(new AsioTimer(m_route_system->GetSchedule()->GetIOService(), std::chrono::seconds(m_heartbeat_interval)));
	m_heartbeat_timer->async_wait(std::bind(&ConnectEndpoint::HandleHeartbeatTimer, this->shared_from_this(), std::placeholders::_1));
	
	// �������ӳɹ�
	HandleConnectSucceed();
}

void ConnectClient::HandleReconnectTimer(const asio::error_code& ec)
{
	// ������ִ����룬˵��������ȡ����ʱ����
	if (ec == asio::error::operation_aborted) return;

	// ��������һ��Ҫ��ӡһ��
	if (ec) CARP_ERROR(u8"��ʱ������δ֪�Ĵ������ͣ�һ��Ҫ�����һ��:" << ec.value());

	// �رգ��ͷ�
	Close("route_id:" + ROUTE2S(m_route_id) + u8":ConnectClient:HandleReconnectTimer ��������ʧ�ܵ�ʱ�����Close������ClearRPC");

	// ���¿�ʼ����
	Connect(m_route_id, m_ip, m_port, m_reconnect_interval, m_heartbeat_interval);
}

void ConnectClient::HandleHeartbeatTimer(const asio::error_code& ec)
{
	// ������ִ����룬˵��������ȡ����ʱ����
	if (ec == asio::error::operation_aborted) return;

	// ��������һ��Ҫ��ӡһ��
	if (ec) CARP_ERROR(u8"��ʱ������δ֪�Ĵ������ͣ�һ��Ҫ�����һ��:" << ec.value());

	// ����������
	HeartbeatMessage msg;
	Send(msg);

	if (!m_heartbeat_timer) return;
	m_heartbeat_timer->expires_at(std::chrono::system_clock::now() + std::chrono::seconds(m_heartbeat_interval));
	m_heartbeat_timer->async_wait(std::bind(&ConnectEndpoint::HandleHeartbeatTimer, this->shared_from_this(), std::placeholders::_1));
}

bool ConnectClient::IsConnected()
{
	return m_is_connecting == false && m_socket != SocketPtr();
}

bool ConnectClient::IsConnecting()
{
	return m_is_connecting;
}

void ConnectClient::Close(const std::string& reason)
{
	CloseImpl(reason);
}

void ConnectClient::CloseImpl(const std::string& reason)
{
	// �ͷŴ����͵���Ϣ��
	auto end = m_pocket_list.end();
	for (auto it = m_pocket_list.begin(); it != end; ++it)
		free(it->memory);
	m_pocket_list.clear();

	// ���Ϊ�������ڷ���
	m_excuting = false;
	// ���Ϊ������������
	m_is_connecting = false;

	// �ر�������ʱ��
	if (m_reconnect_timer)
	{
		asio::error_code ec;
		m_reconnect_timer->cancel(ec);
		m_reconnect_timer = AsioTimerPtr();
	}
	// �ر�������ʱ��
	if (m_heartbeat_timer)
	{
		asio::error_code ec;
		m_heartbeat_timer->cancel(ec);
		m_heartbeat_timer = AsioTimerPtr();
	}

	// �ͷ�socket
	if (m_socket)
	{
		asio::error_code ec;
		m_socket->close(ec);
	}
	m_socket = SocketPtr();

	// ���ﲻҪ�����ͷ�m_memory������asio������
	// �ŵ��������������ͷ�
	// if (m_memory) { free(m_memory); m_memory = 0; }

	// �ɿ��Իص�ȫ���Ե���ʧ�ܴ���
	ClearRPC(reason);
}

void ConnectClient::ExecuteDisconnectCallback()
{
	// ���socket�ǿ�ָ�룬��ô�϶�����������Close�����
	// ���ʱ�����ڶϿ����ӣ����Բ�Ҫ����HandleDisconnected()
	bool close_by_self = (m_socket == SocketPtr());

	// �رգ��ڲ����m_socket����Ϊ��ָ��
	// ���Լ�ʹͬʱ��Ϊ����ʧ�ܻ��߷���ʧ�ܶ�������ExecuteDisconnectCallbackҲ�����ε���HandleDisconnected
	Close("route_id:" + ROUTE2S(m_route_id) + u8" ConnectClient:ExecuteDisconnectCallback �Ͽ����ӵ�ʱ�����Close������ClearRPC");

	// ��������Լ��رյģ���ô�͵��ûص�
	if (close_by_self == false) HandleDisconnected();
}

void ConnectClient::NextReadHead()
{
	// ����Ѿ��ͷ��˾�ֱ�ӷ���
	if (!m_socket) return;

	// ��ʼ����Э��ͷ
	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
					, std::bind(&ConnectEndpoint::HandleReadHead, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2));
}

void ConnectClient::HandleReadHead(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// �ͷ��ڴ�
		if (m_memory) { free(m_memory); m_memory = 0; }
		// ���ݰ�����ʧ�ܣ�˵���ǶϿ�������
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectClient:HandleReadHead ��Ϣ������ʧ�ܣ����ӶϿ���:" << ec.value());
		ExecuteDisconnectCallback();
		return;
	}

	// ��ȡЭ���С
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	
	// �����ڴ�
	if (m_memory) { free(m_memory); m_memory = 0; }
	m_memory = malloc(message_size + CARP_PROTOCOL_HEAD_SIZE);
	char* body_memory = (char*)m_memory;

	// Э��ͷ���Ƶ��ڴ�
	memcpy(body_memory, m_message_head, sizeof(m_message_head));

	// ���û��Э�����ʾ��ȡ���
	if (message_size == 0)
	{
		ReadComplete();
		NextReadHead();
		return;
	}

	// ��ʼ��ȡЭ����
	asio::async_read(*m_socket, asio::buffer((char*)m_memory + CARP_PROTOCOL_HEAD_SIZE, message_size)
		, std::bind(&ConnectEndpoint::HandleReadBody, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ConnectClient::HandleReadBody(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// �ͷ��ڴ�
		if (m_memory) { free(m_memory); m_memory = 0; }
		// ���ݰ�����ʧ�ܣ�˵���ǶϿ�������
		CARP_INFO("route_id:" + ROUTE2S(m_route_id) + u8" ConnectClient:HandleReadBody ��Ϣ������ʧ��:" << ec.value());
		// ֪ͨ�Ͽ�����
		ExecuteDisconnectCallback();
		return;
	}

	// ����Э��
	ReadComplete();
	// ������ȡ��һ����Ϣ��
	NextReadHead();
}

void ConnectClient::ReadComplete()
{
	// ��ȡЭ���С
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	// ���͸�����ϵͳ
	m_route_system->GetSchedule()->Execute(std::bind(&ConnectEndpoint::HandleMessage, this->shared_from_this(), m_memory, message_size + CARP_PROTOCOL_HEAD_SIZE));
	// �ڴ��Ѿ��ƽ���ȥ��HandleMessage�Ḻ���ͷ�
	// ������0
	m_memory = 0;
}

void ConnectClient::Send(const CarpMessage& message)
{
	// ��ȡЭ���С
	CARP_MESSAGE_SIZE message_size = message.GetTotalSize();
	// ��ȡЭ��ID
	CARP_MESSAGE_ID message_id = message.GetID();
	// ��ȡRPCID
	CARP_MESSAGE_RPCID message_rpcid = message.GetRpcID();

	// Э���С = Э�����С + Э��ͷ��С
	unsigned int memory_size = message_size + CARP_PROTOCOL_HEAD_SIZE;

	// �����ڴ�
	void* memory = malloc(memory_size);
	char* body_memory = (char*)memory;

	// ����Э��ͷ��Ϣ
	memcpy(body_memory, &message_size, sizeof(CARP_MESSAGE_SIZE));
	body_memory += sizeof(CARP_MESSAGE_SIZE);
	memcpy(body_memory, &message_id, sizeof(CARP_MESSAGE_ID));
	body_memory += sizeof(CARP_MESSAGE_ID);
	memcpy(body_memory, &message_rpcid, sizeof(CARP_MESSAGE_RPCID));
	body_memory += sizeof(CARP_MESSAGE_RPCID);
	
	// ���л���Ϣ��
	message.Serialize(body_memory);

	// ����
	SendPocket(memory, memory_size);
}

void ConnectClient::SendPocket(void* memory, int memory_size)
{
	// �����ڴ�ṹ
	PocketInfo info;
	info.memory_size = memory_size;
	info.memory = memory;

	// ��ӵ��������б�
	m_pocket_list.push_back(info);
	// ����Ѿ����ڷ����ˣ���ô��ֱ�ӷ���
	if (m_excuting) return;
	// ������ڷ���
	m_excuting = true;
	// ����һ����Ϣ��
	NextSend();
}

void ConnectClient::NextSend()
{
	// ������б��ǿյģ�����socket�Ѿ��ر��ˣ�ֱ�ӷ���
	if (m_pocket_list.empty() || !m_socket)
	{
		m_excuting = false;
		return;
	}

	// ��ȡһ���ṹ��
	PocketInfo info = m_pocket_list.front();
	m_pocket_list.pop_front();

	// ����
	asio::async_write(*m_socket, asio::buffer(info.memory, info.memory_size)
		, std::bind(&ConnectEndpoint::HandleSend, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2, info.memory));
}

void ConnectClient::HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory)
{
	// �ͷ��ڴ�
	if (memory) free(memory);

	// ������
	if (ec)
	{
		// ����ʧ��˵���Ͽ������ˣ��������ﲻ��֪ͨ��ͳһ�ڶ�ȡ�Ǹ�λ�ý���֪ͨ
		CARP_SYSTEM("route_id:" << ROUTE2S(m_route_id) + u8" ConnectClient:HandleSend ��Ϣ������ʧ��:" << ec.value());
		// ���ﲻ֪ͨ�Ͽ����ӣ��ȴ������ǲ���֪ͨ�Ͽ�
		ExecuteDisconnectCallback();
		return;
	}
	
	// ������һ����
	NextSend();
}

} // ALittle
