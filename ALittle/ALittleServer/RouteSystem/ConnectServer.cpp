
#include "ConnectServer.h"
#include "ConnectReceiver.h"
#include "ConnectMessage.h"
#include "RouteDefine.h"
#include "RouteSystem.h"
#include "../ServerSystem/ServerSchedule.h"

#include "Carp/carp_log.hpp"

namespace ALittle
{

ConnectServer::ConnectServer()
: m_port(0), m_route_id(0), m_route_system(nullptr)
{
}

ConnectServer::~ConnectServer()
{
	Close();
}

bool ConnectServer::Start(ROUTE_ID route_id, const std::string& yun_ip, const std::string& ip, int port, int heartbeat, RouteSystem* route_system)
{
	m_route_system = route_system;

	// 检查是否已经创建了接收器
	if (m_acceptor)
	{
		CARP_ERROR(u8"ConnectServer 已经启动了，不能再启动(ip: " << m_ip << ", port:" << m_port << ")");
		return false;
	}

	// 创建监听器开始监听
	try
	{
		if (ip.size())
			m_acceptor = AcceptorPtr(new asio::ip::tcp::acceptor(route_system->GetSchedule()->GetIOService()
			, asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(ip), port), false));
		else
			m_acceptor = AcceptorPtr(new asio::ip::tcp::acceptor(route_system->GetSchedule()->GetIOService()
			, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port), false));
	}
	catch (asio::error_code& ec)
	{
		m_acceptor = AcceptorPtr();
		CARP_ERROR("ConnectServer: " << ip << u8" 启动失败 at port: " << port << " error: " << ec.value());
		return false;
	}

	// 创建心跳定时器
	m_heartbeat_timer = AsioTimerPtr(new AsioTimer(route_system->GetSchedule()->GetIOService(), std::chrono::seconds(heartbeat)));
	m_heartbeat_timer->async_wait(std::bind(&ConnectServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1, heartbeat));

	// 准备接受下一个连接请求
	NextAccept(0);

	// 保存参数
    m_yun_ip = yun_ip;
	m_ip = ip;
	m_port = port;
	m_route_id = route_id;
	
	// 打印一下
	CARP_SYSTEM("ConnectServer: start succeed, " << "route_id:" << ROUTE2S(m_route_id) << " at " << m_ip << ":" << m_port);
	return true;
}

void ConnectServer::Close()
{
	// 关闭和释放接收器
	if (m_acceptor)
	{
		asio::error_code ec;
		m_acceptor->close(ec);
		m_acceptor = AcceptorPtr();
	}

	// 释放定时器
	if (m_heartbeat_timer)
	{
		asio::error_code ec;
		m_heartbeat_timer->cancel(ec);
		m_heartbeat_timer = AsioTimerPtr();
	}

	// 主动关闭所有连接
	for (auto it = m_outer_set.begin(); it != m_outer_set.end(); ++it)
		(*it)->Close(u8"ConnectServer::Close调用");

	// 清除连接集合
	m_outer_set.clear();

	// 打印一下
	CARP_SYSTEM("ConnectServer: stop succeed, " << " route_id:" << ROUTE2S(m_route_id) << " at " << m_ip << ":" << m_port);
}

void ConnectServer::NextAccept(int error_count)
{
	// 判断一下接收器是否已经被释放
	if (!m_acceptor) return;

	// 创建一个socket
	SocketPtr socket = SocketPtr(new asio::ip::tcp::socket(m_route_system->GetSchedule()->GetIOService()));
	// 开始异步接收
	m_acceptor->async_accept(*socket, std::bind(&ConnectServer::HandleAccept, this->shared_from_this(), std::placeholders::_1, socket, error_count));
}

void ConnectServer::HandleAccept(const asio::error_code& ec, SocketPtr socket, int error_count)
{
	if (ec)
	{
		// 这个错误一般不容易出现。
		// 目前发现的是，1.主动修改服务器的ip会触发这个异常  2.服务器刚刚启动网络模块还没有初始化好
		CARP_ERROR("route_id:" + ROUTE2S(m_route_id) + " ConnectServer accept failed: " << ec.value());
		if (error_count > 100)
			Close();
		else
			NextAccept(error_count + 1);
		return;
	}
	// 设置一下不延时
	socket->set_option(asio::ip::tcp::no_delay(true));

	// 调用回调通知有新的连接
	HandleOuterConnect(socket);
	
	// 准备接受下一个连接
	NextAccept(0);
}

void ConnectServer::HandleOuterConnect(SocketPtr socket)
{
	// 创建接收器
	ConnectEndpointPtr receiver = ConnectReceiverPtr(new ConnectReceiver(socket, this->shared_from_this(), m_route_id, m_route_system));
	// 保存接收器
	m_outer_set.insert(receiver);
	// 开始读取数据包
	receiver->NextReadHead();
}

void ConnectServer::HandleOuterDisconnected(ConnectEndpointPtr receiver)
{
	// 通知断开了连接
	receiver->HandleDisconnected();
	// 关闭连接，清理数据
	receiver->Close("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver断开连接，调用close，出发ClearRPC");
	// 从集合中移除
	m_outer_set.erase(receiver);
}

void ConnectServer::ServerSendHeatbeat(const asio::error_code& ec, int interval)
{
	// 如果出现错误码，说明是主动取消定时器的
	if (ec == asio::error::operation_aborted) return;

	// 其他错误，一定要打印一下
	if (ec) CARP_ERROR(u8"定时器出现未知的错误类型，一定要检查解决一下:" << ec.value());

	HeartbeatMessage msg;
	for (auto it = m_outer_set.begin(); it != m_outer_set.end(); ++it)
		(*it)->Send(msg);

	if (!m_heartbeat_timer) return;
	m_heartbeat_timer->expires_at(std::chrono::system_clock::now() + std::chrono::seconds(interval));
	m_heartbeat_timer->async_wait(std::bind(&ConnectServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1, interval));
}

} // ALittle
