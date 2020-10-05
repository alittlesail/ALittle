
#include "ClientReceiver.h"
#include "ClientServer.h"

#include "Carp/carp_log.hpp"
#include "../ServerSystem/ServerSchedule.h"

#include <functional>

namespace ALittle
{

void ClientReceiver::NextReadHeadBinary()
{
	// 如果socket已经被释放，就直接返回
	if (!m_socket) return;

	// 异步读取数据
	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
					, std::bind(&ClientReceiver::HandleReadHeadBinary, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleReadHeadBinary(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存
		if (m_memory) { free(m_memory); m_memory = 0; }
		// 读取失败了说明是连接断开了，通知给server
		CARP_SYSTEM("ClientReceiver::HandleReadHead receive failed:" << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// 从协议头读取数据包大小
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	
	// 如果数据包大小为0，那么就直接执行完成
	if (message_size == 0)
	{
		// 读取完成操作
		ReadComplete();
		// 进行下一步读取
		NextReadHeadBinary();
		return;
	}

	// 有协议体，那么就申请内存
	if (m_memory) { free(m_memory); m_memory = 0; }
	m_memory = malloc(message_size);
	
	// 读取协议体
	asio::async_read(*m_socket, asio::buffer(m_memory, message_size)
		, std::bind(&ClientReceiver::HandleReadBodyBinary, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleReadBodyBinary(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存
		if (m_memory) { free(m_memory); m_memory = 0; }
		// 读取失败了说明是断开了，通知给server
		CARP_SYSTEM("ClientReceiver::HandleReadBody receive failed:" << ec.value());
		ClientServerPtr server = m_server.lock();
		if (server) server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// 读取完成操作
	ReadComplete();
	// 进行下一步读取
	NextReadHeadBinary();
}

void ClientReceiver::SendBinary(const CarpMessage& message)
{
	// 如果已经关闭，那么就不发送数据包
	if (m_is_connected == false) return;

	// 获取消息包总大小
	CARP_MESSAGE_SIZE message_size = message.GetTotalSize();
	// 获取消息包ID
	CARP_MESSAGE_ID message_id = message.GetID();
	// 获取RPCID
	CARP_MESSAGE_RPCID message_rpcid = message.GetRpcID();

	// 计算内存大小
	int memory_size = message_size + CARP_PROTOCOL_HEAD_SIZE;

	// 申请内存
	void* memory = malloc(memory_size);
    if (memory == nullptr)
    {
        CARP_ERROR("memory is null");
        return;
    }
	char* body_memory = static_cast<char*>(memory);

	// 写入消息包大小和ID
	memcpy(body_memory, &message_size, sizeof(CARP_MESSAGE_SIZE));
	body_memory += sizeof(CARP_MESSAGE_SIZE);
	memcpy(body_memory, &message_id, sizeof(CARP_MESSAGE_ID));
	body_memory += sizeof(CARP_MESSAGE_ID);
	memcpy(body_memory, &message_rpcid, sizeof(CARP_MESSAGE_RPCID));
	body_memory += sizeof(CARP_MESSAGE_RPCID);

	// 系列化消息
	message.Serialize(body_memory);

	// 发送数据包
	SendPocket(memory, memory_size);
}

} // ALittle
