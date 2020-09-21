
#ifndef _ALITTLE_CONNECTCLIENT_H_
#define _ALITTLE_CONNECTCLIENT_H_

#include <asio.hpp>
#include "Carp/carp_message.hpp"
#include "RouteIdDefine.h"

#include "ConnectEndpoint.h"

#include <memory>
#include <functional>
#include <chrono>
#include <string>

namespace ALittle
{

class ConnectClient;
typedef std::shared_ptr<ConnectClient> ConnectClientPtr;

typedef std::shared_ptr<asio::ip::tcp::socket> SocketPtr;
typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class ConnectClient : public ConnectEndpoint
{
public:
	ConnectClient(RouteSystem* route_system);
	virtual ~ConnectClient();

//连接部分/////////////////////////////////////////////////////////////////////////////////
public:
	/* 异步连接目标服务器
	 * @param route_id: 路由ID，全局唯一
	 * @param ip: 目标服务器IP
	 * @param port: 目标服务器端口
	 * @param heartbeat_interval: 心跳间隔时间（秒）
	 * @param reconnect_interval: 重连的间隔时间（秒）
	 */
	void Connect(ROUTE_ID route_id
				, const std::string& ip, unsigned int port
				, int heartbeat_interval, int reconnect_interval);

	// 判断是否已经连接
	bool IsConnected();

	// 是否正在连接
	bool IsConnecting();

	// 关闭连接
	void Close(const std::string& reason);

private:
	std::string m_ip;			// 目标服务器的IP
	unsigned int m_port;		// 目标服务器端口
	int m_reconnect_interval;	// 重连间隔时间（秒）
	int m_heartbeat_interval;	// 心跳间隔时间（秒）

public:
	// 获取目标服务器IP和端口
	const std::string& GetIP() const { return m_ip; }
	unsigned int GetPort() const { return m_port; }

private:
	// 异步连接
	void HandleAsyncConnect(const asio::error_code& ec);
	bool m_is_connecting;

private:
	// 重连定时器
	void HandleReconnectTimer(const asio::error_code& ec);
	AsioTimerPtr m_reconnect_timer;	// reconnect timer
	
	// 心跳定时器
	void HandleHeartbeatTimer(const asio::error_code& ec);
	AsioTimerPtr m_heartbeat_timer;	// heatbeat timer

private:
	// 处理断开连接
	void ExecuteDisconnectCallback();

//读取消息包部分/////////////////////////////////////////////////////////////////////////////////
public:
	// 读取协议
	void NextReadHead();
	void HandleReadHead(const asio::error_code& ec, std::size_t actual_size);
	void HandleReadBody(const asio::error_code& ec, std::size_t actual_size);

private:
	// 处理协议
	void ReadComplete();

public:
	SocketPtr m_socket;					// socket

private:
	// 保存协议头
	char m_message_head[CARP_PROTOCOL_HEAD_SIZE];
	// 保存协议体
	void* m_memory;

//发送消息包部分/////////////////////////////////////////////////////////////////////////////////
public:
	// 发送消息包
	void Send(const CarpMessage& message);

private:
	// 处理发送
	void SendPocket(void* memory, int memory_size);
	void NextSend();
	void HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory);

private:
	struct PocketInfo { int memory_size; void* memory; };
	std::list<PocketInfo> m_pocket_list;  // 待发送的数据包列表

	bool m_excuting;	// is in sending
};

} // ALittle

#endif // _ALITTLE_CONNECTCLIENT_H_
