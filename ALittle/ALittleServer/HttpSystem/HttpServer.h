
#ifndef _ALITTLE_HttpServer_H_
#define _ALITTLE_HttpServer_H_

#include <asio.hpp>
#include <asio/ssl.hpp>

#include <memory>

#include <map>
#include <string>

class CarpHttpSocket;
typedef std::shared_ptr<CarpHttpSocket> CarpHttpSocketPtr;

namespace ALittle
{

class HttpReceiver;
typedef std::shared_ptr<HttpReceiver> HttpReceiverPtr;
typedef std::weak_ptr<HttpReceiver> HttpReceiverWeakPtr;

class HttpSender;
typedef std::shared_ptr<HttpSender> HttpSenderPtr;
typedef std::weak_ptr<HttpSender> HttpSenderWeakPtr;

class HttpServer;
typedef std::shared_ptr<HttpServer> HttpServerPtr;
typedef std::weak_ptr<HttpServer> HttpServerWeakPtr;

typedef std::shared_ptr<asio::ip::tcp::acceptor> AcceptorPtr;

typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class ServerSchedule;

class HttpServer : public std::enable_shared_from_this<HttpServer>
{
public:
	HttpServer();
	~HttpServer();

public:
	friend HttpReceiver;
	friend HttpSender;

public:
	/* start server
	 * @param ip: local ip dress
	 * @param port: port
	 * @param heartbeat: invertal to check dead socket
	 * @param is_ssl: is ssl
	 * @param server_pem_path: pem
	 * @param private_key_path: pem
	 * @param pem_password: password of pem
	 */
	bool Start(const std::string& yun_ip, const std::string& ip, unsigned int port, int heartbeat, bool is_ssl, ServerSchedule* schedule
		, const std::string& server_pem_path, const std::string& private_key_path, const std::string& pem_password);

	/* close server
	 */
	void Close();

private:
	void CloseClient(CarpHttpSocketPtr socket);

	void ExecuteRemoveCallBack(CarpHttpSocketPtr socket);
	
private:
	void NextAccept(int error_count);

	void HandleAccept(CarpHttpSocketPtr socket, const asio::error_code& ec, int error_count);
	void HandleHandShake(CarpHttpSocketPtr socket, const asio::error_code& ec);

public:
	// receive container
	typedef std::map<CarpHttpSocketPtr, HttpReceiverPtr> SocketReceiverMap;
	// sender container
	typedef std::map<CarpHttpSocketPtr, HttpSenderPtr> SocketSenderMap;

private:
	SocketReceiverMap m_receiver_socket_map;
	SocketSenderMap m_sender_socket_map;

public:
	/* get all sender
	 * @return all sender
	 */
	SocketSenderMap& GetAllSender();
	/* get http receiver count
	 * @return count
	 */
	size_t GetReceiverCount() const { return m_receiver_socket_map.size(); }

    const std::string& GetYunIp() const { return m_yun_ip; }
	const std::string& GetIp() const { return m_ip; }
	bool IsSSL() const { return m_is_ssl; }
	unsigned int GetPort() const { return m_port; }

private:
	std::string GetPemPassword() const;
	
private:
	AcceptorPtr m_acceptor;
	asio::ssl::context m_context;
	ServerSchedule* m_schedule;
	bool m_is_ssl;
	std::string m_pem_password;
    std::string m_yun_ip;
	std::string m_ip;
	unsigned int m_port;

private:
	int m_heartbeat_interval;
	AsioTimerPtr m_heartbeat_timer;

	void ServerSendHeatbeat(const asio::error_code& ec);

private:
	// handle http message
	void HandleHttpMessage(HttpSenderPtr sender, const std::string& msg);
	// handle http file message
	bool HandleHttpFileMessage(HttpSenderPtr sender, const std::string& msg);
	// handle http file completed message
	void HandleHttpFileCompletedMessage(HttpSenderPtr sender
							, const std::string& msg
							, const std::string& file_path
							, const std::string* reason);
};

} // ALittle

#endif // _ALITTLE_HttpServer_H_
