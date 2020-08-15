
#include "HttpClient.h"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/HttpHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"

#include <SDL.h>
#include <SDL_net.h>
#include <stdio.h>

namespace ALittle
{

SafeIDCreator<int> HttpClient::s_id_creator;

HttpClient::HttpClient()
: m_continue_load(true), m_socket(nullptr)
{
	m_id = s_id_creator.CreateID();
}

HttpClient::~HttpClient()
{
	s_id_creator.ReleaseID(m_id);
	if (m_socket) SDLNet_TCP_Close(m_socket);
}

void HttpClient::SetURL(const char* url, const char* content)
{
	if (m_socket)
	{
		ALITTLE_ERROR("socket already exist!");
		return;
	}

	if (url) m_url = url;
	if (content) m_content = content;
	m_response.resize(1, 0);
	m_status = "";

#ifdef __IPHONEOS__
	std::string domain, path;
	int port = 0;
	NetHelper::CalcHttpDomainAndPortByUrl(m_url, domain, port, path);
	m_socket = SDLNet_TCP_IPV6SocketCreate(NetHelper::GetAIFamily(domain.c_str(), port));
#else
	m_socket = SDLNet_TCP_SocketCreate();
#endif
}

const char* HttpClient::GetStatus() const
{
	return m_status.c_str();
}

const char* HttpClient::GetResponse() const
{
	return m_response.data();
}

void HttpClient::GetContent( char*& content, int& size )
{
	size = static_cast<int>(m_response.size()) - 1;
	if (size <= 0)
	{
		content = 0;
		size = 0;
		return;
	}
	content = m_response.data();
}

const char* HttpClient::GetURL() const
{
	return m_url.c_str();
}

int HttpClient::GetID() const
{
	return m_id;
}

void HttpClient::Start()
{
	g_ThreadSystem.AddTask(this, ThreadSystem::THREAD_TYPE_SLOW);
}

void HttpClient::Stop()
{
	m_continue_load = false;
#ifdef __IPHONEOS__
	if (m_socket) SDLNet_TCP_JustClose(m_socket);
#else
	if (m_socket) SDLNet_TCP_JustShutdown(m_socket);
#endif
}

void HttpClient::Execute()
{
	m_response.resize(0);
	m_chunk_buffer.resize(0);
	m_failed_reason.clear();
	bool result = Load();
	m_response.push_back(0); // push end of string
	m_chunk_buffer.clear();
	if (result)
		g_ScheduleSystem.PushUserEvent(NET_HTTP_SUCCEED, (void*)this);
	else
	{
		if (m_failed_reason.empty()) m_failed_reason = "status is not 200";
		g_ScheduleSystem.PushUserEvent(NET_HTTP_FAILED, (void*)this);
	}
}

void HttpClient::Abandon()
{
	m_failed_reason = "abandon http client";
	g_ScheduleSystem.PushUserEvent(NET_HTTP_FAILED, (void*)this);
}

#define HTTP_RESPONSE_BUFFER_SIZE 1024

bool HttpClient::Load()
{
	if (m_continue_load == false)
	{
		m_failed_reason = "http cancel";
		return false;
	}
	
	std::string domain;
	int port;
	std::string path;
	// get domain and port by url
	if (!HttpHelper::CalcDomainAndPortByUrl(m_url, domain, port, path))
	{
		m_failed_reason = "NetSystem::CalcDomainAndPortByUrl failed:" + m_url;
		return false;
	}

	std::string request;
	if (m_content.size())
	{
		// generate POST head
		HttpHelper::GeneratePostRequestHead(domain, path, m_content, request);
	}
	else
	{
		// generate GET head
		HttpHelper::GenerateGetRequestHead(domain, path, request);
	}

	if (!m_socket)
	{
		m_failed_reason = std::string() + "Socket Create failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}

#ifdef __IPHONEOS__
	// start connect
	if (SDLNet_TCP_IPV6SocketConnect(m_socket, domain.c_str(), port)<0)
	{
		m_failed_reason = std::string() + "SDLNet_TCP_IPV6SocketConnect failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}
#else
	IPaddress st_ip;
	// resolve IP host
	if (SDLNet_ResolveHost(&st_ip, domain.c_str(), port) < 0)
	{
		m_failed_reason = std::string() + "SDLNet_ResolveHost failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}

	// start connect
	if (SDLNet_TCP_SocketConnect(&st_ip, m_socket)<0)
	{
		m_failed_reason = std::string() + "SDLNet_TCP_SocketConnect failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}
#endif

	// send request
	if (NetHelper::TCPSocketSend(m_socket, (void*)request.c_str(), static_cast<int>(request.size())) < static_cast<int>(request.size()))
	{
		m_failed_reason = std::string() + "NetHelper::TCPSocketSend failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}

	// receive buffer
	char response_buffer[HTTP_RESPONSE_BUFFER_SIZE] = {0};

	// HTTP head
	std::string response_head;
	int len = 0;
	int binary_offset = 0;
	bool http_end = false;
	do 
	{
		// is connect to receive
		if (m_continue_load == false)
		{
			m_failed_reason = "http cancel";
			return false;
		}

		// receive response
		len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
		if (len > 0)
		{
			// check receive \r\n\r\n
			int current_size = (int)response_head.size();
			response_head.append(response_buffer, len);
			int find_start_pos = current_size - static_cast<int>(strlen("\r\n\r\n"));
			if (find_start_pos < 0) find_start_pos = 0;

			size_t find_pos = response_head.find("\r\n\r\n", find_start_pos);
			if (find_pos != std::string::npos)
			{
				// check byte count behind \r\n\r\n 
				binary_offset = static_cast<int>(find_pos) + static_cast<int>(strlen("\r\n\r\n")) - current_size;
				http_end = true;
				break;
			}
		}
	} while (len > 0);

	// there has not http head
	if (http_end == false)
	{
		m_failed_reason = "can't find \\r\\n\\r\\n in HTTP response!" + m_url;
		return false;
	}

	// check status
	if (!HttpHelper::CalcStatusFromHttp(response_head, m_status))
	{
		m_failed_reason = "NetHelper::CalcStatusFromHttpResponse failed!, " + response_head;
		return false;
	}

	bool status_200 = (m_status == "200");

	// get file size of response
	int total_size = 0;
	HttpHelper::ResponseType response_type = HttpHelper::ResponseType::RESPONSE_TYPE_CONTENT_LENGTH;
	// check size
	if (HttpHelper::CalcFileSizeFromHttp(response_head, total_size, response_type))
	{
		m_response.reserve(static_cast<size_t>(total_size) + 1);

		// append content
		for (int i = binary_offset; i < len; ++i) m_response.push_back(response_buffer[i]);

		// dec size of append
		total_size -= len - binary_offset;
		// check total size
		if (total_size <= 0) return status_200;

		do
		{
			// check continue or not
			if (m_continue_load == false)
			{
				m_failed_reason = "http cancel";
				return false;
			}

			// receive response
			len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
			if (len > 0)
			{
				// add to m_response
				for (int i = 0; i < len; ++i) m_response.push_back(response_buffer[i]);
				total_size -= len;
				// check completed
				if (total_size <= 0) return status_200;
			}
		}
		while(len > 0);

		if (m_continue_load == false)
		{
			m_failed_reason = "http cancel";
			return false;
		}

		return status_200;
	}

	// append content to chunk buffer
	for (int i = binary_offset; i < len; ++i) m_chunk_buffer.push_back(response_buffer[i]);

	std::vector<char> split_r_n; split_r_n.push_back('\r'); split_r_n.push_back('\n');
	std::vector<char> split_space; split_space.push_back(' ');
	// handle chunk
	while (true)
	{
		// check continue or not
		if (m_continue_load == false)
		{
			m_failed_reason = "http cancel";
			return false;
		}

		int start_index = -1, end_index = -1;
		bool result = NetHelper::VectorCharFindString(m_chunk_buffer, split_r_n, start_index, end_index);
		if (result == false)
		{
			// check continue or not
			if (m_continue_load == false)
			{
				m_failed_reason = "http cancel";
				return false;
			}

			len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
			if (len <= 0)
			{
				m_failed_reason = "SDLNet_TCP_Recv failed";
				return false;
			}
			for (int i = 0; i < len; ++i) m_chunk_buffer.push_back(response_buffer[i]);
		}
		else if (start_index == 0) // pop \r\n
		{
			for (size_t i = 2; i < m_chunk_buffer.size(); ++i)
				m_chunk_buffer[i - 2] = m_chunk_buffer[i];
			if (m_chunk_buffer.size() >= 2)
				m_chunk_buffer.resize(m_chunk_buffer.size() - 2);
		}
		else
		{
			int space_start = -1, space_end = -1;
			bool result = NetHelper::VectorCharFindString(m_chunk_buffer, split_space, space_start, space_end);
			if (result && space_start < start_index) start_index = space_start;

			std::vector<char> chunk_size;
			for (int i = 0; i < start_index; ++i) chunk_size.push_back(m_chunk_buffer[i]);
			int chunk_size_n = -1;
			if (!NetHelper::VectorChar2Hex(chunk_size, chunk_size_n))
			{
				m_failed_reason = "NetHelper::VectorChar2Hex failed";
				return false;
			}
			if (chunk_size_n <= 0) break;

			for (size_t i = end_index; i < m_chunk_buffer.size(); ++i)
				m_chunk_buffer[i-end_index] = m_chunk_buffer[i];
			if ((int)m_chunk_buffer.size() >= end_index)
				m_chunk_buffer.resize(m_chunk_buffer.size() - end_index);

			int size = (int)m_chunk_buffer.size();
			if (size >= chunk_size_n)
			{
				for (int i = 0; i < chunk_size_n; ++i) m_response.push_back(m_chunk_buffer[i]);

				for (size_t i = chunk_size_n; i < m_chunk_buffer.size(); ++i)
					m_chunk_buffer[i-chunk_size_n] = m_chunk_buffer[i];
				if ((int)m_chunk_buffer.size() >= chunk_size_n)
					m_chunk_buffer.resize(m_chunk_buffer.size() - chunk_size_n);
			}
			else
			{
				for (size_t i = 0; i < m_chunk_buffer.size(); ++i) m_response.push_back(m_chunk_buffer[i]);
				m_chunk_buffer.resize(0);

				int need_size = chunk_size_n - size;
				while (need_size > 0)
				{
					// check continue or not
					if (m_continue_load == false)
					{
						m_failed_reason = "http cancel";
						return false;
					}

					len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
					if (len <= 0)
					{
						m_failed_reason = "SDLNet_TCP_Recv failed";
						return false;
					}
					if (len <= need_size)
					{
						for (int i = 0; i < len; ++i) m_response.push_back(response_buffer[i]);
					}
					else
					{
						for (int i = 0; i < need_size; ++i) m_response.push_back(response_buffer[i]);
						for (int i = need_size; i < len; ++i) m_chunk_buffer.push_back(response_buffer[i]);
					}
					need_size -= len;
				}
			}
		}
	}

	if (m_continue_load == false)
	{
		m_failed_reason = "http cancel";
		return false;
	}

	return status_200;
}

void HttpClient::HandleEvent(unsigned int event_type, void* data1, void* data2)
{
	HttpClient* client = (HttpClient*)data1;
	if (client->m_socket)
	{
		SDLNet_TCP_Close(client->m_socket);
		client->m_socket = nullptr;
	}
	if (event_type == NET_HTTP_SUCCEED)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpClientSucceed", client->GetID());
	else if (event_type == NET_HTTP_FAILED)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpClientFailed", client->GetID(), client->m_failed_reason.c_str());
}

} // ALittle
