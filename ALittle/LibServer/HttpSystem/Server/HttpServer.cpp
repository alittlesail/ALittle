
#include "HttpServer.h"
#include "HttpReceiver.h"
#include "HttpSender.h"

#define CARP_HAS_SSL
#include "Carp/carp_http.hpp"

#include "ALittle/LibServer/ServerSystem/ServerSchedule.h"

namespace ALittle
{

HttpServer::HttpServer()
: m_port(0), m_heartbeat_interval(30)
, m_context(asio::ssl::context::sslv23), m_is_ssl(false), m_schedule(nullptr)
{
}

HttpServer::~HttpServer()
{
	Close();
}

std::string HttpServer::GetPemPassword() const
{
	return m_pem_password;
}

bool HttpServer::Start(const std::string& yun_ip, const std::string& ip, unsigned int port, int heartbeat, bool is_ssl, ServerSchedule* schedule
							  , const std::string& server_pem_path, const std::string& private_key_path, const std::string& pem_password)
{
	m_schedule = schedule;

	// check is already started
	if (m_acceptor)
	{
		CARP_ERROR("http server already started(ip: " << m_ip << ", port:" << m_port << ")");
		return false;
	}

	try
	{
		if (is_ssl)
		{
			if (server_pem_path.size())
				m_pem_password = pem_password;
			else
				m_pem_password = "test";

			m_context.set_options(asio::ssl::context::default_workarounds | asio::ssl::context::no_sslv2 | asio::ssl::context::single_dh_use);
			m_context.set_password_callback(std::bind(&HttpServer::GetPemPassword, this->shared_from_this()));

			// if pem_path is empty
			if (server_pem_path.size())
			{
				// init context
				m_context.use_certificate_chain_file(server_pem_path);
				m_context.use_private_key_file(private_key_path, asio::ssl::context::pem);
			}
			else
			{
				// init context
				std::string dh512_pem = "Diffie-Hellman-Parameters: (512 bit)\n"
					"    prime:\n"
					"        00:a0:bc:d0:c2:c3:a8:c7:a5:62:13:cd:f0:63:39:\n"
					"        ea:85:e0:f7:ca:00:8a:57:ec:12:dd:92:2b:20:70:\n"
					"        38:6c:03:60:b1:19:e3:0b:e9:d3:05:f1:1b:cc:8c:\n"
					"        9c:1a:30:3e:91:de:db:17:a7:19:cf:da:a0:2d:ee:\n"
					"        ef:35:95:8b:4b\n"
					"    generator: 5 (0x5)\n"
					"-----BEGIN DH PARAMETERS-----\n"
					"MEYCQQCgvNDCw6jHpWITzfBjOeqF4PfKAIpX7BLdkisgcDhsA2CxGeML6dMF8RvM\n"
					"jJwaMD6R3tsXpxnP2qAt7u81lYtLAgEF\n"
					"-----END DH PARAMETERS-----";
				std::string server_pem = "-----BEGIN CERTIFICATE-----\n"
					"MIIB/jCCAWcCCQDlADUqOr8YCTANBgkqhkiG9w0BAQUFADA7MQswCQYDVQQGEwJB\n"
					"VTEMMAoGA1UECBMDTlNXMQ8wDQYDVQQHEwZTeWRuZXkxDTALBgNVBAoTBGFzaW8w\n"
					"HhcNMDUxMTAyMTk1MjMzWhcNMTUxMTAyMTk1MjMzWjBMMQswCQYDVQQGEwJBVTEM\n"
					"MAoGA1UECBMDTlNXMQ8wDQYDVQQHEwZTeWRuZXkxDTALBgNVBAoTBGFzaW8xDzAN\n"
					"BgNVBAsTBnNlcnZlcjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAxAkg4iw5\n"
					"X8pXhJ8GfjGRKVOClt/EI9ypQMqWQSRH0pGDFlIOQzsfhqsCyp/xcfCwPBvfMIeE\n"
					"IzYiZ5kH6YD9EfHmIA6hsd1i3layCpeiA2VXrUXsvL8Y3fUt1/3IAR+pmVI4XGas\n"
					"lCb0zs1n0K08v9AWBkVE5rirA5an263Sd+kCAwEAATANBgkqhkiG9w0BAQUFAAOB\n"
					"gQBzFX/efrhGVzfK4Ue+/7Og44r7OLzQepSyQavFhp+t3PX1hy4ifneTnqMyME8w\n"
					"WuB94G/gtST9ECVHRKUuBn4xT1rz5DO20h3VSAzTirkSFQPdWunyBbIva0Hsf6pF\n"
					"287CA1cM106X0Vs4dv2F2u0zSszYfOysAM1pIPcxdyboXA==\n"
					"-----END CERTIFICATE-----\n"
					"-----BEGIN RSA PRIVATE KEY-----\n"
					"Proc-Type: 4,ENCRYPTED\n"
					"DEK-Info: DES-EDE3-CBC,9A7CF9C13224C492\n"
					"\n"
					"w00sJ2/d79LRI+9LRsnQkBZwIo/NbprFtN3SVqcUAtncqowl9BnKZnQ2csnj8KZA\n"
					"STAL+PZAyJQTiJfJxecCkB8Tu4/apFe2V9/PxUirJzGtJ9FHBAjLgmpK4yWwSCMq\n"
					"txyy8hjm8ggR8SQNJ1Jf+O6uGotillq02TJ0RluRrhukkfevClXTfCl3ngGI3D1q\n"
					"v5dFZrU2r2pGpkxCxI8SoQCCaH6l/plR9IhKl1/cz9chiXUFmAb4kMazneZaFmiu\n"
					"B8AJMQcFDfKttdKmkxY1qdQI9bOKw2YSZT6aASZTHD84hDloQRdgok8VO1YBKfzj\n"
					"0jEYnaYuXZGD+h38giABPV0iTY7aC0RdcyP63ZQH95KXtSLGBfUHEOvR4jR4uLu9\n"
					"3Qfw4j1/HzmCrXVZNyGswwagVuVcvmBuHwGmnxMaWCGIC1CODf8X5BG4V932Akpl\n"
					"mCeQyLdkXHehZvSV1OCwxGko0FjVwnKIOplyMqCVpeDNwuddH02zo5h+kBSrTg0m\n"
					"XEMlVMAadS9vgwLCLL1GKeVpYT3jNbgDfUrXC6udycgGdYA6QtmeuiZ3Lv37TQ8K\n"
					"LD7ono+XsT38XvlKRqbPrlHNae+PRLudKWHsgrZg2MckyEpG/x9dygru561p1Dns\n"
					"Bm17CVkQUIZyAPXQB6/UmxPbJYsChiQXxy3/4U2eZLVVkHRP7gPWBnFjNoyd5OBw\n"
					"G+psOVLNgCnFh+z4NO5CB4mVNtrR1NAH6IFhnlrip4YFRk3XPHVlkrxn6fHeEDGE\n"
					"eVB3XJcgsGnVQCvF5vsymZWZ722xgLPkK8iG3QLayoM4c9RlrKMwwA==\n"
					"-----END RSA PRIVATE KEY-----\n"
					"-----BEGIN CERTIFICATE-----\n"
					"MIIB7TCCAVYCCQCxKhAUH1ygCDANBgkqhkiG9w0BAQUFADA7MQswCQYDVQQGEwJB\n"
					"VTEMMAoGA1UECBMDTlNXMQ8wDQYDVQQHEwZTeWRuZXkxDTALBgNVBAoTBGFzaW8w\n"
					"HhcNMDUxMTAyMTk0ODU1WhcNMTUxMTAyMTk0ODU1WjA7MQswCQYDVQQGEwJBVTEM\n"
					"MAoGA1UECBMDTlNXMQ8wDQYDVQQHEwZTeWRuZXkxDTALBgNVBAoTBGFzaW8wgZ8w\n"
					"DQYJKoZIhvcNAQEBBQADgY0AMIGJAoGBAMkNbM2RjFdm48Wy1nBA3+exfJL5fR6H\n"
					"guRFu/7MKf6pQZGRqhzxIWYRoYQDx16BggHwqFVVls5hgoQF0fUqoHfE8MLGwr6m\n"
					"T6rIYBrIAGnH8eMhfwMNy4I0emkoWI+grEXlw54IUSijh8LokLWorElyGuPmxhn3\n"
					"IgZkgGe8dCQTAgMBAAEwDQYJKoZIhvcNAQEFBQADgYEAdpHw+r3X4NwzKn9nQs3h\n"
					"mQK2WeH6DVQ1r7fWqEq1Lq10qBdobbjDRE9jpezWdGMThbYtle6/8wHUJeq189PR\n"
					"XwZWyRvnfcI+pqX832yNRh24Ujwuv3wlx3JOVByybCoJc05N1THaHo0Q7j//8HsX\n"
					"VS/RFHuq3muy47cV9gbsCIw=\n"
					"-----END CERTIFICATE-----";

				m_context.use_certificate_chain(asio::buffer(server_pem.c_str(), server_pem.size()));
				m_context.use_private_key(asio::buffer(server_pem.c_str(), server_pem.size()), asio::ssl::context::pem);
				m_context.use_tmp_dh(asio::buffer(dh512_pem.c_str(), dh512_pem.size()));
			}
		}

		// create acceptor
		if (ip.size())
			m_acceptor = AcceptorPtr(new asio::ip::tcp::acceptor(schedule->GetIOService()
			, asio::ip::tcp::endpoint(asio::ip::address_v4::from_string(ip), port), false));
		else
			m_acceptor = AcceptorPtr(new asio::ip::tcp::acceptor(schedule->GetIOService()
			, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port), false));
	}
	catch (asio::error_code& ec)
	{
		m_acceptor = AcceptorPtr();
		CARP_SYSTEM("HttpServer: start failed at " << ip << ":" << port << " error: " << ec.value());
		return false;
	}

