
#include "HttpClientPost.h"
#include "../Helper/StringHelper.h"

namespace ALittle
{
	
#define CONTENT_TYPE_BOUNDARY "----WebKitFormBoundarywP43vY132opdlHoz"

HttpClientPost::HttpClientPost()
: m_file(0), m_response_type(HttpHelper::ResponseType::RESPONSE_TYPE_CONTENT_LENGTH)
, m_response_size(0), m_cur_size(0), m_total_size(0), m_http_buffer(), m_io_service(0)
, m_stoped(false)
{
}

HttpClientPost::~HttpClientPost()
{
	if (m_file) { fclose(m_file); m_file = 0; }
}

void HttpClientPost::SendRequest(const std::string& url
									 , const std::map<std::string, std::string>& value_map
									 , const std::string& file_name
									 , const std::string& file_path
									 , std::function<void(bool, const std::string&, const std::string&, const std::string&)> complete_func
									 , std::function<void(int, int)> progress_func
									 , asio::io_service* io_service
									 , const std::string& add_header/*=""*/)
{
	// get domain and port from url
	std::string domain;
	int port = 0;
	std::string path;
	bool result = HttpHelper::CalcDomainAndPortByUrl(url, domain, port, path);
	if (!result)
	{
		m_error = "can't find domain and port in url:" + url;
		complete_func(false, "", m_response_head, m_error);
		return;
	}

	bool is_ssl = (port == 443);

	// save info
	m_complete_callback = complete_func;
	m_progress_callback = progress_func;
	m_url = url;
	m_file_path = file_path;
	m_file_name = file_name;
	m_value_map = value_map;
	m_io_service = io_service;

	// calc request head
	if (!GeneratePostRequest(domain, add_header))
	{
		m_error = "generate post request failed: " + url;
		complete_func(false, "", m_response_head, m_error);
		return;
	}

	m_socket = ALittleSocketPtr(new ALittleSocket(is_ssl, m_io_service, domain));
	
	// get ip dress by domain
	m_resolver = ResolverPtr(new asio::ip::tcp::resolver(*m_io_service));
	asio::ip::tcp::resolver::query ip_query(domain, std::to_string(port));

	// bind callback
	std::function<void(const asio::error_code& ec
		, asio::ip::tcp::resolver::iterator endpoint_iterator)> query_func;
	query_func = std::bind(&HttpClientPost::HandleQueryIPByDemain, this->shared_from_this()
		, std::placeholders::_1, std::placeholders::_2, domain, std::to_string(port));

	// query
	m_resolver->async_resolve(ip_query, query_func);
}

void HttpClientPost::Stop()
{
	m_stoped = true;
}

void HttpClientPost::HandleQueryIPByDemain(	const asio::error_code& ec
										, asio::ip::tcp::resolver::iterator endpoint_iterator
										, const std::string& domain, const std::string& port)
{
	if (ec)
	{
		m_error = "query ip by domain failed and try again:" + domain + ", " + port;
		// try again
		m_resolver = ResolverPtr(new asio::ip::tcp::resolver(*m_io_service));
		asio::ip::tcp::resolver::query ip_query(domain, port);

		std::function<void(const asio::error_code& ec
			, asio::ip::tcp::resolver::iterator endpoint_iterator)> query_func;
		query_func = std::bind(&HttpClientPost::HandleQueryIPByDemainAgain, this->shared_from_this()
			, std::placeholders::_1, std::placeholders::_2);

		m_resolver->async_resolve(ip_query, query_func);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// start connect
	asio::ip::tcp::resolver::iterator endpoint = endpoint_iterator;
	SOCKETHELPER_AsyncConnect(m_socket, endpoint
		, std::bind(&HttpClientPost::HandleSocketConnect, this->shared_from_this()
		, std::placeholders::_1, ++endpoint_iterator));
}

void HttpClientPost::HandleQueryIPByDemainAgain(const asio::error_code& ec , asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if (ec)
	{
		m_error = "query ip by domain failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// start connect
	asio::ip::tcp::resolver::iterator endpoint = endpoint_iterator;
	SOCKETHELPER_AsyncConnect(m_socket, endpoint
		, std::bind(&HttpClientPost::HandleSocketConnect, this->shared_from_this()
		, std::placeholders::_1, ++endpoint_iterator));
}

bool HttpClientPost::GeneratePostRequest(const std::string& domain, const std::string& add_header/*=""*/)
{
	// cut string after http://
	std::string new_url;
	if (m_url.substr(0, 8) == "https://")
		new_url = m_url.substr(8);
	else
		new_url = m_url;

	// find position of path
	std::string::size_type path_pos = new_url.find('/');
	if (path_pos != std::string::npos)
		new_url = HttpHelper::UrlEncode(new_url.substr(path_pos));
	else
		new_url = "";

	// store total size
	size_t total_size = 0;

	// init param
	m_request_param = "";
	m_request_file_begin = "";
	m_request_file_end = "";

	// generate param part
	std::map<std::string, std::string>::const_iterator it, end = m_value_map.end();
	for (it = m_value_map.begin(); it != end; ++it)
	{
		m_request_param.append("--").append(CONTENT_TYPE_BOUNDARY).append("\r\n");
		m_request_param.append("Content-Disposition: form-data; name=\"").append(it->first).append("\"\r\n\r\n");
		m_request_param.append(it->second).append("\r\n");
	}

	// add param size to total size
	total_size += m_request_param.size();

	// handle file part
	if (m_file_path.size())
	{
		// open file
#ifdef _WIN32
		fopen_s(&m_file, m_file_path.c_str(), "rb");
#else
		m_file = fopen(m_file_path.c_str(), "rb");
#endif
		if (!m_file)
		{
			m_error = "can't open file:" + m_file_path;
			return false;
		}

		// calc size of file
		fseek(m_file, 0, SEEK_END);
		m_cur_size = 0;
		m_total_size = (int)ftell(m_file);
		total_size += m_total_size;
		fseek(m_file, 0, SEEK_SET);

		// generate file begin param
		m_request_file_begin.append("--").append(CONTENT_TYPE_BOUNDARY).append("\r\n");
		m_request_file_begin.append("Content-Disposition: form-data; name=\"").append(m_file_name)
			.append("\"; filename=\"").append(m_file_name).append("\"\r\n");
		m_request_file_begin.append("Content-Type: application/octet-stream\r\n\r\n");

		// generate end param
		m_request_file_end.append("\r\n--").append(CONTENT_TYPE_BOUNDARY).append("--\r\n");

		// add to total size
		total_size += m_request_file_begin.size();
		total_size += m_request_file_end.size();
	}
	// handle param part
	else if (m_request_param.size())
	{
		// generate end param
		m_request_file_end.append("--").append(CONTENT_TYPE_BOUNDARY).append("--\r\n");
		
		// add to total size
		total_size += m_request_file_end.size();
	}

	// add header
	std::string upper_add_header = add_header;
	StringHelper::UpperString(upper_add_header);

	// generate request head
	m_request_head = "";
	if (new_url.size())
		m_request_head.append("POST ").append(new_url).append(" HTTP/1.1\r\n");
	else
		m_request_head.append("POST /").append(" HTTP/1.1\r\n");
	if (upper_add_header.find("ACCEPT") == std::string::npos)
		m_request_head.append("Accept: */*\r\n");
	if (upper_add_header.find("USER-AGENT") == std::string::npos)
		m_request_head.append("User-Agent: ALittle Client\r\n");
	m_request_head.append("Host: ").append(domain).append("\r\n");
	if (total_size > 0)
	{
		m_request_head.append("Content-Type: multipart/form-data; boundary=").append(CONTENT_TYPE_BOUNDARY).append("\r\n");
		m_request_head.append("Content-Length: ").append(std::to_string(total_size)).append("\r\n");
	}
	if (upper_add_header.find("CONNECTION") == std::string::npos)
		m_request_head.append("Connection: Keep-Alive\r\n");
	m_request_head.append(add_header);
	m_request_head.append("\r\n");
	m_total_size = total_size;

	return true;
}

void HttpClientPost::HandleSocketConnect(const asio::error_code& ec
										, asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	if (!ec)
	{
		SOCKETHELPER_AfterAsyncConnect(m_socket);
#ifdef ALITTLE_HAS_SSL
		if (m_socket->ssl_socket)
			m_socket->ssl_socket->async_handshake(asio::ssl::stream<asio::ip::tcp::socket>::client
				, std::bind(&HttpClientPost::HandleSSLHandShake, this->shared_from_this(), std::placeholders::_1));
		else
#endif
			HandleSSLHandShake(asio::error_code());
	}  
	else if (endpoint_iterator != asio::ip::tcp::resolver::iterator())  
	{  
		asio::ip::tcp::resolver::iterator endpoint = endpoint_iterator;
		SOCKETHELPER_AsyncConnect(m_socket, endpoint
			, std::bind(&HttpClientPost::HandleSocketConnect, this->shared_from_this()
			, std::placeholders::_1, ++endpoint_iterator));
	}  
	else  
	{
		m_error = "connect domain failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
	}  
}

void HttpClientPost::HandleSocketSendRequestHead(const asio::error_code& ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		m_error = "socket send post request head failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	if (m_request_param.size())
	{
		// send param
		SOCKETHELPER_AsyncWrite(m_socket, m_request_param.c_str(), m_request_param.size()
			, std::bind(&HttpClientPost::HandleSocketSendRequestParam, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
		return;
	}

	if (m_request_file_begin.size())
	{
		// send file begin param
		SOCKETHELPER_AsyncWrite(m_socket, m_request_file_begin.c_str(), m_request_file_begin.size()
			, std::bind(&HttpClientPost::HandleSocketSendRequestFileBegin, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
		return;
	}
}

void HttpClientPost::HandleSocketSendRequestParam(const asio::error_code& ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		m_error = "socket send post request param failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	if (m_request_file_begin.size())
	{
		// send file begin param
		SOCKETHELPER_AsyncWrite(m_socket, m_request_file_begin.c_str(), m_request_file_begin.size()
			, std::bind(&HttpClientPost::HandleSocketSendRequestFileBegin, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
		return;
	}

	// send end param
	SOCKETHELPER_AsyncWrite(m_socket, m_request_file_end.c_str(), m_request_file_end.size()
		, std::bind(&HttpClientPost::HandleSocketSendRequestFileEnd, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void HttpClientPost::HandleSocketSendRequestFileBegin(const asio::error_code& ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		m_error = "socket send post request file begin failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

    if (m_file == 0)
    {
        m_error = "why m_file is null";
        m_complete_callback(false, "", m_response_head, m_error);
        return;
    }

	size_t read_size = fread(m_http_buffer, 1, sizeof(m_http_buffer), m_file);
	if (read_size > 0)
	{
		// send file content
		SOCKETHELPER_AsyncWrite(m_socket, m_http_buffer, read_size
			, std::bind(&HttpClientPost::HandleSocketSendRequestFile, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		if (m_file) { fclose(m_file); m_file = 0; }
		
		// send end param
		SOCKETHELPER_AsyncWrite(m_socket, m_request_file_end.c_str(), m_request_file_end.size()
			, std::bind(&HttpClientPost::HandleSocketSendRequestFileEnd, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
}

void HttpClientPost::HandleSocketSendRequestFile(const asio::error_code& ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		m_error = "socket send post request file failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

    if (m_file == 0)
    {
        m_error = "why m_file is null";
        m_complete_callback(false, "", m_response_head, m_error);
        return;
    }

	m_cur_size += (int)bytes_transferred;
	if (m_progress_callback)
		m_progress_callback(m_total_size, m_cur_size);

	size_t read_size = fread(m_http_buffer, 1, sizeof(m_http_buffer), m_file);
	if (read_size > 0)
	{
		// send file content
		SOCKETHELPER_AsyncWrite(m_socket, m_http_buffer, read_size
			, std::bind(&HttpClientPost::HandleSocketSendRequestFile, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		if (m_file) { fclose(m_file); m_file = 0; }
		
		// send end param
		SOCKETHELPER_AsyncWrite(m_socket, m_request_file_end.c_str(), m_request_file_end.size()
			, std::bind(&HttpClientPost::HandleSocketSendRequestFileEnd, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
}

void HttpClientPost::HandleSocketSendRequestFileEnd(const asio::error_code& ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		m_error = "socket send post request file end failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// start receive http response
	SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
		, std::bind(&HttpClientPost::HandleResponseHead, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void HttpClientPost::HandleResponseHead(const asio::error_code& ec, std::size_t actual_size)
{
	if (ec)
	{
		m_error = "read response failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// store current size of response
	int current_size = (int)m_response.size();
	// add new byte to response
	m_response.append(m_http_buffer, actual_size);

	// set start point to find
	int find_start_pos = current_size - (int)strlen("\r\n\r\n");
	if (find_start_pos < 0) find_start_pos = 0;

	// find \r\n\r\n
	size_t find_pos = m_response.find("\r\n\r\n", find_start_pos);
	if (find_pos != std::string::npos)
	{
		// save response head
		m_response_head = m_response.substr(0, find_pos + strlen("\r\n\r\n"));

		// read status of head
		std::string status;
		if (!HttpHelper::CalcStatusFromHttp(m_response_head, status))
		{
			m_error = "http status calc failed:" + m_response;
			m_complete_callback(false, "", m_response_head, m_error);
			return;
		}

		// check status is 200
		if (status != "200")
		{
			m_error = "http status error:" + status;
			m_complete_callback(false, "", m_response_head, m_error);
			return;
		}

		m_response_size = 0;
		// read content size
		if (!HttpHelper::CalcFileSizeFromHttp(m_response_head, m_response_size, m_response_type))
		{
			m_error = "http file size calc failed:" + m_response;
			m_complete_callback(false, "", m_response_head, m_error);
			return;
		}

		// pos content is then count of bytes after current size
		int content_pos = (int)find_pos + (int)strlen("\r\n\r\n") - current_size;
		// calc content size
		int content_size = (int)actual_size - content_pos;

		// clear response
		m_response = "";

		// split handle
		if (m_response_type == HttpHelper::ResponseType::RESPONSE_TYPE_CONTENT_LENGTH)
			HandleResponseByContentLength(ec, content_size, content_pos);
		else if (m_response_type == HttpHelper::ResponseType::RESPONSE_TYPE_CHUNK)
			HandleResponseByChunk(ec, content_size, content_pos);
		else
			HandleResponseByDataFollow(ec, content_size, content_pos);		
	}
	else
	{
		// read next bytes
		SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
			, std::bind(&HttpClientPost::HandleResponseHead, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}
}

void HttpClientPost::HandleResponseByContentLength(const asio::error_code& ec, std::size_t actual_size, int buffer_offset)
{
	if (ec)
	{
		m_error = "read response failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// dec content size that is received now
	m_response_size -= (int)actual_size;

	m_response.append(m_http_buffer + buffer_offset, actual_size);

	if (m_response_size <= 0)
	{
		m_complete_callback(true, m_response, m_response_head, m_error);
		return;
	}

	// read next bytes
	SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
		, std::bind(&HttpClientPost::HandleResponseByContentLength, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2, 0));
}

void HttpClientPost::HandleResponseByDataFollow(const asio::error_code& ec, std::size_t actual_size, int buffer_offset)
{
	if (ec)
	{
		m_complete_callback(true, m_response, m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// write new content to file or buffer
	m_response.append(m_http_buffer + buffer_offset, actual_size);

	// read next bytes
	SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
		, std::bind(&HttpClientPost::HandleResponseByDataFollow, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2, 0));
}

void HttpClientPost::HandleResponseByChunk(const asio::error_code& ec, std::size_t actual_size, int buffer_offset)
{
	if (ec)
	{
		m_error = "read response failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// calc chunk size
	if (m_response_size <= 0)
	{
		// save old len of chunk size string
		int old_chunk_size_len = (int)m_chunk_size.size();
		// append new buffer
		m_chunk_size.append(m_http_buffer + buffer_offset, actual_size);

		// check size complete
		size_t chunk_pos = m_chunk_size.find("\r\n");
		if (chunk_pos == std::string::npos)
		{
			// if chunk is too large then fail
			if (m_chunk_size.size() >= HTTP_HEAD_BUFFER_SIZE)
			{
				m_error = "read response failed: chunk size is too large! " + std::to_string(m_chunk_size.size());
				m_complete_callback(false, "", m_response_head, m_error);
				return;
			}

			SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
				, std::bind(&HttpClientPost::HandleResponseByChunk, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2, 0));
			return;
		}
		else if (chunk_pos == 0)
		{
			m_chunk_size = "";
			int add_chunk_size = ((int)strlen("\r\n") - (int)old_chunk_size_len);
			if (actual_size - add_chunk_size > 0)
				HandleResponseByChunk(ec, actual_size - add_chunk_size, buffer_offset + add_chunk_size);
			else
				SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
					, std::bind(&HttpClientPost::HandleResponseByChunk, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2, 0));
			return;
		}

		size_t chunk_space = m_chunk_size.find(" ");
		if (chunk_space != std::string::npos && chunk_space < chunk_pos)
			chunk_pos = chunk_space;

		// calc chunk size
		int result = 0;
		std::string number(m_chunk_size.c_str(), chunk_pos);
		if (chunk_pos == 0 || HttpHelper::String2HexNumber(result, number) == false)
		{
			m_error = "read chunk size calc failed:" + std::to_string(m_chunk_size.size());
			m_complete_callback(false, "", m_response_head, m_error);
			return;
		}
		m_response_size = result;

		// receive complete
		if (m_response_size == 0)
		{
			m_complete_callback(true, m_response, m_response_head, m_error);
			return;
		}

		// clear chunk size string
		m_chunk_size = "";
		int add_chunk_size = static_cast<int>(chunk_pos) + static_cast<int>(strlen("\r\n")) - static_cast<int>(old_chunk_size_len);
		if (static_cast<int>(actual_size) - add_chunk_size > 0)
			HandleResponseByChunk(ec, actual_size - add_chunk_size, buffer_offset + add_chunk_size);
		else
			SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
				, std::bind(&HttpClientPost::HandleResponseByChunk, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2, 0));
		return;
	}

	if (static_cast<int>(actual_size) <= m_response_size)
	{
		m_response.append(m_http_buffer + buffer_offset, actual_size);

		m_response_size -= static_cast<int>(actual_size);
		SOCKETHELPER_AsyncReadSome(m_socket, m_http_buffer, sizeof(m_http_buffer)
			, std::bind(&HttpClientPost::HandleResponseByChunk, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2, 0));
		return;
	}

	m_response.append(m_http_buffer + buffer_offset, m_response_size);

	buffer_offset += m_response_size;
	actual_size -= m_response_size;
	m_response_size = 0;

	HandleResponseByChunk(ec, actual_size, buffer_offset);
}

void HttpClientPost::HandleSSLHandShake(const asio::error_code& ec)
{
	if (ec)
	{
		m_error = "ssl hand shake failed:"; m_error += asio::system_error(ec).what();
		m_complete_callback(false, "", m_response_head, m_error);
		return;
	}

	if (m_stoped)
	{
		m_error = "stoped";
		m_complete_callback(false, "", "", m_error);
		return;
	}

	// connect succeed and send request
	SOCKETHELPER_AsyncWrite(m_socket, m_request_head.c_str(), m_request_head.size()
		, std::bind(&HttpClientPost::HandleSocketSendRequestHead, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2)); 
}

} // ALittle
