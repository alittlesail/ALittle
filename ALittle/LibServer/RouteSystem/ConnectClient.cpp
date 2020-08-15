
#include "ConnectClient.h"
#include "ConnectMessage.h"
#include "RouteDefine.h"
#include "RouteSystem.h"
#include "ALittle/LibServer/ServerSystem/ServerSchedule.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"

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
	// 关闭
	Close("route_id:" + ROUTE2S(m_route_id) + u8":ConnectClient调用析构函数的时候触发ClearRPC");
	// 释放内存
	if (m_memory) { free(m_memory); m_memory = 0; }
}

void ConnectClient::Connect(ROUTE_ID route_id
							, const std::string& ip, unsigned int port
							, int heartbeat_interval
							, int reconnect_interval)
{
	// 检查是否正在连接
	if (m_is_connecting)
	{
		ALITTLE_ERROR(u8"ConnectClient:Connect 正在连接的时候，不能再进行连接，" << "ip:" << ip << ", port:" << port);
		return;
	}

	// 先关闭
	Close(u8"ConnectClient:Connect 时调用Close触发ClearRPC");

	// 标记为正在连接
	m_is_connecting = true;
	// 保存断开重连的间隔时间
	m_reconnect_interval = reconnect_interval;
	// 保存心跳包的间隔时间
	m_heartbeat_interval = heartbeat_interval;
	// 创建一个socket对象
	m_socket = SocketPtr(new asio::ip::tcp::socket(m_route_system->GetSchedule()->GetIOService()));
	// 创建一个目标服务器的连接点
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::from_string(ip), port);

	// 保存并初始化
	m_ip = ip;
	m_port = port;
	m_route_id = route_id;
	m_target_route_id = 0;

	// 开始异步连接
	m_socket->async_connect(ep, std::bind(&ConnectEndpoint::HandleAsyncConnect, this->shared_from_this(), std::placeholders::_1));
}

void ConnectClient::HandleAsyncConnect(const asio::error_code& ec)
{
	if (ec)
	{
		// 这个日志不打印，因为会出现太多，又不重要
		// ALITTLE_SYSTEM(u8"ConnectClient 连接失败: " << SUTF8(asio::system_error(ec).what()) << ", ip:" << m_ip << ", port:" << m_port);
		
		// 处理连接失败
		HandleConnectFailed();

		// 打开重连计时器
		m_reconnect_timer = AsioTimerPtr(new AsioTimer(m_route_system->GetSchedule()->GetIOService(), std::chrono::seconds(m_reconnect_interval)));
		m_reconnect_timer->async_wait(std::bind(&ConnectEndpoint::HandleReconnectTimer, this->shared_from_this(), std::placeholders::_1));
		return;
	}
	// 设置 nodelay
	m_socket->set_option(asio::ip::tcp::no_delay(true));
	
	// 标记为不是正在发包
	m_excuting = false;
	// 标记为不是正在连接
	m_is_connecting = false;

	// 发送本端数据，进行注册锁定
	QConnectRegister msg;
	msg.route_id = m_route_id;
	Send(msg);

	// 开始接受消息包
	NextReadHead();

	// 创建心跳定时器
	m_heartbeat_timer = AsioTimerPtr(new AsioTimer(m_route_system->GetSchedule()->GetIOService(), std::chrono::seconds(m_heartbeat_interval)));
	m_heartbeat_timer->async_wait(std::bind(&ConnectEndpoint::HandleHeartbeatTimer, this->shared_from_this(), std::placeholders::_1));
	
	// 处理连接成功
	HandleConnectSucceed();
}

void ConnectClient::HandleReconnectTimer(const asio::error_code& ec)
{
	// 如果出现错误码，说明是主动取消定时器的
	if (ec == asio::error::operation_aborted) return;

	// 其他错误，一定要打印一下
	if (ec) ALITTLE_ERROR(u8"定时器出现未知的错误类型，一定要检查解决一下:" << SUTF8(ec.message().c_str()));

	// 关闭，释放
	Close("route_id:" + ROUTE2S(m_route_id) + u8":ConnectClient:HandleReconnectTimer 主动连接失败的时候调用Close，触发ClearRPC");

	// 重新开始连接
	Connect(m_route_id, m_ip, m_port, m_reconnect_interval, m_heartbeat_interval);
}

