
#include "ConnectClient.h"
#include "../ServerSystem/SocketSchedule.h"
extern "C" {
	#include "../socket.h"
}

namespace ALittle
{
	 
ConnectClient::ConnectClient(_socket* c, SocketSchedule* schedule, int id)
: m_port(0), m_binary_value(0), m_excuting(false), m_is_connecting(false), m_id(id)
{
}

ConnectClient::~ConnectClient()
{
	Close();
	// 释放内存
	if (m_binary_value) { free(m_binary_value); m_binary_value = 0; }
}

void ConnectClient::Connect(const std::string& ip, unsigned int port)
{
	// 检查是否正在连接
	if (IsConnected() || IsConnecting()) return;

	// 标记为正在连接
	m_is_connecting = true;
	// 创建一个socket对象
	m_socket = SocketPtr(new asio::ip::tcp::socket(m_schedule->GetIOService()));
	// 创建一个目标服务器的连接点
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::from_string(ip), port);

	// 保存并初始化
	m_ip = ip;
	m_port = port;

	// 开始异步连接
	m_socket->async_connect(ep, std::bind(&ConnectClient::HandleAsyncConnect, this->shared_from_this(), std::placeholders::_1));
}

void ConnectClient::HandleAsyncConnect(const asio::error_code& ec)
{
	if (ec)
	{
		// 这个日志不打印，因为会出现太多，又不重要
		// ALITTLE_SYSTEM(u8"ConnectClient 连接失败: " << SUTF8(asio::system_error(ec).what()) << ", ip:" << m_ip << ", port:" << m_port);
		
		// 处理连接失败
		HandleConnectFailed();
		return;
	}
	// 设置 nodelay
	m_socket->set_option(asio::ip::tcp::no_delay(true));
	
	// 标记为不是正在发包
	m_excuting = false;
	// 标记为不是正在连接
	m_is_connecting = false;

	// 处理连接成功
	HandleConnectSucceed();
}

bool ConnectClient::IsConnected()
{
	return m_is_connecting == false && m_socket != SocketPtr();
}

bool ConnectClient::IsConnecting()
{
	return m_is_connecting;
}

void ConnectClient::Close()
{
	// 释放带发送的消息包
	auto end = m_pocket_list.end();
	for (auto it = m_pocket_list.begin(); it != end; ++it)
		free(it->memory);
	m_pocket_list.clear();

	// 标记为不是正在发包
	m_excuting = false;
	// 标记为不是正在连接
	m_is_connecting = false;

	// 释放socket
	if (m_socket)
	{
		asio::error_code ec;
		m_socket->close(ec);
	}
	m_socket = SocketPtr();

	// 这里不要急着释放m_memory，可能asio正在用
	// 放到析构函数里面释放
	// if (m_binary_value) { free(m_binary_value); m_binary_value = 0; }
}

void ConnectClient::ExecuteDisconnectCallback()
{
	// 如果socket是空指针，那么肯定是主动调用Close引起的
	// 这个时候不属于断开连接，所以不要调用HandleDisconnected()
	bool close_by_self = (m_socket == SocketPtr());

	// 关闭，内部会把m_socket设置为空指针
	// 所以即使同时因为接收失败或者发送失败而触发的ExecuteDisconnectCallback也不会多次调用HandleDisconnected
	Close();

	// 如果不是自己关闭的，那么就调用回调
	if (close_by_self == false) HandleDisconnected();
}

void ConnectClient::HandleConnectFailed()
{
	socket_event* event = socket_createevent(m__socket);
	event->type = socket_event_types::MSG_CONNECT_FAILED;
	event->id = m_id;
	socket_addevent(m__socket, event, 0);

	// 释放自己
	// 这个务必最后最后调用，这个操作相当于delete自己
	m_schedule->m_connect_map.erase(m_id);
}

void ConnectClient::HandleConnectSucceed()
{
	socket_event* event = socket_createevent(m__socket);
	event->type = socket_event_types::MSG_CONNECT_SUCCEED;
	event->id = m_id;
	socket_addevent(m__socket, event, 0);
}

void ConnectClient::HandleDisconnected()
{
	socket_event* event = socket_createevent(m__socket);
	event->type = socket_event_types::MSG_DISCONNECTED;
	event->id = m_id;
	socket_addevent(m__socket, event, 0);

	// 释放自己
	// 这个务必最后最后调用，这个操作相当于delete自己
	m_schedule->m_connect_map.erase(m_id);
}

