
#ifndef _ALITTLE_SIPSCHEDULE_H_
#define _ALITTLE_SIPSCHEDULE_H_

#include "carp_schedule.hpp"
#include "carp_lua.hpp"
#include "carp_string.hpp"
#include "carp_log.hpp"

#include "RtpManager.h"
#include "SipManager.h"

class SipSchedule : public CarpSchedule
{
public:
	SipSchedule() : m_sip(this), m_rtp(this) {}
    ~SipSchedule();

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginNamespace("sip")
			.beginClass<SipSchedule>("SipSchedule")
			.addConstructor<void(*)()>()
		    .addCFunction("PullEvent", &SipSchedule::PullEvent)
			.endClass()
            .addFunction("Setup", SipSchedule::Setup)
			.endNamespace();
	}

    static void Setup(const char* log_path, const char* log_name)
	{
        s_carp_log.Setup(log_path, log_name, false);
	}

	void PushEvent(std::function<int(lua_State*)> func) { m_event.push_back(func); }
	int PullEvent(lua_State* l_state)
	{
		if (m_event.empty()) return 0;
		const int ret = m_event.front()(l_state);
		m_event.pop_front();
		return ret;
	}

public:
	SipManager& GetSip() { return m_sip; }
	RtpManager& GetRtp() { return m_rtp; }

private:
	SipManager m_sip;
	RtpManager m_rtp;

private:
	std::mutex m_mutex;
	std::list<std::function<int(lua_State*)>> m_event;
};

#endif
