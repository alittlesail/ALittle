
#include "ClientReceiver.h"
#include "ClientServer.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ALittle/LibServer/ServerSystem/ServerSchedule.h"

#include <functional>

namespace ALittle
{

void ClientReceiver::NextReadHeadBinary()
{
	// ���socket�Ѿ����ͷţ���ֱ�ӷ���
	if (!m_socket) return;

	// �첽��ȡ����
	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
					, std::bind(&ClientReceiver::HandleReadHeadBinary, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleReadHeadBinary(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// �ͷ��ڴ�
		if (m_memory) { free(m_memory); m_memory = 0; }
		// ��ȡʧ����˵�������ӶϿ��ˣ�֪ͨ��server
		ALITTLE_SYSTEM("ClientReceiver::HandleReadHead receive failed:" << SUTF8(ec.message().c_str()));
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// ��Э��ͷ��ȡ���ݰ���С
	MESSAGE_SIZE message_size = *(MESSAGE_SIZE*)m_message_head;
	
	// ������ݰ���СΪ0����ô��ֱ��ִ�����
	if (message_size == 0)
	{
		// ��ȡ��ɲ���
		ReadComplete();
		// ������һ����ȡ
		NextReadHeadBinary();
		return;
	}

	// ��Э���壬��ô�������ڴ�
	if (m_memory) { free(m_memory); m_memory = 0; }
	m_memory = malloc(message_size);
	
	// ��ȡЭ����
	asio::async_read(*m_socket, asio::buffer(m_memory, message_size)
		, std::bind(&ClientReceiver::HandleReadBodyBinary, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleReadBodyBinary(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// �ͷ��ڴ�
		if (m_memory) { free(m_memory); m_memory = 0; }
		// ��ȡʧ����˵���ǶϿ��ˣ�֪ͨ��server
		ALITTLE_SYSTEM("ClientReceiver::HandleReadBody receive failed:" << SUTF8(ec.message().c_str()));
		ClientServerPtr server = m_server.lock();
		if (server) server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// ��ȡ��ɲ���
	ReadComplete();
	// ������һ����ȡ
	NextReadHeadBinary();
}

void ClientReceiver::SendBinary(const Message& message)
{
	// ����Ѿ��رգ���ô�Ͳ��������ݰ�
	if (m_is_connected == false) return;

	// ��ȡ��Ϣ���ܴ�С
	MESSAGE_SIZE message_size = message.GetTotalSize();
	// ��ȡ��Ϣ��ID
	MESSAGE_ID message_id = message.GetID();
	// ��ȡRPCID
	MESSAGE_RPCID message_rpcid = message.GetRpcID();

	// �����ڴ��С
	int memory_size = message_size + PROTOCOL_HEAD_SIZE;

	// �����ڴ�
	void* memory = malloc(memory_size);
    if (memory == nullptr)
    {
        ALITTLE_ERROR("memory is null");
        return;
    }
	char* body_memory = static_cast<char*>(memory);

	// д����Ϣ����С��ID
	memcpy(body_memory, &message_size, sizeof(MESSAGE_SIZE));
	body_memory += sizeof(MESSAGE_SIZE);
	memcpy(body_memory, &message_id, sizeof(MESSAGE_ID));
	body_memory += sizeof(MESSAGE_ID);
	memcpy(body_memory, &message_rpcid, sizeof(MESSAGE_RPCID));
	body_memory += sizeof(MESSAGE_RPCID);

	// ϵ�л���Ϣ
	message.Serialize(body_memory);

	// �������ݰ�
	SendPocket(memory, memory_size);
}

} // ALittle