
#ifndef _ALITTLE_CONNECTCLIENT_H_
#define _ALITTLE_CONNECTCLIENT_H_

#include <asio/asio.hpp>
#include "ALittle/LibCommon/Protocol/Message.h"
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

//���Ӳ���/////////////////////////////////////////////////////////////////////////////////
public:
	/* �첽����Ŀ�������
	 * @param route_id: ·��ID��ȫ��Ψһ
	 * @param ip: Ŀ�������IP
	 * @param port: Ŀ��������˿�
	 * @param heartbeat_interval: �������ʱ�䣨�룩
	 * @param reconnect_interval: �����ļ��ʱ�䣨�룩
	 */
	void Connect(ROUTE_ID route_id
				, const std::string& ip, unsigned int port
				, int heartbeat_interval, int reconnect_interval);

	// �ж��Ƿ��Ѿ�����
	bool IsConnected();

	// �Ƿ���������
	bool IsConnecting();

	// �ر�����
	void Close(const std::string& reason);

private:
	std::string m_ip;			// Ŀ���������IP
	unsigned int m_port;		// Ŀ��������˿�
	int m_reconnect_interval;	// �������ʱ�䣨�룩
	int m_heartbeat_interval;	// �������ʱ�䣨�룩

public:
	// ��ȡĿ�������IP�Ͷ˿�
	const std::string& GetIP() const { return m_ip; }
	unsigned int GetPort() const { return m_port; }

private:
	// �첽����
	void HandleAsyncConnect(const asio::error_code& ec);
	bool m_is_connecting;

private:
	// ������ʱ��
	void HandleReconnectTimer(const asio::error_code& ec);
	AsioTimerPtr m_reconnect_timer;	// reconnect timer
	
	// ������ʱ��
	void HandleHeartbeatTimer(const asio::error_code& ec);
	AsioTimerPtr m_heartbeat_timer;	// heatbeat timer

private:
	// �����Ͽ�����
	void ExecuteDisconnectCallback();

//��ȡ��Ϣ������/////////////////////////////////////////////////////////////////////////////////
public:
	// ��ȡЭ��
	void NextReadHead();
	void HandleReadHead(const asio::error_code& ec, std::size_t actual_size);
	void HandleReadBody(const asio::error_code& ec, std::size_t actual_size);

private:
	// ����Э��
	void ReadComplete();

public:
	SocketPtr m_socket;					// socket

private:
	// ����Э��ͷ
	char m_message_head[PROTOCOL_HEAD_SIZE];
	// ����Э����
	void* m_memory;

//������Ϣ������/////////////////////////////////////////////////////////////////////////////////
public:
	// ������Ϣ��
	void Send(const Message& message);

private:
	// ��������
	void SendPocket(void* memory, int memory_size);
	void NextSend();
	void HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory);

private:
	struct PocketInfo { int memory_size; void* memory; };
	std::list<PocketInfo> m_pocket_list;  // �����͵����ݰ��б�

	bool m_excuting;	// is in sending
};

} // ALittle

#endif // _ALITTLE_CONNECTCLIENT_H_