    // save info
    m_yun_ip = yun_ip;
	m_ip = ip;
	m_port = port;
	m_heartbeat_interval = heartbeat;
	m_is_ssl = is_ssl;

	// start timer for heartbeat
	m_heartbeat_timer = AsioTimerPtr(new AsioTimer(m_schedule->GetIOService(), std::chrono::seconds(m_heartbeat_interval)));
	m_heartbeat_timer->async_wait(std::bind(&HttpServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1));

	// start to accept next connect
	NextAccept(0);

	CARP_SYSTEM("HttpServer: start succeed at " << ip << ":" << port);
	return true;
}

void HttpServer::Close()
{
	if (!m_acceptor) return;

	// reset
	m_context = asio::ssl::context(asio::ssl::context::sslv23);

	// close accept
	m_acceptor->close();

	// release acceptor
	m_acceptor = AcceptorPtr();

	// release timer
	m_heartbeat_timer = AsioTimerPtr();

	// clear all sockets
	asio::error_code ec;
	SocketReceiverMap::iterator receiver_it, receiver_end = m_receiver_socket_map.end();
	for (receiver_it = m_receiver_socket_map.begin(); receiver_it != receiver_end; ++receiver_it)
		CARPHTTPSOCKET_Close(receiver_it->first);

	m_receiver_socket_map.clear();
	m_sender_socket_map.clear();

	CARP_SYSTEM("HttpServer stop succeed.");
}