void ConnectClient::HandleHeartbeatTimer(const asio::error_code& ec)
{
	// 如果出现错误码，说明是主动取消定时器的
	if (ec == asio::error::operation_aborted) return;

	// 其他错误，一定要打印一下
	if (ec) ALITTLE_ERROR(u8"定时器出现未知的错误类型，一定要检查解决一下:" << SUTF8(ec.message().c_str()));

	// 发送心跳包
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
	// 释放带发送的消息包
	auto end = m_pocket_list.end();
	for (auto it = m_pocket_list.begin(); it != end; ++it)
		free(it->memory);
	m_pocket_list.clear();

	// 标记为不是正在发包
	m_excuting = false;
	// 标记为不是正在连接
	m_is_connecting = false;

	// 关闭重连定时器
	if (m_reconnect_timer)
	{
		asio::error_code ec;
		m_reconnect_timer->cancel(ec);
		m_reconnect_timer = AsioTimerPtr();
	}
	// 关闭心跳定时器
	if (m_heartbeat_timer)
	{
		asio::error_code ec;
		m_heartbeat_timer->cancel(ec);
		m_heartbeat_timer = AsioTimerPtr();
	}

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

	// 可靠性回调全部以调用失败处理
	ClearRPC(reason);
}

void ConnectClient::ExecuteDisconnectCallback()
{
	// 如果socket是空指针，那么肯定是主动调用Close引起的
	// 这个时候不属于断开连接，所以不要调用HandleDisconnected()
	bool close_by_self = (m_socket == SocketPtr());

	// 关闭，内部会把m_socket设置为空指针
	// 所以即使同时因为接收失败或者发送失败而触发的ExecuteDisconnectCallback也不会多次调用HandleDisconnected
	Close("route_id:" + ROUTE2S(m_route_id) + u8" ConnectClient:ExecuteDisconnectCallback 断开连接的时候调用Close，触发ClearRPC");

	// 如果不是自己关闭的，那么就调用回调
	if (close_by_self == false) HandleDisconnected();
}

void ConnectClient::NextReadHead()
{
	// 如果已经释放了就直接返回
	if (!m_socket) return;

	// 开始接受协议头
	asio::async_read(*m_socket, asio::buffer(m_message_head, sizeof(m_message_head))
					, std::bind(&ConnectEndpoint::HandleReadHead, this->shared_from_this()
					, std::placeholders::_1, std::placeholders::_2));
}

void ConnectClient::HandleReadHead(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存
		if (m_memory) { free(m_memory); m_memory = 0; }
		// 数据包接受失败，说明是断开连接了
		ALITTLE_SYSTEM("route_id:" + ROUTE2S(m_route_id) + u8" ConnectClient:HandleReadHead 消息包接收失败，连接断开了:" << SUTF8(ec.message().c_str()));
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
		, std::bind(&ConnectEndpoint::HandleReadBody, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void ConnectClient::HandleReadBody(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// 释放内存
		if (m_memory) { free(m_memory); m_memory = 0; }
		// 数据包接受失败，说明是断开连接了
		ALITTLE_INFO("route_id:" + ROUTE2S(m_route_id) + u8" ConnectClient:HandleReadBody 消息包接收失败:" << SUTF8(ec.message().c_str()));
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
	m_route_system->GetSchedule()->Execute(std::bind(&ConnectEndpoint::HandleMessage, this->shared_from_this(), m_memory, message_size + PROTOCOL_HEAD_SIZE));
	// 内存已经移交出去，HandleMessage会负责释放
	// 这里置0
	m_memory = 0;
}

void ConnectClient::Send(const Message& message)
{
	// 获取协议大小
	MESSAGE_SIZE message_size = message.GetTotalSize();
	// 获取协议ID
	MESSAGE_ID message_id = message.GetID();
	// 获取RPCID
	MESSAGE_RPCID message_rpcid = message.GetRpcID();

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
	message.Serialize(body_memory);

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
		, std::bind(&ConnectEndpoint::HandleSend, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2, info.memory));
}

void ConnectClient::HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory)
{
	// 释放内存
	if (memory) free(memory);

	// 检查错误
	if (ec)
	{
		// 发送失败说明断开连接了，但是这里不做通知，统一在读取那个位置进行通知
		ALITTLE_SYSTEM("route_id:" << ROUTE2S(m_route_id) + u8" ConnectClient:HandleSend 消息包发送失败:" << SUTF8(ec.message().c_str()));
		// 这里不通知断开连接，等待接受那部分通知断开
		ExecuteDisconnectCallback();
		return;
	}
	
	// 发送下一个包
	NextSend();
}

} // ALittle
