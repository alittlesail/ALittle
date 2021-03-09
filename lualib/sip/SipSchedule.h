
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
#include "sip-transport.h"
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
			.addFunction("Register", &SipSchedule::RegisterForLua)
		    .addCFunction("PullEvent", &SipSchedule::PullEvent)
			.endClass()
            .addFunction("Setup", SipSchedule::Setup)
			.endNamespace();
	}

    static void Setup(const char* log_path, const char* log_name)
	{
        s_carp_log.Setup(log_path, log_name, false);
	}

	void RegisterForLua(const char* nickname ,const char* account, const char* password) { Execute(std::bind(&SipSchedule::Register, this, std::string(nickname), std::string(account), std::string(password))); }

public:
	SipSchedule();

public:
	// 启动SIP
    bool Start(const char* self_sip_ip, unsigned int self_sip_port, const char* self_sip_domain
		, const char* remote_sip_ip, unsigned int remote_sip_port, const char* remote_sip_domain);
	// 关闭
    void Close();
	// 发送数据包
    void Send(void* memory, size_t size);
	// 获取当前ip
	const std::string& GetSelfSipIp() const { return m_self_sip_ip; }
	// 获取当前ip的网关
	const std::string& GetSelfSipDomain() const { return m_self_sip_domain; }
	// 获取当前端口
	unsigned int GetSelfSipPort() const { return m_self_sip_port; }
	// 获取线路的域名
	const std::string& GetRemoteDomain() const { return m_remote_sip_domain; }

public:
	sip_agent_t* GetAgent() const { return m_agent; }
	sip_transport_t* GetTransport() { return &m_uac; }

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
	void Register(const std::string& nickname, const std::string& account, const std::string& password);

	// 获取注册号码
	struct RegisterInfo
	{
		std::string account;
		std::string password;
		std::string nickname;
	};
	const RegisterInfo* GetRegisterInfo(const std::string& account) const;

private:
	void HandleRemoteSip(CarpUdpServer::HandleInfo& info);

public:
    void PushEvent(std::function<int(lua_State*)> func);
    int PullEvent(lua_State* l_state);

private:
	CarpUdpServerPtr m_udp_self_sip;
	std::string m_self_sip_ip;
	std::string m_self_sip_domain;
	unsigned int m_self_sip_port = 0;

	std::string m_remote_sip_ip;
	unsigned int m_remote_sip_port = 0;
	std::string m_remote_sip_domain;
	asio::ip::udp::endpoint m_remote_sip_endpoint;

private:
	std::mutex m_mutex;
	std::list<std::function<int(lua_State*)>> m_event;

private:
	CarpTimer m_timer;
	std::unordered_map<int, TimerNode> m_timer_map;

private:
	std::unordered_map<std::string, RegisterInfo> m_register_map;

private:
	sip_agent_t* m_agent = nullptr;
	sip_transport_t m_uac;
};

#endif