void HttpServer::CloseClient(CarpHttpSocketPtr socket)
{
	if (!socket) return;
	// close client
	CARPHTTPSOCKET_Close(socket);
	
	// remove receiver
	m_receiver_socket_map.erase(socket);
	// remove sender
	SocketSenderMap::iterator it = m_sender_socket_map.find(socket);
	if (it != m_sender_socket_map.end())
	{
		it->second->m_is_removed = true;
		m_sender_socket_map.erase(it);
	}
	// CARP_INFO("HttpServer ##CLOSE, socket count : " << m_receiver_socket_map.size());
}

void HttpServer::ExecuteRemoveCallBack(CarpHttpSocketPtr socket)
{
	// if socket is not exist, than is close by self, no need to invoke callback
	SocketSenderMap::iterator it = m_sender_socket_map.find(socket);
	if (it == m_sender_socket_map.end()) return;

	// invoke callback
	// m_schedule->HandleRemoveClient(it->second);
	
	// close socket
	CloseClient(socket);
}

void HttpServer::NextAccept(int error_count)
{
	// check acceptor
	if (!m_acceptor) return;

	// create socket
	CarpHttpSocketPtr socket = CarpHttpSocketPtr(new CarpHttpSocket(m_is_ssl, &m_schedule->GetIOService(), &m_context));
	
	// bind callback
	CARPHTTPSOCKET_AsyncAccept(socket, m_acceptor, std::bind(&HttpServer::HandleAccept, this->shared_from_this(), socket, std::placeholders::_1, error_count));
}

