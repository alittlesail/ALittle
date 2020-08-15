
#include "HttpFile.h"

#include "ALittle/LibCommon/Helper/FileHelper.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/HttpHelper.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/Helper/FileHelperEx.h"

#include <SDL.h>
#include <SDL_net.h>
#include <stdio.h>

namespace ALittle
{

SafeIDCreator<int> HttpFile::s_id_creator;

#define CONTENT_TYPE_BOUNDARY "----WebKitFormBoundarywP43vY132opdlHoz"

HttpFile::HttpFile()
: m_total_size(0)
, m_cur_size(0)
, m_start_size(0)
, m_continue_load(true)
, m_socket(0)
, m_download(false)
{
	m_id = s_id_creator.CreateID();
}

HttpFile::~HttpFile()
{
	s_id_creator.ReleaseID(m_id);
	if (m_socket) SDLNet_TCP_Close(m_socket);
}

const char* HttpFile::GetStatus()
{
	return m_status.c_str();
}

const char* HttpFile::GetContent()
{
	return m_response.c_str();
}

const char* HttpFile::GetPath()
{
	return m_file_path.c_str();
}

void HttpFile::SetURL(const char* url, const char* file_path, bool download, int start_size)
{
	if (m_socket)
	{
		ALITTLE_ERROR("socket already exist!");
		return;
	}

	m_url = url;
	m_file_path = file_path;
	m_download = download;
	m_start_size = start_size;
	m_response = "";
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

int HttpFile::GetID() const
{
	return m_id;
}

unsigned int HttpFile::GetTotalSize() const
{
	return m_total_size;
}

unsigned int HttpFile::GetCurSize() const
{
	return m_cur_size;
}

void HttpFile::Start()
{
	g_ThreadSystem.AddTask(this, ThreadSystem::THREAD_TYPE_SLOW);
}

void HttpFile::Stop()
{
	m_continue_load = false;
#ifdef __IPHONEOS__
	if (m_socket) SDLNet_TCP_JustClose(m_socket);
#else
	if (m_socket) SDLNet_TCP_JustShutdown(m_socket);
#endif
}

void HttpFile::Execute()
{
	m_failed_reason.clear();
	if (m_download)
	{
		m_chunk_buffer.resize(0);
		bool result = Download();
		m_chunk_buffer.clear();
		if (result)
			g_ScheduleSystem.PushUserEvent(HTTP_DOWNLOAD_SUCCEED_EVENT, (void*)this);
		else
		{
			if (m_failed_reason.empty()) m_failed_reason = "status is not 200";
			g_ScheduleSystem.PushUserEvent(HTTP_DOWNLOAD_FAILED_EVENT, (void*)this);
		}
	}
	else
	{
		if (Upload())
			g_ScheduleSystem.PushUserEvent(HTTP_UPLOAD_SUCCEED_EVENT, (void*)this);
		else
		{
			if (m_failed_reason.empty()) m_failed_reason = "status is not 200";
			g_ScheduleSystem.PushUserEvent(HTTP_UPLOAD_FAILED_EVENT, (void*)this);
		}
	}
}

void HttpFile::Abandon()
{
	m_failed_reason = "abandon http file";
	if (m_download)
		g_ScheduleSystem.PushUserEvent(HTTP_DOWNLOAD_FAILED_EVENT, (void*)this);
	else
		g_ScheduleSystem.PushUserEvent(HTTP_UPLOAD_FAILED_EVENT, (void*)this);
}

#define HTTP_RESPONSE_BUFFER_SIZE 1024

bool HttpFile::Download()
{
	if (m_continue_load == false)
	{
		m_failed_reason = "http file cancel";
		return false;
	}

	// init current size is 0
	m_cur_size = 0;
	// init total size is 0
	m_total_size = 0;

	// get domain and port from url
	std::string domain;
	int port;
	std::string path;
	if (!HttpHelper::CalcDomainAndPortByUrl(m_url, domain, port, path))
	{
		m_failed_reason = "NetHelper::CalcDomainAndPortByUrl failed:" + m_url;
		return false;
	}

	// generate HTTP head
	std::string request_head;
	HttpHelper::GenerateGetRequestHead(domain, path, request_head);
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
	// send head
	if (NetHelper::TCPSocketSend(m_socket, (void*)request_head.c_str(), static_cast<int>(request_head.size())) < static_cast<int>(request_head.size()))
	{
		m_failed_reason = std::string() + "NetHelper::TCPSocketSend failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}

	// buffer
	char response_buffer[HTTP_RESPONSE_BUFFER_SIZE] = {0};

	// HTTP
	std::string response_head;
	int len = 0;
	int binary_offset = 0;
	bool http_end = false;
	do 
	{
		// receive bytes
		len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
		if (len > 0)
		{
			int current_size = (int)response_head.size();
			response_head.append(response_buffer, len);
			int find_start_pos = current_size - static_cast<int>(strlen("\r\n\r\n"));
			if (find_start_pos < 0) find_start_pos = 0;

			size_t find_pos = response_head.find("\r\n\r\n", find_start_pos);
			if (find_pos != std::string::npos)
			{
				binary_offset = static_cast<int>(find_pos) + static_cast<int>(strlen("\r\n\r\n")) - current_size;
				http_end = true;
				break;
			}
		}
	} while (len > 0);

	// check receive \r\n\r\n or not
	if (http_end == false)
	{
		m_failed_reason = "can't find \\r\\n\\r\\n in HTTP response!";
		return false;
	}
	
	// get status in head
	if (!HttpHelper::CalcStatusFromHttp(response_head, m_status))
	{
		m_failed_reason = "NetHelper::CalcStatusFromHttpResponse failed!, " + response_head;
		return false;
	}

	// define file pointer
	SDL_RWops* file = 0;
	if (m_start_size > 0)
	{
		// open file with mode rb+
		file = FileHelperEx::OpenFile(m_file_path, false, "rb+");
		if (!file)
		{
			m_failed_reason = m_file_path + " open failed with mode:rb+";
			return false;
		}
		// seek file to start_size
		SDL_RWseek(file, m_start_size, RW_SEEK_SET);
		m_cur_size = m_start_size;
		m_total_size += m_cur_size;
	}
	else
	{
		file = FileHelperEx::OpenFile(m_file_path, false, "wb");
		if (!file)
		{
			m_failed_reason = m_file_path + " open failed with mode:wb";
			return false;
		}
	}

	bool status_200 = (m_status == "200");

	// get file size in response
	int total_size = 0;
	HttpHelper::ResponseType response_type = HttpHelper::ResponseType::RESPONSE_TYPE_CONTENT_LENGTH;
	if (HttpHelper::CalcFileSizeFromHttp(response_head, total_size, response_type))
	{
		if (total_size <= 0) { SDL_RWclose(file); return status_200; }
		m_total_size += total_size;

		// handle bytes behind \r\n\r\n
		if (binary_offset < len)
		{
			// set current size
			m_cur_size += len - binary_offset;
			// write to file
			SDL_RWwrite(file, response_buffer + binary_offset, 1, static_cast<size_t>(len) - static_cast<size_t>(binary_offset));
			g_ScheduleSystem.PushUserEvent(HTTP_DOWNLOADING_EVENT, (void*)this);

			if (m_cur_size >= m_total_size) { SDL_RWclose(file); return status_200; }
		}

		// continue receive data
		do
		{
			if (m_continue_load == false)
			{
				m_failed_reason = "http file cancel";
				SDL_RWclose(file); return false;
			}

			len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
			if (len > 0)
			{
				SDL_RWwrite(file, response_buffer, 1, len);
				m_cur_size += len;

				g_ScheduleSystem.PushUserEvent(HTTP_DOWNLOADING_EVENT, (void*)this);

				if (m_cur_size >= m_total_size) break;
			}
			else
			{
				m_failed_reason = std::string() + "SDLNet_TCP_Recv failed:" + SDL_GetError();
				// close file
				SDL_RWclose(file);
				return false;
			}
		}
		while(len > 0);

		// close file
		SDL_RWclose(file);
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
			m_failed_reason = "http file cancel";
			SDL_RWclose(file);
			return false;
		}

		int start_index = -1, end_index = -1;
		bool result = NetHelper::VectorCharFindString(m_chunk_buffer, split_r_n, start_index, end_index);
		if (result == false)
		{
			// check continue or not
			if (m_continue_load == false)
			{
				m_failed_reason = "http file cancel";
				SDL_RWclose(file);
				return false;
			}

			len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
			if (len <= 0)
			{
				m_failed_reason = std::string() + "SDLNet_TCP_Recv failed:" + SDL_GetError();
				SDL_RWclose(file);
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
				m_failed_reason = "NetHelper::VectorChar2Hex failed!";
				SDL_RWclose(file);
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
				SDL_RWwrite(file, &m_chunk_buffer[0], 1, chunk_size_n);
				// for (int i = 0; i < chunk_size_n; ++i) m_response.push_back(m_chunk_buffer[i]);

				for (size_t i = chunk_size_n; i < m_chunk_buffer.size(); ++i)
					m_chunk_buffer[i-chunk_size_n] = m_chunk_buffer[i];
				if ((int)m_chunk_buffer.size() >= chunk_size_n)
					m_chunk_buffer.resize(m_chunk_buffer.size() - chunk_size_n);
			}
			else
			{
				SDL_RWwrite(file, &m_chunk_buffer[0], 1, m_chunk_buffer.size());
				// for (unsigned int i = 0; i < m_chunk_buffer.size(); ++i) m_response.push_back(m_chunk_buffer[i]);
				m_chunk_buffer.resize(0);

				int need_size = chunk_size_n - size;
				while (need_size > 0)
				{
					// check continue or not
					if (m_continue_load == false)
					{
						m_failed_reason = "http file cancel";
						SDL_RWclose(file);
						return false;
					}

					len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
					if (len <= 0)
					{
						m_failed_reason = std::string() + "SDLNet_TCP_Recv failed:" + SDL_GetError();
						SDL_RWclose(file);
						return false;
					}
					if (len <= need_size)
					{
						SDL_RWwrite(file, response_buffer, 1, len);
						// for (int i = 0; i < len; ++i) m_response.push_back(response_buffer[i]);
					}
					else
					{
						SDL_RWwrite(file, response_buffer, 1, need_size);
						// for (int i = 0; i < need_size; ++i) m_response.push_back(response_buffer[i]);
						for (int i = need_size; i < len; ++i) m_chunk_buffer.push_back(response_buffer[i]);
					}
					need_size -= len;
				}
			}
		}
	}

	if (m_continue_load == false)
	{
		m_failed_reason = "http file cancel";
		SDL_RWclose(file);
		return false;
	}

	SDL_RWclose(file);
	return status_200;
}

bool HttpFile::Upload()
{
	if (m_continue_load == false)
	{
		m_failed_reason = "http file cancel";
		return false;
	}

	// init current size
	m_cur_size = 0;
	// init total size
	m_total_size = 0;

	// get domain and port from url
	std::string domain;
	int port;
	std::string path;
	if (!HttpHelper::CalcDomainAndPortByUrl(m_url, domain, port, path))
	{
		m_failed_reason = "NetHelper::CalcDomainAndPortByUrl failed:" + m_url;
		return false;
	}

	SDL_RWops* file = FileHelperEx::OpenFile(m_file_path, false, "rb");
	if (!file)
	{
		m_failed_reason = "can't open file:" + m_file_path;
		return false;
	}

	// get file size
	SDL_RWseek(file, 0, RW_SEEK_END);
	m_total_size = static_cast<unsigned int>(SDL_RWtell(file));
	SDL_RWseek(file, 0, RW_SEEK_SET);

	// calc upload size
	unsigned int upload_size = m_total_size;

	// seek file to start_size
	if (m_start_size > 0)
	{
		// seek file to start_size
		SDL_RWseek(file, m_start_size, RW_SEEK_SET);
		upload_size -= m_start_size;
		m_cur_size = m_start_size;
	}

	std::string request_file_begin;
	request_file_begin.append("--").append(CONTENT_TYPE_BOUNDARY).append("\r\n");
	request_file_begin.append("Content-Disposition: form-data; name=\"").append(m_file_path)
		.append("\"; filename=\"").append(m_file_path).append("\"\r\n");
	request_file_begin.append("Content-Type: application/octet-stream\r\n\r\n");

	upload_size += static_cast<int>(request_file_begin.size());

	std::string request_file_end;
	request_file_end.append("\r\n--").append(CONTENT_TYPE_BOUNDARY).append("--\r\n");

	upload_size += static_cast<int>(request_file_end.size());
	
	// generate HTTP hread
	std::string request_head;
	request_head.append("POST ").append(HttpHelper::UrlEncode(path)).append(" HTTP/1.1\r\n");
	request_head.append("Accept: */*\r\n");
	request_head.append("User-Agent: ALittle Client\r\n");
	request_head.append("Host: ").append(domain).append("\r\n");
	char text[32] = {0};
#ifdef _WIN32
	sprintf_s(text, "%d", upload_size);
#else
	sprintf(text, "%d", upload_size);
#endif
	request_head.append("Content-Type: multipart/form-data; boundary=").append(CONTENT_TYPE_BOUNDARY).append("\r\n");
	request_head.append("Content-Length: ").append(text).append("\r\n");
	request_head.append("Connection: Close\r\n");
	request_head.append("\r\n");

#ifdef __IPHONEOS__
	// start connect
	if (SDLNet_TCP_IPV6SocketConnect(m_socket, domain.c_str(), port)<0)
	{
		m_failed_reason = std::string() + "SDLNet_TCP_IPV6SocketConnect failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}
#else
	IPaddress st_ip;
	// resolve ip
	if (SDLNet_ResolveHost(&st_ip, domain.c_str(), port) < 0)
	{
		m_failed_reason = std::string() + "SDLNet_ResolveHost failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		SDL_RWclose(file);
		return false;
	}

	// start connect
	if (SDLNet_TCP_SocketConnect(&st_ip, m_socket)<0)
	{
		m_failed_reason = std::string() + "SDLNet_TCP_SocketConnect failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		SDL_RWclose(file);
		return false;
	}
#endif

	// send http head
	if (NetHelper::TCPSocketSend(m_socket, (void*)request_head.c_str(), static_cast<int>(request_head.size())) < static_cast<int>(request_head.size()))
	{
		m_failed_reason = std::string() + "NetHelper::TCPSocketSend failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		SDL_RWclose(file);
		return false;
	}

	// send http head
	if (NetHelper::TCPSocketSend(m_socket, (void*)request_file_begin.c_str(), static_cast<int>(request_file_begin.size())) < static_cast<int>(request_file_begin.size()))
	{
		m_failed_reason = std::string() + "NetHelper::TCPSocketSend failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		SDL_RWclose(file);
		return false;
	}

	// buffer
	char response_buffer[HTTP_RESPONSE_BUFFER_SIZE] = {0};

	// upload file
	int read_size = 0;
	do 
	{
		// read file
		read_size = static_cast<int>(SDL_RWread(file, response_buffer, 1, HTTP_RESPONSE_BUFFER_SIZE));
		if (read_size > 0)
		{
			// send content
			if (NetHelper::TCPSocketSend(m_socket, response_buffer, read_size) < read_size)
			{
				m_failed_reason = std::string() + "NetHelper::TCPSocketSend failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
				SDL_RWclose(file);
				return false;
			}

			// set upload size
			m_cur_size += read_size;
			g_ScheduleSystem.PushUserEvent(HTTP_UPLOADING_EVENT, (void*)this);
		}

		if (m_continue_load == false)
		{
			m_failed_reason = "http file cancel";
			// close file
			SDL_RWclose(file);
			return false;
		}
	}
	while (read_size > 0);

	// close file
	SDL_RWclose(file);

	// send upload tail
	if (NetHelper::TCPSocketSend(m_socket, (void*)request_file_end.c_str(), static_cast<int>(request_file_end.size())) < static_cast<int>(request_file_end.size()))
	{
		m_failed_reason = std::string() + "NetHelper::TCPSocketSend failed:" + SDLNet_GetError() + ", domain:" + domain + ", port:" + X2S(port);
		return false;
	}

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
			m_failed_reason = "http file cancel";
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
		m_failed_reason = "can't find \\r\\n\\r\\n in HTTP response!";
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
	if (!HttpHelper::CalcFileSizeFromHttp(response_head, total_size, response_type))
	{
		total_size = 0;
		m_failed_reason = "can't find Content-Length info!, " + response_head;
		return false;
	}

	// responses
	m_response.resize(0);
	m_response.reserve(static_cast<size_t>(total_size) + 1);

	// append content
	for (int i = binary_offset; i < len; ++i)
		m_response.push_back(response_buffer[i]);

	// dec size of append
	total_size -= len - binary_offset;
	int receive_size = len - binary_offset;
	// check total size
	if (total_size <= 0)
	{
		m_response.push_back(0);
		return status_200;
	}

	do
	{
		// check continue or not
		if (m_continue_load == false)
		{
			m_failed_reason = "http file cancel";
			m_response.push_back(0);
			return false;
		}

		len = SDLNet_TCP_Recv(m_socket, response_buffer, HTTP_RESPONSE_BUFFER_SIZE);
		if (len > 0)
		{
			// add to m_response
			for (int i = 0; i < len; ++i)
				m_response.push_back(response_buffer[i]);
			total_size -= len;
			receive_size += len;
			// check completed
			if (total_size <= 0)
			{
				m_response.push_back(0);
				return status_200;
			}
		}
	}
	while(len > 0);


	if (m_continue_load == false)
	{
		m_failed_reason = "http file cancel";
		return false;
	}

	return status_200;
}

void HttpFile::HandleEvent( unsigned int event_type, void* data1, void* data2 )
{
	HttpFile* file = (HttpFile*)data1;
	if (file == 0) return;
	if (file->m_socket && event_type != HTTP_DOWNLOADING_EVENT && event_type != HTTP_UPLOADING_EVENT)
	{
		SDLNet_TCP_Close(file->m_socket);
		file->m_socket = 0;
	}

    if (event_type == HTTP_DOWNLOADING_EVENT || event_type == HTTP_UPLOADING_EVENT)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpFileProcess", file->GetID(), file->GetCurSize(), file->GetTotalSize());
    else if (event_type == HTTP_DOWNLOAD_SUCCEED_EVENT || event_type == HTTP_UPLOAD_SUCCEED_EVENT)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpFileSucceed", file->GetID());
    else if (event_type == HTTP_DOWNLOAD_FAILED_EVENT || event_type == HTTP_UPLOAD_FAILED_EVENT)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpFileFailed", file->GetID(), file->m_failed_reason.c_str());
}

} // ALittle