void ConnectClient::ReadNumber(int size, int read_type)
{
	// 如果已经释放了就直接返回
	if (!m_socket) return;

	// 开始接受协议头
	asio::async_read(*m_socket, asio::buffer(m_simple_value, size)
					, std::bind(&ConnectClient::HandleReadNumber, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2, read_type));
}

void ConnectClient::HandleReadNumber(const asio::error_code& ec, std::size_t actual_size, int type)
{
	if (ec)
	{
		// 释放内存
		if (m_binary_value) { free(m_binary_value); m_binary_value = 0; }
		ExecuteDisconnectCallback();
		return;
	}

	socket_event* event = socket_createevent(m__socket);
	event->type = (socket_event_types)type;
	switch (event->type)
	{
	case socket_event_types::MSG_READ_UINT8: event->int_value = *((unsigned char*)m_simple_value); break;
	case socket_event_types::MSG_READ_INT8: event->int_value = *((char*)m_simple_value); break;
	case socket_event_types::MSG_READ_UINT16: event->int_value = *((unsigned short*)m_simple_value); break;
	case socket_event_types::MSG_READ_INT16: event->int_value = *((short*)m_simple_value); break;
	case socket_event_types::MSG_READ_UINT32: event->int_value = *((unsigned int*)m_simple_value); break;
	case socket_event_types::MSG_READ_INT32: event->int_value = *((int*)m_simple_value); break;
	case socket_event_types::MSG_READ_UINT64: event->int_value = *((unsigned long long*)m_simple_value); break;
	case socket_event_types::MSG_READ_INT64: event->int_value = *((long long*)m_simple_value); break;
	case socket_event_types::MSG_READ_FLOAT: event->double_value = *((float*)m_simple_value); break;
	case socket_event_types::MSG_READ_DOUBLE: event->double_value = *((double*)m_simple_value); break;
	}
	socket_addevent(m__socket, event, 0);
}

void ConnectClient::ReadBinary(int size, int read_type)
{
	// 如果已经释放了就直接返回
	if (!m_socket) return;
	if (m_binary_value != 0) return;

	m_binary_value = (char*)malloc(size);

	// 开始接受协议头
	asio::async_read(*m_socket, asio::buffer(m_binary_value, size)
		, std::bind(&ConnectClient::HandleReadBinary, this->shared_from_this()
			, std::placeholders::_1, std::placeholders::_2, read_type));
}

void ConnectClient::HandleReadBinary(const asio::error_code& ec, std::size_t actual_size, int type)
{
	if (ec)
	{
		// 释放内存
		if (m_binary_value) { free(m_binary_value); m_binary_value = 0; }
		ExecuteDisconnectCallback();
		return;
	}

	socket_event* event = socket_createevent(m__socket);
	event->type = (socket_event_types)type;
	event->binary_value = m_binary_value;
	m_binary_value = 0;
	socket_addevent(m__socket, event, 0);
}

void ConnectClient::SendPocket(void* memory, int memory_size)
{
	// 构建内存结构
	PocketInfo info;
	info.memory_size = memory_size;
	info.memory = memory;

	// 添加到待发送列表
	m_pocket_list.push_back(info);
	// 如果已经正在发送了，那么就直接返回
	if (m_excuting) return;
	// 标记正在发送
	m_excuting = true;
	// 发送一个消息包
	NextSend();
}

void ConnectClient::NextSend()
{
	// 如果包列表是空的，或者socket已经关闭了，直接返回
	if (m_pocket_list.empty() || !m_socket)
	{
		m_excuting = false;
		return;
	}

	// 获取一个结构体
	PocketInfo info = m_pocket_list.front();
	m_pocket_list.pop_front();

	// 发送
	asio::async_write(*m_socket, asio::buffer(info.memory, info.memory_size)
		, std::bind(&ConnectClient::HandleSend, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2, info.memory));
}

void ConnectClient::HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory)
{
	// 释放内存
	if (memory) free(memory);

	// 检查错误
	if (ec)
	{
		// 这里不通知断开连接，等待接受那部分通知断开
		ExecuteDisconnectCallback();
		return;
	}
	
	// 发送下一个包
	NextSend();
}

} // ALittle
