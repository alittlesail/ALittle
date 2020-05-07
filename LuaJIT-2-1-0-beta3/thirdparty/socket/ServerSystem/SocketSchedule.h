
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

#include "google/protobuf/compiler/importer.h"
#include "google/protobuf/dynamic_message.h"

struct _socket;

namespace ALittle
{

typedef asio::basic_waitable_timer<std::chrono::system_clock> AsioTimer;
typedef std::shared_ptr<AsioTimer> AsioTimerPtr;

class ConnectClient;
typedef std::shared_ptr<ConnectClient> ConnectClientPtr;

class SocketSchedule
{
public:
	SocketSchedule();
	~SocketSchedule();

	friend class ConnectClient;

public:
	void RunOne();
	void Exit();

public:
	void Connect(struct _socket* c, int id, const char* ip, int port);
	void Close(struct _socket* c, int id);
	ConnectClientPtr GetClient(int id);

	size_t GetConnectCount() { return m_connect_map.size(); }

public:
	bool SetProtobufRoot(const std::string& path);
	bool LoadProtobufFile(const std::string& path);

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
	std::unordered_map<int, ConnectClientPtr> m_connect_map;

private:
	// 导入信息
	google::protobuf::compiler::Importer* m_importer;
	google::protobuf::DynamicMessageFactory* m_factory;
};

} // ALittle

#endif // _ALITTLE_SOCKETSCHEDULE_H_
