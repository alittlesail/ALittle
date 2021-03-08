
#ifndef _ALITTLE_SIPSCHEDULE_H_
#define _ALITTLE_SIPSCHEDULE_H_

#include "carp_schedule.hpp"
#include "carp_lua.hpp"
#include "carp_string.hpp"
#include "carp_log.hpp"
#include "carp_udp_server.hpp"
#include "carp_timer.hpp"

extern "C" {
#include "sip-agent.h"
#include "sip-timer.h"
}

class SipSchedule : public CarpSchedule
{
public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginNamespace("sip")
			.beginClass<SipSchedule>("SipSchedule")
			.addConstructor<void(*)()>()
		    .addFunction("Start", &SipSchedule::Start)
			.addFunction("Close", &SipSchedule::Close)
			.addFunction("Register", &SipSchedule::Register)
		    .addCFunction("PullEvent", &SipSchedule::PullEvent)
			.endClass()
            .addFunction("Setup", SipSchedule::Setup)
			.endNamespace();
	}

    static void Setup(const char* log_path, const char* log_name)
	{
        s_carp_log.Setup(log_path, log_name, false);
	}

public:
	SipSchedule();

public:
	// 启动SIP
    bool Start(const char* self_sip_ip, unsigned int self_sip_port, const char* remote_sip_ip, unsigned int remote_sip_port);
	// 关闭
    void Close();
	// 发送数据包
	void Send(void* memory, size_t size) { m_udp_self_sip->Send(memory, size, m_remote_sip_endpoint); }

public:
	struct TimerNode
	{
		int timer_id = 0;
		sip_timer_handle handle = nullptr;
		void* usrptr = nullptr;
	};
	int AddTimer(int timeout, sip_timer_handle handle, void* usrptr);
	void RemoveTimer(int id);

public:
	// 注册号码
	void Register(const char* account, const char* password, const char* show_account);

private:
	void HandleRemoteSip(CarpUdpServer::HandleInfo& info);

public:
    void PushEvent(std::function<int(lua_State*)> func);
    int PullEvent(lua_State* l_state);

private:
	CarpUdpServerPtr m_udp_self_sip;
	std::string m_self_sip_ip;
	unsigned int m_self_sip_port = 0;

	std::string m_remote_sip_ip;
	unsigned int m_remote_sip_port = 0;
	asio::ip::udp::endpoint m_remote_sip_endpoint;

private:
	std::mutex m_mutex;
	std::list<std::function<int(lua_State*)>> m_event;

private:
	CarpTimer m_timer;
	std::unordered_map<int, TimerNode> m_timer_map;

private:
	sip_agent_t* m_agent = nullptr;
};

#endif
