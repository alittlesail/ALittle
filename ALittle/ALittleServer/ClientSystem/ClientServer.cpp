
#include "ClientReceiver.h"
#include "ClientServer.h"

#include "Carp/carp_log.hpp"
#include "../ServerSystem/ServerSchedule.h"

namespace ALittle
{

ClientServer::ClientServer()
: m_port(0), m_schedule(nullptr)
{
}

ClientServer::~ClientServer()
{
	Close();
}

bool ClientServer::Start(const std::string& yun_ip, const std::string& ip, int port, int heartbeat, ServerSchedule* schedule)
{
	m_schedule = schedule;

	// 如果已经开启了就直接返回
	if (m_acceptor)
	{
		CARP_ERROR("Client server already started(ip: " << m_ip << ", port:" << m_port << ")");
		return false;
	}

	// 创建一个接收器，并启动
	try
	{
		if (ip.size())
			m_acceptor = AcceptorPtr(new asio::ip::tcp::acceptor(schedule->GetIOService()
			, asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(ip), port), false));
		else
			m_acceptor = AcceptorPtr(new asio::ip::tcp::acceptor(schedule->GetIOService()
			, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port), false));
	}
	catch (asio::error_code& ec)
	{
		m_acceptor = AcceptorPtr();
		CARP_ERROR("ClientServer: " << ip << " start failed at port: " << port << " error: " << ec.value());
		return false;
	}

	// 创建定时器i
	m_heartbeat_timer = AsioTimerPtr(new AsioTimer(schedule->GetIOService(), std::chrono::seconds(heartbeat)));
	m_heartbeat_timer->async_wait(std::bind(&ClientServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1, heartbeat));

	// 开始接受
	NextAccept(0);

    m_yun_ip = yun_ip;
	m_ip = ip;
	m_port = port;
	
	CARP_SYSTEM("ClientServer: start succeed at " << m_ip << ":" << m_port);
	return true;
}

void ClientServer::Close()
{
	// 关闭并释放接收器
	if (m_acceptor)
	{
		m_acceptor->close();
		m_acceptor = AcceptorPtr();
	}

	// 释放定时器
	if (m_heartbeat_timer)
	{
		m_heartbeat_timer->cancel();
		m_heartbeat_timer = AsioTimerPtr();
	}

	// 关闭所有客户端连接
	auto end = m_outer_set.end();
	for (auto it = m_outer_set.begin(); it != end; ++it)
		(*it)->Close();
	m_outer_set.clear();

	CARP_SYSTEM("ClientServer: stop succeed.");
}

void ClientServer::NextAccept(int error_count)
{
	// 检查接收器是否合法
	if (!m_acceptor) return;

	// 创建一个Socket对象
	SocketPtr socket = SocketPtr(new asio::ip::tcp::socket(m_schedule->GetIOService()));
	// 开始等待接收
	m_acceptor->async_accept(*socket, std::bind(&ClientServer::HandleAccept, this->shared_from_this()
        , std::placeholders::_1, socket, error_count));
}

void ClientServer::HandleAccept(const asio::error_code& ec, SocketPtr socket, int error_count)
{
	if (ec)
	{
		CARP_ERROR("ClientServer accept failed: " << ec.value());
		if (error_count > 100)
			Close();
		else
			NextAccept(error_count + 1);
		return;
	}
	// 设置为no delay
	socket->set_option(asio::ip::tcp::no_delay(true));

	// 处理新的socket
	HandleOuterConnect(socket);
	
	// 接收下一个连接
	NextAccept(0);
}

void ClientServer::HandleOuterConnect(SocketPtr socket)
{
	// 创建一个客户端连接
	ClientReceiverPtr receiver = ClientReceiverPtr(new ClientReceiver(socket, this->shared_from_this(), m_schedule));
	// 保存起来
	m_outer_set.insert(receiver);

	// 客户端连接马上开始接受数据包
	receiver->NextReadHeadFirst();

	// 通知客户端连接进来了
	m_schedule->HandleClientConnect(receiver);
}

void ClientServer::HandleOuterDisconnected(ClientReceiverPtr receiver)
{
	// 关闭并移除客户端连接
	receiver->Close();
	m_outer_set.erase(receiver);

	// 通知断开连接
	m_schedule->HandleClientDisconnect(receiver);
}

void ClientServer::HandleClientMessage(ClientReceiverPtr receiver, CARP_MESSAGE_SIZE message_size, CARP_MESSAGE_ID message_id, CARP_MESSAGE_RPCID message_rpcid, void* memory)
{
	// 通知处理消息包
	m_schedule->HandleClientMessage(receiver, message_size, message_id, message_rpcid, memory);
	// 释放内存
	if (memory) free(memory);
}

void ClientServer::ServerSendHeatbeat(const asio::error_code& ec, int interval)
{
	// 向所有客户端发送心跳包
	HeartbeatMessage msg;
	auto end = m_outer_set.end();
	for (auto it = m_outer_set.begin(); it != end; ++it)
		(*it)->Send(msg);

	if (!m_heartbeat_timer) return;
	m_heartbeat_timer->expires_at(std::chrono::system_clock::now() + std::chrono::seconds(interval));
	m_heartbeat_timer->async_wait(std::bind(&ClientServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1, interval));
}

} // ALittle
