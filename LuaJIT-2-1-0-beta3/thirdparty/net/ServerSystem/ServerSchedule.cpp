
#include <asio/asio.hpp>

#include "ServerSchedule.h"

#include "../Helper/StringHelper.h"
#include "../Helper/HttpHelper.h"
#include "../Helper/FileHelper.h"

#include "../HttpSystem/HttpClientText.h"
#include "../HttpSystem/HttpClientPost.h"

extern "C" {
#include "../net.h"
}

namespace ALittle
{

ServerSchedule::ServerSchedule()
{
    m_is_exit = false;
}

ServerSchedule::~ServerSchedule()
{
}

void ServerSchedule::RunOne()
{
	asio::error_code ec;
	m_io_service.run_one(ec);
}

void ServerSchedule::Exit()
{
	if (m_is_exit) return;
	m_is_exit = true;
	m_io_service.stop();
}

void ServerSchedule::HttpDownload(_net* c, int id, const char* url, const char* file_path)
{
	HttpClientTextPtr client = HttpClientTextPtr(new HttpClientText);
	client->SendRequest(url, true, "text/html", "", 0
		, [this, id, c](bool result, const std::string& body, const std::string& head)
		{
			net_event* event = (net_event*)malloc(sizeof(net_event));
			event->id = id;
			event->next = 0;
			event->content = 0;
			event->total_size = 0;
			event->cur_size = 0;
			if (result)
				event->type = net_event_types::HTTP_FILE_SUCCEED;
			else
				event->type = net_event_types::HTTP_FILE_FAILED;
			net_addevent(c, event, 1);
		}
		, [this, id, c](int total_size, int cur_size)
		{
			net_event* event = (net_event*)malloc(sizeof(net_event));
			event->id = id;
			event->next = 0;
			event->content = 0;
			event->total_size = total_size;
			event->cur_size = cur_size;
			event->type = net_event_types::HTTP_FILE_PROGRESS;
			net_addevent(c, event, 0);
		}, &m_io_service, file_path, "");
}

void ServerSchedule::HttpUpload(_net* c, int id, const char* url, const char* file_path)
{
	HttpClientPostPtr client = HttpClientPostPtr(new HttpClientPost);
	client->SendRequest(url, std::map<std::string, std::string>()
		, FileHelper::GetJustFileNameByPath(file_path), file_path
		, [this, id, c](bool result, const std::string& body, const std::string& head)
		{
			net_event* event = (net_event*)malloc(sizeof(net_event));
			event->id = id;
			event->next = 0;
			event->content = 0;
			event->total_size = 0;
			event->cur_size = 0;
			if (result)
				event->type = net_event_types::HTTP_FILE_SUCCEED;
			else
				event->type = net_event_types::HTTP_FILE_FAILED;
			net_addevent(c, event, 1);
		}
		, [this, id, c](int total_size, int cur_size)
		{
			net_event* event = (net_event*)malloc(sizeof(net_event));
			event->id = id;
			event->next = 0;
			event->content = 0;
			event->total_size = total_size;
			event->cur_size = cur_size;
			event->type = net_event_types::HTTP_FILE_PROGRESS;
			net_addevent(c, event, 0);
		}, &m_io_service, "");
}

void ServerSchedule::HttpGet(net* c, int id, const char* url)
{
	HttpClientTextPtr client = HttpClientTextPtr(new HttpClientText);
	client->SendRequest(url, true, "text/html", "", 0
		, [this, id, c](bool result, const std::string& body, const std::string& head)
		{
			net_event* event = (net_event*)malloc(sizeof(net_event));
			event->id = id;
			event->next = 0;
			event->total_size = 0;
			event->cur_size = 0;
			event->content = (kstring_t*)calloc(1, sizeof(kstring_t));
			if (result)
			{
				event->type = net_event_types::HTTP_SUCCEED;
				kputs(body.c_str(), event->content);
			}	
			else
			{
				event->type = net_event_types::HTTP_FAILED;
				kputs(head.c_str(), event->content);
			}
			net_addevent(c, event, 1);
		}, nullptr, &m_io_service, "", "");
}

void ServerSchedule::HttpPost(net* c, int id, const char* url, const char* type, const char* content)
{
	HttpClientTextPtr client = HttpClientTextPtr(new HttpClientText);
	client->SendRequest(url, false, type, content, strlen(content)
		, [this, id, c](bool result, const std::string& body, const std::string& head)
		{
			net_event* event = (net_event*)malloc(sizeof(net_event));
			event->id = id;
			event->next = 0;
			event->total_size = 0;
			event->cur_size = 0;
			event->content = (kstring_t*)calloc(1, sizeof(kstring_t));
			if (result)
			{
				event->type = net_event_types::HTTP_SUCCEED;
				kputs(body.c_str(), event->content);
			}
			else
			{
				event->type = net_event_types::HTTP_FAILED;
				kputs(head.c_str(), event->content);
			}
			net_addevent(c, event, 1);
		}, nullptr, &m_io_service, "", "");
}

} // ALittle
