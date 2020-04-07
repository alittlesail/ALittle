
#ifndef _ALITTLE_SERVERSCHEDULE_H_
#define _ALITTLE_SERVERSCHEDULE_H_

#include <set>
#include <map>
#include <string>
#include <thread>
#include <functional>
#include <asio.hpp>

struct _net;

namespace ALittle
{

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

public:
	asio::io_service& GetIOService() { return m_io_service; }

public:
	bool IsExit() const { return m_is_exit; }

private:
	bool m_is_exit;
	
private:
	asio::io_service m_io_service;
};

} // ALittle

#endif // _ALITTLE_SERVERSCHEDULE_H_
