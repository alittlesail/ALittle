
#ifndef _ALITTLE_CLIENTRECEIVER_H_
#define _ALITTLE_CLIENTRECEIVER_H_

#include <asio/asio.hpp>
#include "ALittle/LibCommon/Protocol/Message.h"
#include <memory>


namespace ALittle
{

class ClientServer;
typedef std::shared_ptr<ClientServer> ClientServerPtr;
typedef std::weak_ptr<ClientServer> ClientServerWeakPtr;

typedef std::shared_ptr<asio::ip::tcp::socket> SocketPtr;

class ServerSchedule;

class ClientReceiver : public std::enable_shared_from_this<ClientReceiver>
{
public:
	ClientReceiver(SocketPtr socket, ClientServerWeakPtr server, ServerSchedule* schedule);
	~ClientReceiver();

	friend class ClientServer;

public:
	// 关闭连接，释放内存
	void Close();

//接受部分/////////////////////////////////////////////////////////////////////////////////

private:
	void NextReadHeadFirst();
	void HandleReadHeadFirst(const asio::error_code& ec, std::size_t actual_size);

private:
	// 读取协议
	void NextReadHeadBinary();
	void HandleReadHeadBinary(const asio::error_code& ec, std::size_t actual_size);
	void HandleReadBodyBinary(const asio::error_code& ec, std::size_t actual_size);

private:
	void NextReadWebSocketHandShake();
	void HandleWebSocketHandShakeReceive(const asio::error_code& ec, std::size_t actual_size);
	void HandleWebSocketHandShakeSend(const asio::error_code& ec, std::size_t actual_size);

private:
	void NextWebSocketRead1();
	void HandleNextWebSocketRead1(const asio::error_code& ec, std::size_t actual_size);
	void NextWebSocketRead2(int payload_len);
	void HandleNextWebSocketRead2(const asio::error_code& ec, std::size_t actual_size);
	void NextWebSocketReadMark();
	void HandleNextWebSocketReadMark(const asio::error_code& ec, std::size_t actual_size);
	void NextWebSocketReadData();
	void HandleNextWebSocketReadData(const asio::error_code& ec, std::size_t actual_size);
	void HandleWebSocketReadData(int total_size, int offset);
	void ReleaseWebSocketBuffer();

private:
	bool m_is_websocket;
	void* m_websocket_buffer;		// web socket buffer
	std::string m_websocket_handshake;	// websocket hand shake string
	char m_frame_buffer[8];				// frame buffer

	bool m_has_mark;				// has mark
	char m_mark[4];					// mark
	int m_opcode;					// opcode
	int m_data_length;				// data length

	int m_head_size;				// head size received
	int m_body_size;				// body size received
	bool m_current_is_message;		// current is message
//======================================================================================

private:
	// 处理协议
	void ReadComplete();

public:
	// 读取客户端的公网IP和端口
	const std::string& GetRemoteIP() const { return m_remote_ip; }
	int GetRemotePort() const { return m_remote_port; }
	bool IsConnected() const { return m_is_connected; }

private:
	SocketPtr m_socket;				// Socket
	std::string m_remote_ip;		// 客户端的公网IP
	int m_remote_port;				// 客户端的公网端口

private:
	// 协议头
	char m_message_head[PROTOCOL_HEAD_SIZE];
	// 协议体
	void* m_memory;
	// 归属的服务器
	ClientServerWeakPtr m_server;
	// 对应调用模块
	ServerSchedule* m_schedule;

//发送部分/////////////////////////////////////////////////////////////////////////////////

public:
	// 发送协议
	void Send(const Message& message);

private:
	void SendBinary(const Message& message);
	void SendWebSocket(const Message& message);

private:
	// 处理发送
	void SendPocket(void* memory, int memory_size);
	void NextSend();
	void HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory);

private:
	struct PocketInfo { int memory_size; void* memory; };
	std::list<PocketInfo> m_pocket_list; // 待发送的数据包列表

	bool m_excuting;	// 是否正在发送
	bool m_is_connected;// 是否处于连接状态
};

} // ALittle

#endif // _ALITTLE_CLIENTRECEIVER_H_
