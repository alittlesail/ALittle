
#include "ConnectClient.h"
#include "../ServerSystem/ServerSchedule.h"
extern "C" {
	#include "../net.h"
}

#include "../Helper/StringHelper.h"

namespace ALittle
{
	 
ConnectClient::ConnectClient(_net* c, ServerSchedule* schedule, int id)
: m_port(0), m_memory(0), m_excuting(false), m_is_connecting(false), m_message_head(), m_id(id)
{
}

ConnectClient::~ConnectClient()
{
	Close();
	// 释放内存
	if (m_memory) { free(m_memory); m_memory = 0; }
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

	// 开始接受消息包
	NextReadHead();

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
	// if (m_memory) { free(m_memory); m_memory = 0; }
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
	net_event* event = net_createevent(m_net);
	event->type = net_event_types::MSG_CONNECT_FAILED;
	event->id = m_id;
	net_addevent(m_net, event, 0);

	// 释放自己
	// 这个务必最后最后调用，这个操作相当于delete自己
	m_schedule->m_connect_map.erase(m_id);
}

void ConnectClient::HandleConnectSucceed()
{
	net_event* event = net_createevent(m_net);
	event->type = net_event_types::MSG_CONNECT_SUCCEED;
	event->id = m_id;
	net_addevent(m_net, event, 0);
}

void ConnectClient::HandleDisconnected()
{
	net_event* event = net_createevent(m_net);
	event->type = net_event_types::MSG_DISCONNECTED;
	event->id = m_id;
	net_addevent(m_net, event, 0);

	// 释放自己
	// 这个务必最后最后调用，这个操作相当于delete自己
	m_schedule->m_connect_map.erase(m_id);
}

void ConnectClient::NextReadHead()
{
	// 如果已经释放了就直接返回
	if (!m_socket) return;

	// 开始接受协议头
	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
					, std::bind(&ConnectClient::HandleReadHead, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2));
}

void ConnectClient::HandleReadHead(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存
		if (m_memory) { free(m_memory); m_memory = 0; }
		ExecuteDisconnectCallback();
		return;
	}

	// 读取协议大小
	MESSAGE_SIZE message_size = *(MESSAGE_SIZE*)m_message_head;
	
	// 申请内存
	if (m_memory) { free(m_memory); m_memory = 0; }
	m_memory = malloc(message_size + PROTOCOL_HEAD_SIZE);
	char* body_memory = (char*)m_memory;

	// 协议头复制到内存
	memcpy(body_memory, m_message_head, sizeof(m_message_head));

	// 如果没有协议体表示读取完成
	if (message_size == 0)
	{
		ReadComplete();
		NextReadHead();
		return;
	}

	// 开始读取协议体
	asio::async_read(*m_socket, asio::buffer((char*)m_memory + PROTOCOL_HEAD_SIZE, message_size)
		, std::bind(&ConnectClient::HandleReadBody, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ConnectClient::HandleReadBody(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存
		if (m_memory) { free(m_memory); m_memory = 0; }
		// 通知断开连接
		ExecuteDisconnectCallback();
		return;
	}

	// 处理协议
	ReadComplete();
	// 继续读取下一个消息包
	NextReadHead();
}

void ConnectClient::ReadComplete()
{
	// 获取协议大小
	MESSAGE_SIZE message_size = *(MESSAGE_SIZE*)m_message_head;
	// 发送给调度系统
	m_schedule->Execute(std::bind(&ConnectClient::HandleMessage, this->shared_from_this(), m_memory, message_size + PROTOCOL_HEAD_SIZE));
	// 内存已经移交出去，HandleMessage会负责释放
	// 这里置0
	m_memory = 0;
}

void ConnectClient::Send(const _write_factory* factory)
{
	// 获取协议大小
	MESSAGE_SIZE message_size = factory->size;
	// 获取协议ID
	MESSAGE_ID message_id = factory->id;
	// 获取RPCID
	MESSAGE_RPCID message_rpcid = factory->rpc_id;

	// 协议大小 = 协议体大小 + 协议头大小
	unsigned int memory_size = message_size + PROTOCOL_HEAD_SIZE;

	// 申请内存
	void* memory = malloc(memory_size);
	char* body_memory = (char*)memory;

	// 设置协议头信息
	memcpy(body_memory, &message_size, sizeof(MESSAGE_SIZE));
	body_memory += sizeof(MESSAGE_SIZE);
	memcpy(body_memory, &message_id, sizeof(MESSAGE_ID));
	body_memory += sizeof(MESSAGE_ID);
	memcpy(body_memory, &message_rpcid, sizeof(MESSAGE_RPCID));
	body_memory += sizeof(MESSAGE_RPCID);
	
	// 序列化消息包
	if (factory->size > 0)
		memcpy(body_memory, &(kv_A(factory->memory, 0)), factory->size);
	
	// 发送
	SendPocket(memory, memory_size);
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

void ConnectClient::HandleMessage(void* memory, int memory_size)
{
	net_event* event = net_createevent(m_net);
	event->type = net_event_types::MSG_MESSAGE;
	event->id = m_id;
	event->rfactory = net_createrfactory(m_net, (char*)memory, memory_size);
	net_addevent(m_net, event, 0);
}

} // ALittle
