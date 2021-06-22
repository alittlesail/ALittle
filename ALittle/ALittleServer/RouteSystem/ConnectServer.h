
#ifndef _ALITTLE_CONNECTSERVER_H_
#define _ALITTLE_CONNECTSERVER_H_

#include <asio.hpp>
#include "Carp/carp_message.hpp"
#include "RouteIdDefine.h"

#include <string>
#include <memory>
#include <chrono>

namespace ALittle
{

class ConnectReceiver;
typedef std::shared_ptr<ConnectReceiver> ConnectReceiverPtr;
typedef std::weak_ptr<ConnectReceiver> ConnectReceiverWeakPtr;
class ConnectEndpoint;
typedef std::shared_ptr<ConnectEndpoint> ConnectEndpointPtr;
typedef std::weak_ptr<ConnectEndpoint> ConnectEndpointWeakPtr;

typedef std::shared_ptr<asio::ip::tcp::socket> SocketPtr;
typedef std::shared_ptr<asio::ip::tcp::acceptor> AcceptorPtr;
typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class RouteSystem;

class ConnectServer : public std::enable_shared_from_this<ConnectServer>
{
public:
	friend ConnectReceiver;

public:
	/* 路由服务器
     * @param route_id: 服务器路由ID
     * @param yun_ip: 云服务对外的IP
	 * @param ip: 本端的服务器IP
	 * @param port: 本端的服务器端口
	 * @param heartbeat: 心跳包间隔时间（秒）
	 * @return succeed or not
	 */
	bool Start(ROUTE_ID route_id, const std::string& yun_ip, const std::string& ip, int port, int heartbeat, RouteSystem* route_system);

	// 关闭服务器
	void Close();

private:
	// 等待接收下一个socket
	void NextAccept(int error_count);

	// 处理新的socket连接
	void HandleAccept(const asio::error_code& ec, SocketPtr socket, int error_count);

private:
	AcceptorPtr m_acceptor;		// 接收器
    std::string m_yun_ip;       // 云服务器的ip
	std::string m_ip;			// 本端的ip
	int m_port;					// 本端的端口

private:
	ROUTE_ID m_route_id;	// 路由ID

///////////////////////////////////////////////////////////////////////////////////////////////
	
private:
	// 处理新的连接
	void HandleOuterConnect(SocketPtr socket);

	// 处理连接断开
	void HandleOuterDisconnected(ConnectEndpointPtr receiver);
	
private:
	std::set<ConnectEndpointPtr> m_outer_set;	// 连接集合

private:
	// 定时发送心跳包
	void ServerSendHeatbeat(const asio::error_code& ec, int interval);
	AsioTimerPtr m_heartbeat_timer;	// 心跳包定时器
	RouteSystem* m_route_system;

public:
	ConnectServer();
	~ConnectServer();
};

} // ALittle

#endif // _ALITTLE_CONNECTSERVER_H_
