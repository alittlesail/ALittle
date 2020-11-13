
#include "HttpSender.h"
#include "HttpServer.h"
#include "HttpReceiver.h"

#include "Carp/carp_file.hpp"
#include "Carp/carp_file_cache.hpp"

#include "../ServerSystem/ServerSchedule.h"

namespace ALittle
{

void HttpSender_HandleSend(HttpSenderPtr self, const asio::error_code& ec, std::size_t bytes_transferred);

#define HTTPS_SEND_FILE_BUFFER_SIZE 10240

HttpSender::HttpSender(CarpHttpSocketPtr socket, HttpServerPtr server, ServerSchedule* schedule)
: m_socket(socket), m_end_time(0), m_is_sending(false)
, m_server_system(server), m_schedule(schedule)
, m_is_removed(false)
, m_user_data(0), m_id(0)
{
	// save target ip
	CARPHTTPSOCKET_GetRemoteIp(socket, m_remote_ip);
	CARPHTTPSOCKET_GetRemotePort(socket, m_remote_port);
}

HttpSender::~HttpSender()
{
	Clear();
}

void HttpSender::Clear()
{
	if (m_file)
	{
		m_file->Close();
		m_file = nullptr;
	}
	m_http_content = "";
}

void HttpSender::SendString(const std::string& message)
{
	// if in sending, then return
	if (m_is_sending)
	{
		CARP_ERROR("Https Sender already in sending");
		Close();
		return;
	}

	// set current is in sending
	m_is_sending = true;

	// generate http content
	m_http_content = "";
	m_http_content += "HTTP/1.1 200 OK\r\n";
	m_http_content += "Access-Control-Allow-Origin: *\r\n";
	m_http_content += "Access-Control-Allow-Credentials: true\r\n";
	m_http_content += "Server: ALittle Https Server\r\n";
	m_http_content += "Content-Type: text/html\r\n";
	m_http_content += "Accept-Ranges: bytes\r\n";
	m_http_content = m_http_content + "Content-Length: " + std::to_string(message.size()) + "\r\n";
	m_http_content += "Connection: Close\r\n";
	m_http_content += "\r\n"; // ending code
	// add message content
	m_http_content += message;

	// send response
	CARPHTTPSOCKET_AsyncWrite(m_socket, m_http_content.c_str(), m_http_content.size(),
		std::bind(HttpSender_HandleSend, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void HttpSender_HandleSend(HttpSenderPtr self, const asio::error_code& ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		CARP_INFO("error info:" << ec.value());
		self->Close();
		return;
	}

	self->HandleSend(bytes_transferred);
}

void HttpSender::HandleSend(std::size_t bytes_transferred)
{
	m_http_content = "";

	// check is sending file
	if (m_file && m_file->IsOpen())
	{
		// read file
		int size = m_file->Read(&(m_file_buffer[0]), (int)m_file_buffer.size());
		// if completed
		if (size == 0)
		{
			// close file
			m_file->Close();
			// send completed do not affect by heart beat
			m_end_time = CarpTime::GetCurTime();
		}
		else
		{
			// send file content
			CARPHTTPSOCKET_AsyncWrite(m_socket, &(m_file_buffer[0]), size,
				std::bind(HttpSender_HandleSend, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
		}
	}
	else
	{
		// send completed do not affect by heart beat
		m_end_time = CarpTime::GetCurTime();
	}
}

const std::string& HttpSender::GetRemoteIP() const
{
	return m_remote_ip;
}

int HttpSender::GetRemotePort() const
{
	return m_remote_port;
}

void HttpSender::Close()
{
	// clear buffer, reset status
	Clear();
	// save socket, this is import!(prevent count of smart point desc to 0)
	CarpHttpSocketPtr socket = m_socket;
	// remove from server
	HttpServerPtr server_system = m_server_system.lock();
	if (server_system) server_system->ExecuteRemoveCallBack(socket);

	// send completed do not affect by heart beat
	m_end_time = 0;
}

bool HttpSender::StartReceiveFile(const std::string& file_path, int start_size, std::string& reason)
{
	HttpReceiverPtr receiver = m_receiver.lock();
	if (!receiver)
	{
		reason = u8"Http�����Ѿ��Ͽ�";
		return false;
	}

	return receiver->StartReceiveFile(file_path, start_size, reason);
}

void HttpSender::SendFile(const char* path, const char* content_type, bool for_download, int start_size, bool use_cache, const char* show_name)
{
	// if in sending, then return
	if (m_is_sending)
	{
		CARP_ERROR("Https Sender already in sending");
		Close();
		return;
	}

	// save file path
	m_file_path = path;

	// set is in sending
	m_is_sending = true;

	// open file
	m_file = m_schedule->GetFileCacheGroup().Create(path, use_cache);

	// if file is open failed, then send error response
	if (m_file == nullptr || !m_file->IsOpen())
	{
		m_http_content = "";
		m_http_content += "HTTP/1.1 404 Not Found\r\n";
		m_http_content += "Access-Control-Allow-Origin: *\r\n";
		m_http_content += "Access-Control-Allow-Credentials: true\r\n";
		m_http_content += "Server: ALittle Https Server\r\n";
		m_http_content += "Connection: Close\r\n";
		m_http_content += "Content-Type: text/html\r\n";
		m_http_content += "Content-Length: 0\r\n";
		m_http_content += "\r\n";

		// send
		CARPHTTPSOCKET_AsyncWrite(m_socket, m_http_content.c_str(), m_http_content.size(),
			std::bind(HttpSender_HandleSend, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));

		return;
	}

	// calc file size
	int size = m_file->GetFileSize();
	
	if (start_size > size)
	{
		CARP_ERROR("Https Sender start size:("<< start_size << ") is large than file size:" << size);
		Close();
		return;
	}

	if (start_size > 0)
	{
		m_file->SetOffset(start_size);
		size -= start_size;
	}

	// create buffer
	if (size < HTTPS_SEND_FILE_BUFFER_SIZE)
		m_file_buffer.resize(size);
	else
		m_file_buffer.resize(HTTPS_SEND_FILE_BUFFER_SIZE);

	// generate http response
	m_http_content = "";
	m_http_content += "HTTP/1.1 200 OK\r\n";
	m_http_content += "Access-Control-Allow-Origin: *\r\n";
	m_http_content += "Access-Control-Allow-Credentials: true\r\n";
	m_http_content += "Server: ALittle Https Server\r\n";
	if (for_download)
	{
		m_http_content += "Content-Disposition: attachment;filename=";
		if (show_name && strlen(show_name) > 0)
			m_http_content += CarpHttpHelper::UrlEncode(show_name);
		else
			m_http_content += CarpHttpHelper::UrlEncode(CarpFile::GetFileNameByPath(path));
		m_http_content += "\r\n";
	}
	if (content_type == 0 || content_type[0] == 0)
		m_http_content += "Content-Type: application/octet-stream\r\n";
	else
		m_http_content.append("Content-Type: ").append(content_type).append("\r\n");
	m_http_content += "Accept-Ranges: bytes\r\n";
	m_http_content += "Connection: Close\r\n";
	m_http_content = m_http_content + "Content-Length: " + std::to_string(size) + "\r\n";
	m_http_content += "\r\n"; // ending code

	// send
	CARPHTTPSOCKET_AsyncWrite(m_socket, m_http_content.c_str(), m_http_content.size(),
		std::bind(HttpSender_HandleSend, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

bool HttpSender::IsSending() const
{
	return m_is_sending;
}

bool HttpSender::IsRemoved() const
{
	return m_is_removed;
}

void HttpSender::Heartbeat(int second)
{
	// 0: return
	if (m_end_time == 0) return;

	// not wait second
	if (CarpTime::GetCurTime() - m_end_time < second) return;

	// close
	Close();
}

} // ALittle
