
#include "ClientReceiver.h"
#include "ClientServer.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ALittle/LibServer/ServerSystem/ServerSchedule.h"

#include <functional>

namespace ALittle
{

ClientReceiver::ClientReceiver(SocketPtr socket, ClientServerWeakPtr server, ServerSchedule* schedule)
    : m_socket(socket), m_server(server), m_memory(0), m_excuting(false), m_is_connected(true), m_schedule(schedule)
	, m_is_websocket(false), m_websocket_buffer(0), m_frame_buffer(), m_has_mark(false), m_opcode(0), m_data_length(0)
	, m_head_size(0), m_body_size(0), m_current_is_message(false)
{
	// 获取客户端的公网IP
	m_remote_ip = socket->remote_endpoint().address().to_string();
	m_remote_port = socket->remote_endpoint().port();
}

ClientReceiver::~ClientReceiver()
{
	// 关闭socket，释放资源
	Close();
	// 释放内存
	if (m_memory) { free(m_memory); m_memory = 0; }
	if (m_websocket_buffer) { free(m_websocket_buffer); m_websocket_buffer = 0; }
}

void ClientReceiver::NextReadHeadFirst()
{
	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
		, std::bind(&ClientReceiver::HandleReadHeadFirst, this->shared_from_this()
			, std::placeholders::_1, std::placeholders::_2));
}

void ClientReceiver::HandleReadHeadFirst(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		ALITTLE_SYSTEM("receive failed:" << SUTF8(ec.message().c_str()));
		ClientServerPtr server = m_server.lock();
		if (server)	server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// check first char, if is 'G' then is websocket, otherwise binary
	if (m_message_head[0] != 'G')
		HandleReadHeadBinary(ec, actual_size);
	else
	{
		m_is_websocket = true;
		HandleWebSocketHandShakeReceive(ec, actual_size);
	}
}

void ClientReceiver::ReadComplete()
{
	// 设置大小为0
	m_head_size = 0;
	m_body_size = 0;

	// 检查服务器是否还存在
	ClientServerPtr server = m_server.lock();
	if (!server)
	{
		// 释放内存
		if (m_memory) { free(m_memory); m_memory = 0; }
		return;
	}

	// 读取协议头的信息
	MESSAGE_SIZE* message_size = (MESSAGE_SIZE*)m_message_head;
	MESSAGE_ID* message_id = (MESSAGE_ID*)(m_message_head + sizeof(MESSAGE_SIZE));
	MESSAGE_RPCID* message_rpcid = (MESSAGE_RPCID*)(m_message_head + sizeof(MESSAGE_SIZE) + sizeof(MESSAGE_ID));

	// 通过消息队列执行发送操作
	m_schedule->Execute(std::bind(&ClientServer::HandleClientMessage, server, this->shared_from_this()
		, *message_size, *message_id, *message_rpcid, m_memory));
	// 内存已经移交出去了，HandleClientMessage这个函数内部会负责释放
	// 这里置零
	m_memory = 0;
}

void ClientReceiver::Close()
{
	// 释放正在发送的数据包
	auto end = m_pocket_list.end();
	for (auto it = m_pocket_list.begin(); it != end; ++it)
		free(it->memory);
	m_pocket_list.clear();

	// 标记不是正在执行
	m_excuting = false;

	// 关闭socket
	if (m_socket)
	{
		asio::error_code ec;
		m_socket->close(ec);
	}
	m_socket = SocketPtr();

	// 这里不要急着释放m_memory，可能asio正在用
	// 放到析构函数里面释放
	// if (m_memory) { free(m_memory); m_memory = 0; }
}

void ClientReceiver::Send(const Message& message)
{
	if (m_is_websocket)
		SendWebSocket(message);
	else
		SendBinary(message);
}

void ClientReceiver::SendPocket(void* memory, int memory_size)
{
	// 保存信息
	PocketInfo info;
	info.memory_size = memory_size;
	info.memory = memory;

	// 添加一个数据包
	m_pocket_list.push_back(info);
	// 如果现在正在发送，那么就返回
	if (m_excuting) return;
	// 标记为正在发送
	m_excuting = true;
	// 发出一个包
	NextSend();
}

void ClientReceiver::NextSend()
{
	// 如果没有数据包了，或者socket已经被关闭了，就返回
	if (m_pocket_list.empty() || !m_socket)
	{
		m_excuting = false;
		return;
	}

	// 获取内存数据
	PocketInfo info = m_pocket_list.front();
	m_pocket_list.pop_front();

	// 异步发送
	asio::async_write(*m_socket, asio::buffer(info.memory, info.memory_size)
					, std::bind(&ClientReceiver::HandleSend, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2, info.memory));
}

void ClientReceiver::HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory)
{
	// 释放内存
	if (memory) free(memory);

	if (ec)
	{
		// 如果发送失败了，说明已经断开连接了
		ALITTLE_SYSTEM("send failed:" << SUTF8(ec.message().c_str()));
		ClientServerPtr server = m_server.lock();
		if (server) server->HandleOuterDisconnected(this->shared_from_this());
		return;
	}

	// 发送下一个数据包
	NextSend();
}

} // ALittle
