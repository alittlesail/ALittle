
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

	// ����Ƿ��Ѿ������˽�����
	if (m_acceptor)
	{
		CARP_ERROR(u8"ConnectServer �Ѿ������ˣ�����������(ip: " << m_ip << ", port:" << m_port << ")");
		return false;
	}

	// ������������ʼ����
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
		CARP_ERROR("ConnectServer: " << ip << u8" ����ʧ�� at port: " << port << " error: " << ec.value());
		return false;
	}

	// ����������ʱ��
	m_heartbeat_timer = AsioTimerPtr(new AsioTimer(route_system->GetSchedule()->GetIOService(), std::chrono::seconds(heartbeat)));
	m_heartbeat_timer->async_wait(std::bind(&ConnectServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1, heartbeat));

	// ׼��������һ����������
	NextAccept(0);

	// �������
    m_yun_ip = yun_ip;
	m_ip = ip;
	m_port = port;
	m_route_id = route_id;
	
	// ��ӡһ��
	CARP_SYSTEM("ConnectServer: start succeed, " << "route_id:" << ROUTE2S(m_route_id) << " at " << m_ip << ":" << m_port);
	return true;
}

void ConnectServer::Close()
{
	// �رպ��ͷŽ�����
	if (m_acceptor)
	{
		asio::error_code ec;
		m_acceptor->close(ec);
		m_acceptor = AcceptorPtr();
	}

	// �ͷŶ�ʱ��
	if (m_heartbeat_timer)
	{
		asio::error_code ec;
		m_heartbeat_timer->cancel(ec);
		m_heartbeat_timer = AsioTimerPtr();
	}

	// ��ΪClose�ڲ������RemoveReceiver����RemoveReceiver�ڲ����m_outer_set���в���������������һ��
	std::set<ConnectEndpointPtr> copy_set = m_outer_set;
	for (auto it = copy_set.begin(); it != copy_set.end(); ++it)
		(*it)->Close(u8"ConnectServer::Close����");
	// ������Ӽ���
	m_outer_set.clear();

	// ��ӡһ��
	CARP_SYSTEM("ConnectServer: stop succeed, " << " route_id:" << ROUTE2S(m_route_id) << " at " << m_ip << ":" << m_port);
}

void ConnectServer::NextAccept(int error_count)
{
	// �ж�һ�½������Ƿ��Ѿ����ͷ�
	if (!m_acceptor) return;

	// ����һ��socket
	SocketPtr socket = SocketPtr(new asio::ip::tcp::socket(m_route_system->GetSchedule()->GetIOService()));
	// ��ʼ�첽����
	m_acceptor->async_accept(*socket, std::bind(&ConnectServer::HandleAccept, this->shared_from_this(), std::placeholders::_1, socket, error_count));
}

void ConnectServer::HandleAccept(const asio::error_code& ec, SocketPtr socket, int error_count)
{
	if (ec)
	{
		// �������һ�㲻���׳��֡�
		// Ŀǰ���ֵ��ǣ�1.�����޸ķ�������ip�ᴥ������쳣  2.�������ո���������ģ�黹û�г�ʼ����
		CARP_ERROR("route_id:" + ROUTE2S(m_route_id) + " ConnectServer accept failed: " << ec.value());
		if (error_count > 100)
			Close();
		else
			NextAccept(error_count + 1);
		return;
	}
	// ����һ�²���ʱ
	socket->set_option(asio::ip::tcp::no_delay(true));

	// ���ûص�֪ͨ���µ�����
	HandleOuterConnect(socket);
	
	// ׼��������һ������
	NextAccept(0);
}

void ConnectServer::HandleOuterConnect(SocketPtr socket)
{
	// ����������
	ConnectEndpointPtr receiver = ConnectReceiverPtr(new ConnectReceiver(socket, this->shared_from_this(), m_route_id, m_route_system));
	// ���������
	m_outer_set.insert(receiver);
	// ��ʼ��ȡ���ݰ�
	receiver->NextReadHead();
}

void ConnectServer::HandleOuterDisconnected(ConnectEndpointPtr receiver)
{
	// ֪ͨ�Ͽ�������
	receiver->HandleDisconnected();
	// �ر����ӣ���������
	receiver->Close("route_id:" + ROUTE2S(m_route_id) + u8" ConnectReceiver�Ͽ����ӣ�����close������ClearRPC");
	// ��Ϊreceiver->Close�ڲ��Ѿ�������ConnectServer::RemoveReceiver���������ﲻ��Ҫ�ٵ����Ƴ�
	// ����ע�ͣ���ʾ˵��
	// m_outer_set.erase(receiver);
}

void ConnectServer::RemoveReceiver(ConnectEndpointPtr receiver)
{
	// �Ӽ������Ƴ�
	m_outer_set.erase(receiver);
}

void ConnectServer::ServerSendHeatbeat(const asio::error_code& ec, int interval)
{
	// ������ִ����룬˵��������ȡ����ʱ����
	if (ec == asio::error::operation_aborted) return;

	// ��������һ��Ҫ��ӡһ��
	if (ec) CARP_ERROR(u8"��ʱ������δ֪�Ĵ������ͣ�һ��Ҫ�����һ��:" << ec.value());

	HeartbeatMessage msg;
	for (auto it = m_outer_set.begin(); it != m_outer_set.end(); ++it)
		(*it)->Send(msg);

	if (!m_heartbeat_timer) return;
	m_heartbeat_timer->expires_at(std::chrono::system_clock::now() + std::chrono::seconds(interval));
	m_heartbeat_timer->async_wait(std::bind(&ConnectServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1, interval));
}

} // ALittle
