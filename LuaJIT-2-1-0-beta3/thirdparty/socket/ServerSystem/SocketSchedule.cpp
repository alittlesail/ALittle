
#include <asio/asio.hpp>

#include "SocketSchedule.h"

#include "../ClientSystem/ConnectClient.h"

extern "C" {
#include "../socket.h"
}

namespace ALittle
{

SocketSchedule::SocketSchedule() : m_importer(0), m_is_exit(0), m_factory(0)
{
}

SocketSchedule::~SocketSchedule()
{
}

void SocketSchedule::RunOne()
{
	asio::error_code ec;
	if (m_io_service.run_one(ec) == 0)
	{
		m_io_service.restart();
		m_io_service.run_one(ec);
	}
}

void SocketSchedule::Exit()
{
	if (m_is_exit) return;
	m_is_exit = true;
	m_io_service.stop();
}

void SocketSchedule::Connect(_socket* c, int id, const char* ip, int port)
{
	ConnectClientPtr client;
	auto it = m_connect_map.find(id);
	if (it != m_connect_map.end())
		client = it->second;
	else
		client = ConnectClientPtr(new ConnectClient(c, this, id));
	client->Connect(ip, port);
}

void SocketSchedule::Close(_socket* c, int id)
{
	auto it = m_connect_map.find(id);
	if (it == m_connect_map.end()) return;
	it->second->Close();
	m_connect_map.erase(it);
}

ConnectClientPtr SocketSchedule::GetClient(int id)
{
	auto it = m_connect_map.find(id);
	if (it == m_connect_map.end())
		return nullptr;
	return it->second;
}

bool SocketSchedule::SetProtobufRoot(const std::string& path)
{
	return false;
}

bool SocketSchedule::LoadProtobufFile(const std::string& path)
{
	return false;
}

void SocketSchedule::Timer(_socket* c, int delay_ms)
{
	if (!m_timer)
		m_timer = AsioTimerPtr(new AsioTimer(m_io_service, std::chrono::milliseconds(delay_ms)));
	else
		m_timer->expires_after(std::chrono::milliseconds(delay_ms));

	m_timer->async_wait(std::bind(&SocketSchedule::Update, this, std::placeholders::_1, c));
}

void SocketSchedule::Update(const asio::error_code& ec, _socket* c)
{
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	
	socket_event* event = socket_createevent(c);
	event->type = socket_event_types::TIMER;
	event->time = (int)time;
	socket_addevent(c, event, 1);
}

void SocketSchedule::Execute(std::function<void()> func)
{
	m_io_service.post(func);
}

} // ALittle
