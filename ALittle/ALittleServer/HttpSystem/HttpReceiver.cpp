
#include "HttpReceiver.h"
#include "HttpServer.h"
#include "HttpSender.h"

#include "Carp/carp_http.hpp"
#include "Carp/carp_log.hpp"
#include "Carp/carp_time.hpp"

namespace ALittle
{

#define HTTP_HEAD_BUFFER_SIZE_MAX 10240000

HttpReceiver::HttpReceiver(CarpHttpSocketPtr socket, HttpServerPtr server)
: m_receive_time(0), m_socket(socket), m_server_system(server)
, m_last_size_of_http_buffer(0), m_boundary_or_file(false), m_receive_size(0)
{
	memset(m_http_buffer, 0, sizeof(m_http_buffer));
}

HttpReceiver::~HttpReceiver()
{
	Clear();
}

void HttpReceiver::Clear()
{
	m_http_head = "";
	m_receive_time = 0;
	if (m_file.is_open()) m_file.close();
}

void HttpReceiver::JustWait()
{
	CARPHTTPSOCKET_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
		, std::bind(&HttpReceiver::HandleJustWait, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void HttpReceiver::HandleJustWait(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		Close();
		return;
	}

	JustWait();
}

void HttpReceiver::NextRead()
{
	// update to current time
	m_receive_time = CarpTime::GetCurTime();

	// read next bytes
	CARPHTTPSOCKET_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
		, std::bind(&HttpReceiver::HandleRead, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void HttpReceiver::HandleRead(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		Close();
		return;
	}
	
	// update to current time
	m_receive_time = CarpTime::GetCurTime();

	// store current size
	int current_size = (int)m_http_head.size();
	// add to buffer
	m_http_head.append(m_http_buffer, actual_size);

	// stop receive if lager than max size
	if (m_http_head.size() > HTTP_HEAD_BUFFER_SIZE_MAX)
	{
		CARP_ERROR("HTTP head is large than " << HTTP_HEAD_BUFFER_SIZE_MAX);
		Close();
		return;
	}

	// set start point to find
	int find_start_pos = current_size - (int)strlen("\r\n\r\n");
	if (find_start_pos < 0) find_start_pos = 0;

	// find \r\n\r\n
	std::string::size_type find_pos = m_http_head.find("\r\n\r\n", find_start_pos);
	if (find_pos != std::string::npos)
	{
		// the end position of \r\n\r\n in m_http_head
		int head_size = (int)find_pos + (int)strlen("\r\n\r\n");
		// resize http size, delete other data
		m_http_head.resize(head_size);

		// pos content is then count of bytes after current size
		int receive_size = head_size - current_size;
		// calc content size
		int last_size = (int)actual_size - receive_size;

		// handle GET
		if (m_http_head.substr(0, 3) == "GET")
		{
			// receive completed and do not affect by heart beat
			m_receive_time = 0;

			// handle GET message
			HttpServerPtr server = m_server_system.lock();
			if (server)	server->HandleHttpMessage(m_sender, m_http_head);

			// read next to check sender is disconnected
			JustWait();
			return;
		}

		// handle POST
		if (m_http_head.substr(0, 4) == "POST")
		{
			// get content size from head
			CarpHttpHelper::ResponseType response_type = CarpHttpHelper::ResponseType::RESPONSE_TYPE_CONTENT_LENGTH;
			if (!CarpHttpHelper::CalcFileSizeFromHttp(m_http_head, m_receive_size, response_type)
				|| response_type != CarpHttpHelper::ResponseType::RESPONSE_TYPE_CONTENT_LENGTH)
			{
				CARP_ERROR("can't find Content-Length: in http head:" << m_http_head);
				Close();
				return;
			}

			// get content type from head
			std::string content_type = "";
			if (!CarpHttpHelper::CalcContentTypeFromHttp(m_http_head, content_type))
			{
				CARP_ERROR("can't find Content-Type: in http head:" << m_http_head);
				Close();
				return;
			}

			// check content type, only support below
			if (content_type.find("application/x-www-form-urlencoded") != std::string::npos
				|| content_type.find("text/xml") != std::string::npos
				|| content_type.find("text/plain") != std::string::npos
				|| content_type.find("application/json") != std::string::npos)
			{
				// check is completed
				if (last_size > 0)
				{
					// adjust buffer
					for (int i = 0; i < last_size; ++i)
						m_http_buffer[i] = m_http_buffer[receive_size + i];

					// handle buffer
					asio::error_code ec;
					HandleReadPost(ec, last_size);
					return;
				}

				// read next
				NextReadPost();
				return;
			}
			
			if (content_type.find("multipart/form-data") != std::string::npos)
			{
				// get boundary
				size_t boundary_pos = content_type.find("boundary=");
				if (boundary_pos == std::string::npos)
				{
					CARP_ERROR("can't find boundary in Content-Type:" << m_http_head);
					Close();
					return;
				}
				boundary_pos += strlen("boundary=");
				// dec boundary size at last line, \r\n--boundary--\r\n
				m_receive_size -= (int)content_type.size() - (int)boundary_pos + 8;

				// ready to read boundary
				m_boundary_or_file = true;

				// get file path to save
				HttpServerPtr server = m_server_system.lock();
				if (!server)
				{
					Close();
					return;
				}

                // save last size
                m_last_size_of_http_buffer = last_size;

                // check is completed
                if (last_size > 0)
                {
                    // adjust buffer
                    for (int i = 0; i < last_size; ++i)
                        m_http_buffer[i] = m_http_buffer[receive_size + i];
                }

				bool result = server->HandleHttpFileMessage(m_sender, m_http_head);
				if (result == false)
					Close();

				return;
			}

			CARP_ERROR("unknow Content-Type: in http head:" << m_http_head);
			Close();
			return;
		}

		// handle option
		if (m_http_head.substr(0, 7) == "OPTIONS")
		{
			// receive completed and do not affect by heart beat
			m_receive_time = 0;

			// send empty message
			m_sender->SendString("");

			// read next to check sender is disconnected
			JustWait();
			return;
		}

		CARP_ERROR("unknow http method!" << m_http_head);

		Close();
		return;
	}

	// read next
	NextRead();
}

void HttpReceiver::NextReadFile()
{
	// update to current time
	m_receive_time = CarpTime::GetCurTime();

	CARPHTTPSOCKET_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
		, std::bind(&HttpReceiver::HandleReadFile, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void HttpReceiver::HandleReadFile(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		// check file is open or not
		if (m_file.is_open())
		{
			m_file.close();

			// receive completed and do not affect by heart beat
			m_receive_time = 0;

			std::string reason = "HttpReceiver::HandleReadFile failed:" + std::to_string(ec.value());
			HttpServerPtr server = m_server_system.lock();
			if (server) server->HandleHttpFileCompletedMessage(m_sender, m_http_head, m_file_path, &reason);
		}
		Close();
		return;
	}

	// update current time
	m_receive_time = CarpTime::GetCurTime();

	// if last size lager than 0, then handle new bytes
	if (m_receive_size > 0)
	{
		if (m_boundary_or_file)
		{
			// store current size
			int current_size = (int)m_boundary_temp.size();
			// add to buffer
			m_boundary_temp.append(m_http_buffer, actual_size);

			// stop receive if lager than max size
			if (m_boundary_temp.size() > HTTP_HEAD_BUFFER_SIZE_MAX)
			{
				std::string reason = "HTTP m_boundary_temp is large than HTTP_HEAD_BUFFER_SIZE_MAX";
				HttpServerPtr server = m_server_system.lock();
				if (server) server->HandleHttpFileCompletedMessage(m_sender, m_http_head, m_file_path, &reason);
				Close();
				return;
			}

			// set start point to find
			int find_start_pos = current_size - (int)strlen("\r\n\r\n");
			if (find_start_pos < 0) find_start_pos = 0;

			// find \r\n\r\n
			std::string::size_type find_pos = m_boundary_temp.find("\r\n\r\n", find_start_pos);
			if (find_pos != std::string::npos)
			{
				// the end position of \r\n\r\n in m_boundary_temp
				int head_size = (int)find_pos + (int)strlen("\r\n\r\n");

				// pos content is then count of bytes after current size
				int receive_size = head_size - current_size;
				// calc content size
				int last_size = (int)actual_size - receive_size;

				// dec receive_size
				m_receive_size -= receive_size;

				// ready to receive file content
				m_boundary_or_file = false;

				if (last_size > 0)
				{
					// adjust buffer
					for (int i = 0; i < last_size; ++i)
						m_http_buffer[i] = m_http_buffer[receive_size + i];

					// handle file
					asio::error_code ec;
					HandleReadFile(ec, last_size);
					return;
				}
			}
		}
		else
		{
			// write to file
			if (m_receive_size < (int)actual_size)
				m_file.write(m_http_buffer, m_receive_size);
			else
				m_file.write(m_http_buffer, actual_size);

			// dec content size that is received now
			m_receive_size -= (int)actual_size;

			// check is receive completed
			if (m_receive_size <= 0)
			{
				// close file
				m_file.close();

				// receive completed and do not affect by heart beat
				m_receive_time = 0;

				HttpServerPtr server = m_server_system.lock();
				if (server) server->HandleHttpFileCompletedMessage(m_sender, m_http_head, m_file_path, nullptr);

				JustWait();
				return;
			}
		}
	}

	// read next
	NextReadFile();
}

void HttpReceiver::NextReadPost()
{
	// update to current time
	m_receive_time = CarpTime::GetCurTime();

	CARPHTTPSOCKET_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
		, std::bind(&HttpReceiver::HandleReadPost, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void HttpReceiver::HandleReadPost(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		Close();
		return;
	}

	// update current time
	m_receive_time = CarpTime::GetCurTime();
	// add to buffer
	m_http_head.append(m_http_buffer, actual_size);

	// dec content size that is received now
	m_receive_size -= (int)actual_size;

	// check is completed
	if (m_receive_size <= 0)
	{
		// receive completed and do not affect by heart beat
		m_receive_time = 0;

		// handle post message
		HttpServerPtr server = m_server_system.lock();
		if (server) server->HandleHttpMessage(m_sender, m_http_head);

		JustWait();
		return;
	}

	// read next
	NextReadPost();
}

void HttpReceiver::Close()
{
	// clear buffer, reset status
	Clear();
	// save socket, this is import!(prevent count of smart point desc to 0)
	CarpHttpSocketPtr socket = m_socket;
	// remove from server
	HttpServerPtr server_system = m_server_system.lock();
	if (server_system) server_system->ExecuteRemoveCallBack(socket);
}

void HttpReceiver::Heartbeat(int second)
{
	// 0: return
	if (m_receive_time == 0) return;

	// not wait second
	if (CarpTime::GetCurTime() - m_receive_time < second) return;

	// close
	Close();
}

bool HttpReceiver::StartReceiveFile(const std::string& file_path, int start_size, std::string& reason)
{
	if (!m_file_path.empty())
	{
		reason = "m_file_path is already set:" + m_file_path;
		return false;
	}

	m_file_path = file_path;

	// create file
	if (start_size <= 0)
		m_file.open(m_file_path.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
	else
		m_file.open(m_file_path.c_str(), std::ios::binary | std::ios::out);
	if (!m_file)
	{
		reason = "open file failed:" + m_file_path;
		return false;
	}
	if (start_size > 0) m_file.seekp(start_size);

	// check is completed
	if (m_last_size_of_http_buffer > 0)
	{
		// handle buffer
		asio::error_code ec;
		HandleReadFile(ec, m_last_size_of_http_buffer);
		return true;
	}

	// read next
	NextReadFile();

	return true;
}

} // ALittle
