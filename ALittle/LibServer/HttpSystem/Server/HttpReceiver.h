
#ifndef _ALITTLE_HTTPRECEIVER_H_
#define _ALITTLE_HTTPRECEIVER_H_

#include <asio.hpp>
#include <iostream>
#include <fstream>

#include <memory>

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

#define HTTP_HEAD_BUFFER_SIZE 1024

class HttpReceiver : public std::enable_shared_from_this<HttpReceiver>
{
public:
	friend HttpServer;

public:
	HttpReceiver(CarpHttpSocketPtr socket, HttpServerPtr server);
	~HttpReceiver();

private:
	void JustWait();
	void HandleJustWait(const asio::error_code& ec, std::size_t actual_size);

private:
	void NextRead();
	void HandleRead(const asio::error_code& ec, std::size_t actual_size);

private:
	void NextReadFile();
	void HandleReadFile(const asio::error_code& ec, std::size_t actual_size);

private:
	void NextReadPost();
	void HandleReadPost(const asio::error_code& ec, std::size_t actual_size);

public:
	// this func must invoke
	bool StartReceiveFile(const std::string& file_path, int start_size, std::string& reason);

private:
	void Clear();

	void Close();

private:
	time_t m_receive_time;			// receive time
	void Heartbeat(int second);	// handle heart beat

public:
	HttpSenderPtr m_sender;		// sender

private:
	CarpHttpSocketPtr m_socket;			// socket
	HttpServerWeakPtr m_server_system;	// server that create this receiver

private:
	char m_http_buffer[HTTP_HEAD_BUFFER_SIZE];	// receive buffer
	int m_last_size_of_http_buffer;						// used for file upload, when request file_path and start_size

private:
	std::string m_http_head;	// http head

private:
	bool m_boundary_or_file;	// post boundary
	std::string m_boundary_temp;// post boundary temp

private:
	std::string m_file_path;	// file path
	std::ofstream m_file;		// file object
	int m_receive_size;			// last size
};

} // ALittle

#endif // _ALITTLE_HTTPRECEIVER_H_