void HttpServer::HandleAccept(CarpHttpSocketPtr socket, const asio::error_code& ec, int error_count)
{
	if (ec)
	{
		CARP_ERROR("https server accept failed: " << ec.value());
		if (error_count > 100)
			Close();
		else
			NextAccept(error_count + 1);
		return;
	}

	// set no delay
	CARPHTTPSOCKET_SetNoDelay(socket);
	if (socket->ssl_socket)
		socket->ssl_socket->async_handshake(asio::ssl::stream<asio::ip::tcp::socket>::server
			, std::bind(&HttpServer::HandleHandShake, this->shared_from_this(), socket, std::placeholders::_1));
	else
		HandleHandShake(socket, asio::error_code());

	// accept next
	NextAccept(0);
}

void HttpServer::HandleHandShake(CarpHttpSocketPtr socket, const asio::error_code& ec)
{
	if (ec)
	{
		CARP_ERROR("server hand shake failed: " << ec.value());
		return;
	}

	// create receiver
	HttpReceiverPtr receiver = HttpReceiverPtr(new HttpReceiver(socket, this->shared_from_this()));
	// save receiver
	m_receiver_socket_map[socket] = receiver;

	// create sender
	HttpSenderPtr sender = HttpSenderPtr(new HttpSender(socket, this->shared_from_this(), m_schedule));
	// save sender
	m_sender_socket_map[socket] = sender;

	receiver->m_sender = sender;
	sender->m_receiver = receiver;

	// receiver start to read next
	receiver->NextRead();

	// invoke callback
	// m_schedule->HandleAddClient(sender);
}

HttpServer::SocketSenderMap& HttpServer::GetAllSender()
{
	return m_sender_socket_map;
}

void HttpServer::ServerSendHeatbeat(const asio::error_code& ec)
{
	{
		std::list<HttpSenderPtr> sender_list;
		SocketSenderMap::iterator map_it, map_end = m_sender_socket_map.end();
		for (map_it = m_sender_socket_map.begin(); map_it != map_end; ++map_it)
			sender_list.push_back(map_it->second);

		std::list<HttpSenderPtr>::iterator list_it, list_end = sender_list.end();
		for (list_it = sender_list.begin(); list_it != list_end; ++list_it)
			(*list_it)->Heartbeat(m_heartbeat_interval);
	}

	{
		std::list<HttpReceiverPtr> receiver_list;
		SocketReceiverMap::iterator map_it, map_end = m_receiver_socket_map.end();
		for (map_it = m_receiver_socket_map.begin(); map_it != map_end; ++map_it)
			receiver_list.push_back(map_it->second);

		std::list<HttpReceiverPtr>::iterator list_it, list_end = receiver_list.end();
		for (list_it = receiver_list.begin(); list_it != list_end; ++list_it)
			(*list_it)->Heartbeat(m_heartbeat_interval);
	}

	if (!m_heartbeat_timer) return;
	m_heartbeat_timer->expires_at(std::chrono::system_clock::now() + std::chrono::seconds(m_heartbeat_interval));
	m_heartbeat_timer->async_wait(std::bind(&HttpServer::ServerSendHeatbeat, this->shared_from_this(), std::placeholders::_1));
}

void HttpServer::HandleHttpMessage(HttpSenderPtr sender, const std::string& msg)
{
	m_schedule->HandleHttpMessage(sender, msg);
}

bool HttpServer::HandleHttpFileMessage(HttpSenderPtr sender, const std::string& msg)
{
	return m_schedule->HandleHttpFileMessage(sender, msg);
}

void HttpServer::HandleHttpFileCompletedMessage(HttpSenderPtr sender
												, const std::string& msg
												, const std::string& file_path
												, const std::string* reason)
{
	if (reason == nullptr)
		m_schedule->HandleHttpFileCompletedMessage(sender, file_path, true, "");
	else
		m_schedule->HandleHttpFileCompletedMessage(sender, file_path, false, *reason);
}

} // ALittle