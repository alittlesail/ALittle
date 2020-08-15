
#ifndef _ALITTLE_CLIENTSERVER_H_
#define _ALITTLE_CLIENTSERVER_H_

#include <asio/asio.hpp>
#include "ALittle/LibCommon/Protocol/Message.h"

#include <map>
#include <string>
#include <memory>
#include <chrono>

namespace ALittle
{

class ClientReceiver;
typedef std::shared_ptr<ClientReceiver> ClientReceiverPtr;
typedef std::weak_ptr<ClientReceiver> ClientReceiverWeakPtr;

class ClientServer;
typedef std::shared_ptr<ClientServer> ClientServerPtr;
typedef std::weak_ptr<ClientServer> ClientServerWeakPtr;

typedef std::shared_ptr<asio::ip::tcp::socket> SocketPtr;
typedef std::shared_ptr<asio::ip::tcp::acceptor> AcceptorPtr;
typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class ServerSchedule;

class ClientServer : public std::enable_shared_from_this<ClientServer>
{
public:
	friend ClientReceiver;

public:
	// 启动服务器
    // yun_ip 云服务器的映射ip
	// ip	服务器的IP
	// port 服务器的端口
	// heartbeat TCP心跳包保活间隔时间，单位秒
	bool Start(const std::string& yun_ip, const std::string& ip, int port, int heartbeat, ServerSchedule* schedule);

	// 关闭服务器
	void Close();

private:
	// 等待下一个socket接入
	void NextAccept(int error_count);

	// 处理新的socket接入
	void HandleAccept(const asio::error_code& ec, SocketPtr socket, int error_count);

public:
	// 获取本地的服务器ip和端口
    const std::string& GetYunIp() const { return m_yun_ip; }
	const std::string& GetIp() const { return m_ip; }
	int GetPort() const { return m_port; }

private:
	AcceptorPtr m_acceptor;		// 接收器，用于接收新的socket
    std::string m_yun_ip;       // 云服务器对外的IP
	std::string m_ip;			// 本地服务器的IP
	int m_port;					// 本地服务器的端口

///////////////////////////////////////////////////////////////////////////////////////////////
	
private:
	// 处理一个新的socket
	void HandleOuterConnect(SocketPtr socket);

	// 处理某个连接断开了
	void HandleOuterDisconnected(ClientReceiverPtr receiver);

public:
	// 处理消息事件
	void HandleClientMessage(ClientReceiverPtr receiver, MESSAGE_SIZE message_size, MESSAGE_ID message_id, MESSAGE_RPCID message_rpcid, void* memory);
	
private:
	// 保存客户端连接对象
	std::set<ClientReceiverPtr> m_outer_set;	// container outer
	ServerSchedule* m_schedule;

private:
	// 服务器间隔一定时间向客户端发送心跳包
	void ServerSendHeatbeat(const asio::error_code& ec, int interval);
	// 心跳包定时器
	AsioTimerPtr m_heartbeat_timer;

public:
	ClientServer();
	~ClientServer();
};

} // ALittle

#endif // _ALITTLE_CLIENTSERVER_H_
