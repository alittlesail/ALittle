
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
	// 关闭
	Close("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver调用析构函数的时候触发ClearRPC");
	// 释放内存
	if (m_memory) { free(m_memory); m_memory = 0; }
}

void ConnectReceiver::NextReadHead()
{
	// 如果socket已经释放，这里直接返回
	if (!m_socket) return;

	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
					, std::bind(&ConnectEndpoint::HandleReadHead, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2));
}

void ConnectReceiver::HandleReadHead(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存，标记为未连接
		if (m_memory) { free(m_memory); m_memory = 0; }
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver 消息包接收失败:" << ec.value());

		// 如果当前还是连接状态，那么才调用HandleOuterDisconnected
		// 避免多次调用HandleOuterDisconnected而引起的框架问题
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}

	// 获取协议大小
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	
	if (message_size > 100*1024*1024)
	{
		// 释放内存，标记为未连接
		if (m_memory) { free(m_memory); m_memory = 0; }
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver 消息头超过100M数据 message_size:" << message_size);

		// 如果当前还是连接状态，那么才调用HandleOuterDisconnected
		// 避免多次调用HandleOuterDisconnected而引起的框架问题
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}

	// 申请内存
	if (m_memory) { free(m_memory); m_memory = 0; }
	m_memory = malloc(message_size + CARP_PROTOCOL_HEAD_SIZE);
	char* body_memory = (char*)m_memory;

	// 复制协议头
	memcpy(body_memory, m_message_head, sizeof(m_message_head));

	// 如果没有协议体，那么就直接完成
	if (message_size == 0)
	{
		ReadComplete();
		NextReadHead();
		return;
	}
	
	// 读取协议体
	asio::async_read(*m_socket, asio::buffer((char*)m_memory + CARP_PROTOCOL_HEAD_SIZE, message_size)
		, std::bind(&ConnectEndpoint::HandleReadBody, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ConnectReceiver::HandleReadBody(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存，并且设置为未连接
		if (m_memory) { free(m_memory); m_memory = 0; }
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver 消息包接收失败:" << ec.value());

		// 如果当前还是连接状态，那么才调用HandleOuterDisconnected
		// 避免多次调用HandleOuterDisconnected而引起的框架问题
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server) server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}

	// 协议体读取完毕
	ReadComplete();
	// 读取下一个消息包
	NextReadHead();
}

void ConnectReceiver::ReadComplete()
{
	// 获取协议大小，计算出内存大小
	CARP_MESSAGE_SIZE message_size = *(CARP_MESSAGE_SIZE*)m_message_head;
	int memory_size = message_size + CARP_PROTOCOL_HEAD_SIZE;

	// 处理消息包
	m_route_system->GetSchedule()->Execute(std::bind(&ConnectEndpoint::HandleMessage
							, this->shared_from_this(), m_memory, memory_size));
	// 内存已经移交出去，HandleMessage会负责释放内存
	// 这里置0
	m_memory = 0;
}

void ConnectReceiver::Close(const std::string& reason)
{
	// 释放消息包内存
	PocketList::iterator it, end = m_pocket_list.end();
	for (it = m_pocket_list.begin(); it != end; ++it)
		free(it->memory);
	m_pocket_list.clear();

	// 标记为连接失败
	m_is_connected = false;

	// 关闭并释放socket
	if (m_socket)
	{
		asio::error_code ec;
		m_socket->close(ec);
	}
	m_socket = SocketPtr();

	// 这里不要急着释放m_memory，可能asio正在用
	// 放到析构函数里面释放
	// if (m_memory) { free(m_memory); m_memory = 0; }

	ClearRPC(reason);
}

void ConnectReceiver::Send(const CarpMessage& message)
{
	// 获取消息包大小
	CARP_MESSAGE_SIZE message_size = message.GetTotalSize();
	// 获取消息包ID
	CARP_MESSAGE_ID message_id = message.GetID();
	// 获取消息包RPCID
	CARP_MESSAGE_RPCID message_rpcid = message.GetRpcID();

	// 内存大小 = 协议体大小 + 协议头大小
	int memory_size = message_size + CARP_PROTOCOL_HEAD_SIZE;

	// 申请内存
	void* memory = malloc(memory_size);
	char* body_memory = (char*)memory;

	// 设置协议头
	memcpy(body_memory, &message_size, sizeof(CARP_MESSAGE_SIZE));
	body_memory += sizeof(CARP_MESSAGE_SIZE);
	memcpy(body_memory, &message_id, sizeof(CARP_MESSAGE_ID));
	body_memory += sizeof(CARP_MESSAGE_ID);
	memcpy(body_memory, &message_rpcid, sizeof(CARP_MESSAGE_RPCID));
	body_memory += sizeof(CARP_MESSAGE_RPCID);

	// 序列化
	message.Serialize(body_memory);

	// 发送
	SendPocket(memory, memory_size);
}

void ConnectReceiver::SendPocket(void* memory, int memory_size)
{
	PocketInfo info;
	info.memory_size = memory_size;
	info.memory = memory;

	// 添加到待发送列表
	m_pocket_list.push_back(info);
	// 如果已经正在发送了，就直接返回
	if (m_excuting) return;
	// 标记为当前正在发送
	m_excuting = true;
	// 发送下一个消息包
	NextSend();
}

void ConnectReceiver::NextSend()
{
	// 检查待发送列表，socket是否存在
	if (m_pocket_list.empty() || !m_socket)
	{
		m_excuting = false;
		return;
	}

	// 获取消息包
	PocketInfo info = m_pocket_list.front();
	m_pocket_list.pop_front();

	// 发送
	asio::async_write(*m_socket, asio::buffer(info.memory, info.memory_size)
					, std::bind(&ConnectEndpoint::HandleSend, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2, info.memory));
}

void ConnectReceiver::HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory)
{
	// 释放内存
	if (memory) free(memory);

	if (ec)
	{
		//  消息包发送失败，并通知断开连接
		CARP_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver 消息包发送失败，并通知断开连接:" << ec.value());

		// 如果当前还是连接状态，那么才调用HandleOuterDisconnected
		// 避免多次调用HandleOuterDisconnected而引起的框架问题
		if (m_is_connected)
		{
			m_is_connected = false;
			ConnectServerPtr server = m_server.lock();
			if (server) server->HandleOuterDisconnected(this->shared_from_this());
		}
		return;
	}
	
	// 继续发下一个包
	NextSend();
}

} // ALittle
