
#ifndef _ALITTLE_CONNECTRECEIVER_H_
#define _ALITTLE_CONNECTRECEIVER_H_

#include <asio.hpp>
#include "Carp/carp_message.hpp"
#include "RouteIdDefine.h"

#include "ConnectEndpoint.h"

#include <memory>

namespace ALittle
{

class ConnectServer;
typedef std::shared_ptr<ConnectServer> ConnectServerPtr;
typedef std::weak_ptr<ConnectServer> ConnectServerWeakPtr;

typedef std::shared_ptr<asio::ip::tcp::socket> SocketPtr;
typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class ConnectReceiver : public ConnectEndpoint
{
public:
	ConnectReceiver(SocketPtr socket, ConnectServerWeakPtr server, ROUTE_ID route_id, RouteSystem* route_system);
	virtual ~ConnectReceiver();

	friend class ConnectServer;
	
public:
	// �ر�����
	void Close(const std::string& reason, int delay_second=0) override;
	bool IsConnected() override { return m_is_connected; }

private:
	void NextReadHead() override;
	void HandleReadHead(const asio::error_code& ec, std::size_t actual_size) override;
	void HandleReadBody(const asio::error_code& ec, std::size_t actual_size) override;

private:
	void CloseImpl(const std::string& reason);
	void ReadComplete();

public:
	const std::string& GetIP() const override { return m_remote_ip; }
	unsigned int GetPort() const override { return m_remote_port; }

private:
	// ��ʱclose��ʱ��
	void HandleDelayCloseTimer(const asio::error_code& ec, const std::string& reason) override;
	AsioTimerPtr m_delay_close_timer;	// close timer

private:
	SocketPtr m_socket;				// socket
	std::string m_remote_ip;		// �Է���ip
	int m_remote_port;				// �Է��Ķ˿�

protected:
	ConnectServerWeakPtr m_server;	// �����ķ�����
	
private:
	// ����Э��ͷ
	char m_message_head[CARP_PROTOCOL_HEAD_SIZE];
	// ����Э����
	void* m_memory;

///////////////////////////////////////////////////////////////////////////////////

public:
	void Send(const CarpMessage& message) override;
	void SendPocket(void* memory, int memory_size) override;

private:
	void NextSend();
	void HandleSend(const asio::error_code& ec, std::size_t bytes_transferred, void* memory) override;

private:
	struct PocketInfo { int memory_size; void* memory; };
	typedef std::list<PocketInfo> PocketList;	// pocket list
	PocketList m_pocket_list;

	bool m_excuting;		// is in sending
	bool m_is_connected;	// is connected
};

} // ALittle

#endif // _ALITTLE_CONNECTRECEIVER_H_
