
#ifndef _ALITTLE_CONNECTCLIENT_H_
#define _ALITTLE_CONNECTCLIENT_H_

#include <asio/asio.hpp>

#include <memory>
#include <functional>
#include <chrono>
#include <string>

struct _net;
struct _write_factory;

namespace ALittle
{

class ServerSchedule;
class ConnectClient;
typedef std::shared_ptr<ConnectClient> ConnectClientPtr;

typedef std::shared_ptr<asio::ip::tcp::socket> SocketPtr;

typedef unsigned int MESSAGE_SIZE;
typedef int MESSAGE_ID;
typedef int MESSAGE_RPCID;
#define PROTOCOL_HEAD_SIZE 12

class ConnectClient : public std::enable_shared_from_this<ConnectClient>
{
public:
	ConnectClient(_net* c, ServerSchedule* schedule, int id);
	~ConnectClient();

//连接部分/////////////////////////////////////////////////////////////////////////////////
public:
	/* 异步连接目标服务器
	 * @param route_id: 路由ID，全局唯一
	 * @param ip: 目标服务器IP
	 * @param port: 目标服务器端口
	 */
	void Connect(const std::string& ip, unsigned int port);

	// 判断是否已经连接
	bool IsConnected();

	// 是否正在连接
	bool IsConnecting();

	// 关闭连接
	void Close();

private:
	std::string m_ip;			// 目标服务器的IP
	unsigned int m_port;		// 目标服务器端口

public:
	// 获取目标服务器IP和端口
	const std::string& GetIP() const { return m_ip; }
	unsigned int GetPort() const { return m_port; }

private:
	// 异步连接
	void HandleAsyncConnect(const asio::error_code& ec);
	bool m_is_connecting;

private:
	// 处理断开连接
	void ExecuteDisconnectCallback();
	// 处理连接失败
	void HandleConnectFailed();
	// 处理连接成功
	void HandleConnectSucceed();
	// 处理断开连接
	void HandleDisconnected();
	// 处理消息包
	void HandleMessage(void* memory, int memory_size);

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
	char m_message_head[PROTOCOL_HEAD_SIZE];
	// 保存协议体
	void* m_memory;

//发送消息包部分/////////////////////////////////////////////////////////////////////////////////
public:
	// 发送消息包
	void Send(const _write_factory* message);

private:
	// 处理发送
	void SendPocket(void* memory, int memory_size);
	void NextSend();
	void HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory);

private:
	struct PocketInfo { int memory_size; void* memory; };
	std::list<PocketInfo> m_pocket_list;  // 待发送的数据包列表

	bool m_excuting;	// is in sending

private:
	ServerSchedule* m_schedule;
	_net* m_net;
	int m_id;
};

} // ALittle

#endif // _ALITTLE_CONNECTCLIENT_H_
