
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
	/* ·�ɷ�����
     * @param route_id: ������·��ID
     * @param yun_ip: �Ʒ�������IP
	 * @param ip: ���˵ķ�����IP
	 * @param port: ���˵ķ������˿�
	 * @param heartbeat: ���������ʱ�䣨�룩
	 * @return succeed or not
	 */
	bool Start(ROUTE_ID route_id, const std::string& yun_ip, const std::string& ip, int port, int heartbeat, RouteSystem* route_system);

	// �رշ�����
	void Close();

private:
	// �ȴ�������һ��socket
	void NextAccept(int error_count);

	// �����µ�socket����
	void HandleAccept(const asio::error_code& ec, SocketPtr socket, int error_count);

private:
	AcceptorPtr m_acceptor;		// ������
    std::string m_yun_ip;       // �Ʒ�������ip
	std::string m_ip;			// ���˵�ip
	int m_port;					// ���˵Ķ˿�

private:
	ROUTE_ID m_route_id;	// ·��ID

///////////////////////////////////////////////////////////////////////////////////////////////
	
private:
	// �����µ�����
	void HandleOuterConnect(SocketPtr socket);

	// �������ӶϿ�
	void HandleOuterDisconnected(ConnectEndpointPtr receiver);
	
private:
	std::set<ConnectEndpointPtr> m_outer_set;	// ���Ӽ���

private:
	// ��ʱ����������
	void ServerSendHeatbeat(const asio::error_code& ec, int interval);
	AsioTimerPtr m_heartbeat_timer;	// ��������ʱ��
	RouteSystem* m_route_system;

public:
	ConnectServer();
	~ConnectServer();
};

} // ALittle

#endif // _ALITTLE_CONNECTSERVER_H_
