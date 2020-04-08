
#include <asio/asio.hpp>

#include "ServerSchedule.h"

#include "../Helper/StringHelper.h"
#include "../Helper/HttpHelper.h"
#include "../Helper/FileHelper.h"

#include "../HttpSystem/HttpClientText.h"
#include "../HttpSystem/HttpClientPost.h"
#include "../ClientSystem/ConnectClient.h"

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
	if (m_io_service.run_one(ec) == 0)
	{
		m_io_service.restart();
		m_io_service.run_one(ec);
	}
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
	m_download_map[id] = client;
	client->SendRequest(url, true, "text/html", "", 0
		, [this, id, c](bool result, const std::string& body, const std::string& head, const std::string& error)
		{
			m_download_map.erase(id);
			net_event* event = net_createevent(c);
			event->id = id;
			if (result)
				event->type = net_event_types::HTTP_FILE_SUCCEED;
			else
			{
				event->error = (kstring_t*)calloc(1, sizeof(kstring_t));
				kputs(error.c_str(), event->error);
				event->type = net_event_types::HTTP_FILE_FAILED;
			}
			net_addevent(c, event, 1);
		}
		, [this, id, c](int total_size, int cur_size)
		{
			net_event* event = net_createevent(c);
			event->id = id;
			event->total_size = total_size;
			event->cur_size = cur_size;
			event->type = net_event_types::HTTP_FILE_PROGRESS;
			net_addevent(c, event, 0);
		}, &m_io_service, file_path, "");
}

void ServerSchedule::HttpUpload(_net* c, int id, const char* url, const char* file_path)
{
	HttpClientPostPtr client = HttpClientPostPtr(new HttpClientPost);
	m_upload_map[id] = client;
	client->SendRequest(url, std::map<std::string, std::string>()
		, FileHelper::GetJustFileNameByPath(file_path), file_path
		, [this, id, c](bool result, const std::string& body, const std::string& head, const std::string& error)
		{
			m_upload_map.erase(id);
			net_event* event = net_createevent(c);
			event->id = id;
			if (result)
				event->type = net_event_types::HTTP_FILE_SUCCEED;
			else
			{
				event->error = (kstring_t*)calloc(1, sizeof(kstring_t));
				kputs(error.c_str(), event->error);
				event->type = net_event_types::HTTP_FILE_FAILED;
			}
			net_addevent(c, event, 1);
		}
		, [this, id, c](int total_size, int cur_size)
		{
			net_event* event = net_createevent(c);
			event->id = id;
			event->total_size = total_size;
			event->cur_size = cur_size;
			event->type = net_event_types::HTTP_FILE_PROGRESS;
			net_addevent(c, event, 0);
		}, &m_io_service, "");
}

void ServerSchedule::HttpStopGet(_net* c, int id)
{
	auto it = m_get_map.find(id);
	if (it == m_get_map.end()) return;

	it->second->Stop();
}

void ServerSchedule::HttpStopPost(_net* c, int id)
{
	auto it = m_post_map.find(id);
	if (it == m_post_map.end()) return;

	it->second->Stop();
}

void ServerSchedule::HttpStopDownload(_net* c, int id)
{
	auto it = m_download_map.find(id);
	if (it == m_download_map.end()) return;

	it->second->Stop();
}

void ServerSchedule::HttpStopUpload(_net* c, int id)
{
	auto it = m_upload_map.find(id);
	if (it == m_upload_map.end()) return;

	it->second->Stop();
}

void ServerSchedule::Connect(_net* c, int id, const char* ip, int port)
{
	ConnectClientPtr client;
	auto it = m_connect_map.find(id);
	if (it != m_connect_map.end())
		client = it->second;
	else
		client = ConnectClientPtr(new ConnectClient(c, this, id));
	client->Connect(ip, port);
}

bool ServerSchedule::IsConnected(_net* c, int id)
{
	auto it = m_connect_map.find(id);
	if (it == m_connect_map.end()) return false;
	return it->second->IsConnected();
}

bool ServerSchedule::IsConnecting(_net* c, int id)
{
	auto it = m_connect_map.find(id);
	if (it == m_connect_map.end()) return false;
	return it->second->IsConnecting();
}

void ServerSchedule::Close(_net* c, int id)
{
	auto it = m_connect_map.find(id);
	if (it == m_connect_map.end()) return;
	it->second->Close();
	m_connect_map.erase(it);
}

void ServerSchedule::Send(_net* c, int id, _write_factory* factory)
{
	auto it = m_connect_map.find(id);
	if (it == m_connect_map.end()) return;

	it->second->Send(factory);
}

void ServerSchedule::Timer(_net* c, int delay_ms)
{
	if (!m_timer)
		m_timer = AsioTimerPtr(new AsioTimer(m_io_service, std::chrono::milliseconds(delay_ms)));
	else
		m_timer->expires_after(std::chrono::milliseconds(delay_ms));

	m_timer->async_wait(std::bind(&ServerSchedule::Update, this, std::placeholders::_1, c));
}

void ServerSchedule::Update(const asio::error_code& ec, _net* c)
{
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	
	net_event* event = net_createevent(c);
	event->type = net_event_types::TIMER;
	event->time = (int)time;
	net_addevent(c, event, 1);
}

void ServerSchedule::Execute(std::function<void()> func)
{
	m_io_service.post(func);
}

void ServerSchedule::HttpGet(struct _net* c, int id, const char* url)
{
	HttpClientTextPtr client = HttpClientTextPtr(new HttpClientText);
	m_get_map[id] = client;
	client->SendRequest(url, true, "text/html", "", 0
		, [this, id, c](bool result, const std::string& body, const std::string& head, const std::string& error)
		{
			m_get_map.erase(id);
			net_event* event = net_createevent(c);
			event->id = id;
			if (result)
			{
				event->content = (kstring_t*)calloc(1, sizeof(kstring_t));
				kputs(body.c_str(), event->content);
				event->type = net_event_types::HTTP_SUCCEED;
			}	
			else
			{
				event->error = (kstring_t*)calloc(1, sizeof(kstring_t));
				kputs(error.c_str(), event->error);
				event->type = net_event_types::HTTP_FAILED;
			}
			net_addevent(c, event, 1);
		}, nullptr, &m_io_service, "", "");
}

void ServerSchedule::HttpPost(struct _net* c, int id, const char* url, const char* type, const char* content)
{
	HttpClientTextPtr client = HttpClientTextPtr(new HttpClientText);
	m_post_map[id] = client;
	client->SendRequest(url, false, type, content, strlen(content)
		, [this, id, c](bool result, const std::string& body, const std::string& head, const std::string& error)
		{
			m_post_map.erase(id);
			net_event* event = net_createevent(c);
			event->id = id;
			if (result)
			{
				event->content = (kstring_t*)calloc(1, sizeof(kstring_t));
				kputs(body.c_str(), event->content);
				event->type = net_event_types::HTTP_SUCCEED;
			}
			else
			{
				event->error = (kstring_t*)calloc(1, sizeof(kstring_t));
				kputs(error.c_str(), event->error);
				event->type = net_event_types::HTTP_FAILED;
			}
			net_addevent(c, event, 1);
		}, nullptr, &m_io_service, "", "");
}

} // ALittle
