
#include "ConnectReceiver.h"
#include "ConnectServer.h"
#include "RouteDefine.h"
#include "RouteSystem.h"
#include "../ServerSystem/ServerSchedule.h"

#include "Carp/carp_log.hpp"

namespace ALittle
{

ConnectReceiver::ConnectReceiver(SocketPtr socket, ConnectServerWeakPtr server, ROUTE_ID route_id, RouteSystem* route_system)
: ConnectEndpoint(route_system)
, m_socket(socket), m_server(server), m_memory(0), m_excuting(false), m_is_connected(true)
{
	m_remote_ip = socket->remote_endpoint().address().to_string();
	m_remote_port = socket->remote_endpoint().port();
	m_route_id = route_id;
}

ConnectReceiver::~ConnectReceiver()
{
	// �ر�
	CloseImpl("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver��������������ʱ�򴥷�ClearRPC");
	// �ͷ��ڴ�
	if (m_memory) { free(m_memory); m_memory = 0; }
}

void ConnectReceiver::NextReadHead()
{
	// ���socket�Ѿ��ͷţ�����ֱ�ӷ���
	if (!m_socket) return;

	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
					, std::bind(&ConnectEndpoint::HandleReadHead, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2));
}

void ConnectReceiver::HandleReadHead(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// �ͷ��ڴ棬���Ϊδ����
		if (m_memory) { free(m_memory); m_memory = 0; }
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver ��Ϣ������ʧ��:" << ec.value());

		// �����ǰ��������״̬����ô�ŵ���HandleOuterDisconnected
		// �����ε���HandleOuterDisconnected������Ŀ������
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}

	// ��ȡЭ���С
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	
	if (message_size > 100*1024*1024)
	{
		// �ͷ��ڴ棬���Ϊδ����
		if (m_memory) { free(m_memory); m_memory = 0; }
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver ��Ϣͷ����100M���� message_size:" << message_size);

		// �����ǰ��������״̬����ô�ŵ���HandleOuterDisconnected
		// �����ε���HandleOuterDisconnected������Ŀ������
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}

	// �����ڴ�
	if (m_memory) { free(m_memory); m_memory = 0; }
	m_memory = malloc(message_size + CARP_PROTOCOL_HEAD_SIZE);
	char* body_memory = (char*)m_memory;

	// ����Э��ͷ
	memcpy(body_memory, m_message_head, sizeof(m_message_head));

	// ���û��Э���壬��ô��ֱ�����
	if (message_size == 0)
	{
		ReadComplete();
		NextReadHead();
		return;
	}
	
	// ��ȡЭ����
	asio::async_read(*m_socket, asio::buffer((char*)m_memory + CARP_PROTOCOL_HEAD_SIZE, message_size)
		, std::bind(&ConnectEndpoint::HandleReadBody, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ConnectReceiver::HandleReadBody(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// �ͷ��ڴ棬��������Ϊδ����
		if (m_memory) { free(m_memory); m_memory = 0; }
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver ��Ϣ������ʧ��:" << ec.value());

		// �����ǰ��������״̬����ô�ŵ���HandleOuterDisconnected
		// �����ε���HandleOuterDisconnected������Ŀ������
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server) server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}

	// Э�����ȡ���
	ReadComplete();
	// ��ȡ��һ����Ϣ��
	NextReadHead();
}

void ConnectReceiver::ReadComplete()
{
	// ��ȡЭ���С��������ڴ��С
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	int memory_size = message_size + CARP_PROTOCOL_HEAD_SIZE;

	// ������Ϣ��
	m_route_system->GetSchedule()->Execute(std::bind(&ConnectEndpoint::HandleMessage
							, this->shared_from_this(), m_memory, memory_size));
	// �ڴ��Ѿ��ƽ���ȥ��HandleMessage�Ḻ���ͷ��ڴ�
	// ������0
	m_memory = 0;
}

void ConnectReceiver::Close(const std::string& reason)
{
	CloseImpl(reason);

	// ������server�Ƴ��Լ�
	auto server = m_server.lock();
	if (server) server->RemoveReceiver(this->shared_from_this());
}

void ConnectReceiver::CloseImpl(const std::string& reason)
{
	// �ͷ���Ϣ���ڴ�
	PocketList::iterator it, end = m_pocket_list.end();
	for (it = m_pocket_list.begin(); it != end; ++it)
		free(it->memory);
	m_pocket_list.clear();

	// ���Ϊ����ʧ��
	m_is_connected = false;

	// �رղ��ͷ�socket
	if (m_socket)
	{
		asio::error_code ec;
		m_socket->close(ec);
	}
	m_socket = SocketPtr();

	// ���ﲻҪ�����ͷ�m_memory������asio������
	// �ŵ��������������ͷ�
	// if (m_memory) { free(m_memory); m_memory = 0; }

	ClearRPC(reason);
}

void ConnectReceiver::Send(const CarpMessage& message)
{
	// ��ȡ��Ϣ����С
	CARP_MESSAGE_SIZE message_size = message.GetTotalSize();
	// ��ȡ��Ϣ��ID
	CARP_MESSAGE_ID message_id = message.GetID();
	// ��ȡ��Ϣ��RPCID
	CARP_MESSAGE_RPCID message_rpcid = message.GetRpcID();

	// �ڴ��С = Э�����С + Э��ͷ��С
	int memory_size = message_size + CARP_PROTOCOL_HEAD_SIZE;

	// �����ڴ�
	void* memory = malloc(memory_size);
	char* body_memory = (char*)memory;

	// ����Э��ͷ
	memcpy(body_memory, &message_size, sizeof(CARP_MESSAGE_SIZE));
	body_memory += sizeof(CARP_MESSAGE_SIZE);
	memcpy(body_memory, &message_id, sizeof(CARP_MESSAGE_ID));
	body_memory += sizeof(CARP_MESSAGE_ID);
	memcpy(body_memory, &message_rpcid, sizeof(CARP_MESSAGE_RPCID));
	body_memory += sizeof(CARP_MESSAGE_RPCID);

	// ���л�
	message.Serialize(body_memory);

	// ����
	SendPocket(memory, memory_size);
}

void ConnectReceiver::SendPocket(void* memory, int memory_size)
{
	PocketInfo info;
	info.memory_size = memory_size;
	info.memory = memory;

	// ��ӵ��������б�
	m_pocket_list.push_back(info);
	// ����Ѿ����ڷ����ˣ���ֱ�ӷ���
	if (m_excuting) return;
	// ���Ϊ��ǰ���ڷ���
	m_excuting = true;
	// ������һ����Ϣ��
	NextSend();
}

void ConnectReceiver::NextSend()
{
	// ���������б�socket�Ƿ����
	if (m_pocket_list.empty() || !m_socket)
	{
		m_excuting = false;
		return;
	}

	// ��ȡ��Ϣ��
	PocketInfo info = m_pocket_list.front();
	m_pocket_list.pop_front();

	// ����
	asio::async_write(*m_socket, asio::buffer(info.memory, info.memory_size)
					, std::bind(&ConnectEndpoint::HandleSend, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2, info.memory));
}

void ConnectReceiver::HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory)
{
	// �ͷ��ڴ�
	if (memory) free(memory);

	if (ec)
	{
		//  ��Ϣ������ʧ�ܣ���֪ͨ�Ͽ�����
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver ��Ϣ������ʧ�ܣ���֪ͨ�Ͽ�����:" << ec.value());

		// �����ǰ��������״̬����ô�ŵ���HandleOuterDisconnected
		// �����ε���HandleOuterDisconnected������Ŀ������
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server) server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}
	
	// ��������һ����
	NextSend();
}

} // ALittle
