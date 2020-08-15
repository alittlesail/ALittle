
#ifndef _ALITTLE_SOCKETSCHEDULE_H_
#define _ALITTLE_SOCKETSCHEDULE_H_

#include <set>
#include <map>
#include <string>
#include <thread>
#include <functional>
#include <unordered_map>
#include <asio.hpp>

#include "lua.hpp"

struct _socket;

namespace ALittle
{

typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class SocketClient;
typedef std::shared_ptr<SocketClient> SocketClientPtr;

class SocketSchedule
{
public:
	SocketSchedule();
	~SocketSchedule();

	friend class SocketClient;

public:
	void RunOne();
	void PollOne();
	void Exit();

public:
	void Connect(struct _socket* c, int id, const char* ip, int port);
	void Close(struct _socket* c, int id);
	SocketClientPtr GetClient(int id);

	size_t GetConnectCount() { return m_connect_map.size(); }

public:
	void Timer(struct _socket* c, int delay_ms);
private:
	void Update(const asio::error_code& ec, _socket* c);

public:
	asio::io_service& GetIOService() { return m_io_service; }
	void Execute(std::function<void()> func);
	bool IsExit() const { return m_is_exit; }
private:
	bool m_is_exit;
	
private:
	asio::io_service m_io_service;
	AsioTimerPtr m_timer;

private:
	std::unordered_map<int, SocketClientPtr> m_connect_map;
};

} // ALittle

#endif // _ALITTLE_SOCKETSCHEDULE_H_
