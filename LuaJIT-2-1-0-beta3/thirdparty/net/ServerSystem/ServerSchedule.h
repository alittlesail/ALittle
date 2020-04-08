
#ifndef _ALITTLE_SERVERSCHEDULE_H_
#define _ALITTLE_SERVERSCHEDULE_H_

#include <set>
#include <map>
#include <string>
#include <thread>
#include <functional>
#include <unordered_map>
#include <asio.hpp>

struct _net;

namespace ALittle
{

typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class HttpClientText;
typedef std::shared_ptr<HttpClientText> HttpClientTextPtr;
class HttpClientPost;
typedef std::shared_ptr<HttpClientPost> HttpClientPostPtr;

class ConnectClient;
typedef std::shared_ptr<ConnectClient> ConnectClientPtr;

class ServerSchedule
{
public:
	ServerSchedule();
	~ServerSchedule();

public:
	void RunOne();
	void Exit();

public:
	void HttpGet(struct _net* c, int id, const char* url);
	void HttpPost(struct _net* c, int id, const char* url, const char* type, const char* content);
	void HttpDownload(struct _net* c, int id, const char* url, const char* file_path);
	void HttpUpload(struct _net* c, int id, const char* url, const char* file_path);

	void HttpStopGet(struct _net* c, int id);
	void HttpStopPost(struct _net* c, int id);
	void HttpStopDownload(struct _net* c, int id);
	void HttpStopUpload(struct _net* c, int id);

public:
	void Connect(struct _net* c, int id, const char* ip, int port);
	bool IsConnected(struct _net* c, int id);
	bool IsConnecting(struct _net* c, int id);
	void Close(struct _net* c, int id);
	void Send(struct _net* c, int id, write_factory* factory);
	size_t GetConnectCount() { return m_connect_map.size(); }

public:
	void Timer(struct _net* c, int delay_ms);
private:
	void Update(const asio::error_code& ec, _net* c);

public:
	bool IsExit() const { return m_is_exit; }
private:
	bool m_is_exit;
	
private:
	asio::io_service m_io_service;
	AsioTimerPtr m_timer;

private:
	std::unordered_map<int, HttpClientTextPtr> m_get_map;
	std::unordered_map<int, HttpClientTextPtr> m_post_map;
	std::unordered_map<int, HttpClientTextPtr> m_download_map;
	std::unordered_map<int, HttpClientPostPtr> m_upload_map;

	std::unordered_map<int, ConnectClientPtr> m_connect_map;
};

} // ALittle

#endif // _ALITTLE_SERVERSCHEDULE_H_
