
#include "SipSchedule.h"

bool SipSchedule::Start(const char* self_sip_ip, unsigned int self_sip_port, const char* remote_sip_ip, unsigned int remote_sip_port)
{
    Close();

    m_self_sip_ip = self_sip_ip;
    m_self_sip_port = self_sip_port;

    m_udp_self_sip = std::make_shared<CarpUdpServer>(GetIOService());
    m_udp_self_sip->RegisterUdpHandle(std::bind(&SipSchedule::HandleRemoteSip, this, std::placeholders::_1));
    if (!m_udp_self_sip->Start(m_self_sip_ip, m_self_sip_port))
    {
        Close();
        return false;
    }

    m_remote_sip_ip = remote_sip_ip;
    m_remote_sip_port = remote_sip_port;
    m_remote_sip_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(remote_sip_ip), remote_sip_port);
    return true;
}

void SipSchedule::Close()
{
    if (m_udp_self_sip) m_udp_self_sip->Close();
    m_udp_self_sip = CarpUdpServerPtr();
}

void SipSchedule::Register(const char* account, const char* password, const char* show_account)
{
}

void SipSchedule::HandleRemoteSip(CarpUdpServer::HandleInfo& info)
{
}

void SipSchedule::PushEvent(std::function<int(lua_State*)> func)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_event.push_back(func);
}

int SipSchedule::PullEvent(lua_State* l_state)
{
    std::function<int(lua_State*)> func;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_event.empty()) return 0;
        func = std::move(m_event.front());
        m_event.pop_front();
    }
    return func(l_state);
}
