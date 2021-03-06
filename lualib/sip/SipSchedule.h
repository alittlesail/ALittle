
#ifndef _ALITTLE_SIPSCHEDULE_H_
#define _ALITTLE_SIPSCHEDULE_H_

#include "carp_schedule.hpp"
#include "carp_lua.hpp"
#include "carp_string.hpp"
#include "carp_log.hpp"
#include "carp_udp_server.hpp"

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
	// Æô¶¯SIP
    bool Start(const char* self_sip_ip, unsigned int self_sip_port, const char* remote_sip_ip, unsigned int remote_sip_port);
	// ¹Ø±Õ
    void Close();

public:
	// ×¢²áºÅÂë
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
};

#endif
