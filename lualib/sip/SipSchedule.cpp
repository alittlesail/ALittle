
#include "SipSchedule.h"
#include "carp_string.hpp"

extern "C" {
#include "sip-uas.h"
#include "sip-message.h"
#include "sip-uac.h"
#include "http-parser.h"
#include "http-header-auth.h"
}

#ifndef strncasecmp
#define strncasecmp  _strnicmp   
#endif

static SipSchedule* s_sip_schedule = nullptr;

sip_timer_t sip_timer_start(int timeout, sip_timer_handle handler, void* usrptr)
{
    const auto id = s_sip_schedule->AddTimer(timeout, handler, usrptr);
    sip_timer_t timer = nullptr;
    memcpy(&timer, &id, sizeof(id));
    return timer;
}

int sip_timer_stop(sip_timer_t* timer_ptr)
{
    if (nullptr == timer_ptr || nullptr == *timer_ptr) return -1;

    // 取出数据，并设置为nullptr
    const auto* timer = *timer_ptr;
    *timer_ptr = nullptr;

    int id = 0;
    memcpy(&id, &timer, sizeof(id));
    s_sip_schedule->RemoveTimer(id);

    return 0;
}

int sip_uas_onprack(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session, struct sip_dialog_t* dialog, const void* data, int bytes)
{
    return 0;
}

int sip_uas_onupdate(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session, struct sip_dialog_t* dialog, const void* data, int bytes)
{
    return 0;    
}

void* sip_uas_onsubscribe(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, struct sip_subscribe_t* subscribe)
{
    return nullptr;    
}
int sip_uas_onnotify(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session, const struct cstring_t* event)
{
    return 0;
}

int sip_uas_onpublish(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, const struct cstring_t* event)
{
    return 0;
}

int sip_uas_oninfo(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session)
{
    return 0;
}

int sip_uas_onrefer(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session)
{
    return 0;
}

int sip_uas_onregister(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, const char* user, const char* location, int expires)
{
    auto* schedule = static_cast<SipSchedule*>(param);
    return sip_uas_reply(t, 200, NULL, 0);
}

void* sip_uas_oninvite(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, struct sip_dialog_t* dialog, const void* data, int bytes)
{
    auto* schedule = static_cast<SipSchedule*>(param);

    return nullptr;
}

int sip_uas_onack(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session, struct sip_dialog_t* dialog, int code, const void* data, int bytes)
{
    auto* schedule = static_cast<SipSchedule*>(param);

    return 0;
}

int sip_uas_onbye(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session)
{
    auto* schedule = static_cast<SipSchedule*>(param);

    return 0;
}

int sip_uas_oncancel(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session)
{
    auto* schedule = static_cast<SipSchedule*>(param);

    return 0;
}

int sip_uas_onmessage(void* param, const struct sip_message_t* req, struct sip_uas_transaction_t* t, void* session, const void* data, int bytes)
{
    auto* schedule = static_cast<SipSchedule*>(param);

    return 0;
}

int sip_uas_transport_send(void* param, const struct cstring_t* protocol, const struct cstring_t* url, const struct cstring_t* received, int rport, const void* data, int bytes)
{
    auto* schedule = static_cast<SipSchedule*>(param);

    void* new_memory = malloc(bytes);
    memcpy(new_memory, data, bytes);
    schedule->Send(new_memory, bytes);

    return 0;    
}

int sip_uac_transport_send(void* transport, const void* data, size_t bytes)
{
    auto* schedule = static_cast<SipSchedule*>(transport);

    void* new_memory = malloc(bytes);
    memcpy(new_memory, data, bytes);
    schedule->Send(new_memory, bytes);

    return 0;
}

int sip_uac_transport_via(void* transport, const char* destination, char protocol[16], char local[128], char dns[128])
{
    auto* schedule = static_cast<SipSchedule*>(transport);
    const std::string ip_and_port = schedule->GetSelfSipIp() + ":" + std::to_string(schedule->GetSelfSipPort());

#ifdef _WIN32
    strcpy_s(protocol, 16, "UDP");
    strcpy_s(local, 128, ip_and_port.c_str());
    strcpy_s(dns, 128, schedule->GetSelfSipDomain().c_str());
#else
    strcpy(protocol, "UDP");
    strcpy(local, ip_and_port.c_str());
    strcpy(dns, schedule->GetSelfSipDomain().c_str());
#endif

    return 0;
}

int sip_uac_onregister(void* param, const struct sip_message_t* reply, struct sip_uac_transaction_t* t, int code)
{
    auto* schedule = static_cast<SipSchedule*>(param);

    if (200 <= code && code < 300) return 0;
    
    if (401 == code)
    {
        std::vector<std::string> host_split;
        const std::string host(reply->from.uri.host.p, reply->from.uri.host.n);
        CarpString::Split(host, "@", host_split);
        if (host_split.empty())
        {
            CARP_ERROR("can't find register info, host:" << host);
            return 0;
        }
        const auto* info = schedule->GetRegisterInfo(host_split[0]);
        if (info == nullptr)
        {
            CARP_ERROR("can't find register info, nickname:" << host_split[0]);
            return 0;
        }

        // Unauthorized
        http_header_www_authenticate_t auth = {0};
        const std::string www_auth = "WWW-Authenticate";
        const auto* param_string = sip_params_find_string(&reply->headers, www_auth.c_str(), static_cast<int>(www_auth.size()));
        if (param == nullptr)
        {
            CARP_ERROR("can't find " << www_auth << " in sip");
            return 0;
        }

        const std::string sip_account = "sip:" + info->nickname + "@" + schedule->GetRemoteDomain();
        const std::string registerar = "sip:" + schedule->GetRemoteDomain();
        auto* new_t = sip_uac_register(schedule->GetAgent(), sip_account.c_str(), registerar.c_str(), 3600, sip_uac_onregister, param);
        sip_uac_add_header(new_t, "Call-ID", reply->callid.p); // All registrations from a UAC SHOULD use the same Call-ID
        const std::string cseq = std::to_string(reply->cseq.id + 1) + " REGISTER";
        sip_uac_add_header(new_t, "CSeq", cseq.c_str()); // A UA MUST increment the CSeq value by one for each REGISTER request with the same Call-ID

        std::string www_auth_value(param_string->p, param_string->n);
        http_header_www_authenticate(www_auth_value.c_str(), &auth);

        ++auth.nc;
        if (!auth.algorithm[0]) snprintf(auth.algorithm, sizeof(auth.algorithm), "MD5");
        if (!auth.qop[0]) snprintf(auth.qop, sizeof(auth.qop), "auth");
        else if (strchr(auth.qop, ',')) *strchr(auth.qop, ',') = '\0'; // replace auth,auth-int -> auth
        snprintf(auth.uri, sizeof(auth.uri), "%s", registerar.c_str());
        snprintf(auth.username, sizeof(auth.username), "%s", info->account.c_str());
        char buffer[256] = { 0 };
        http_header_auth(&auth, info->password.c_str(), "REGISTER", NULL, 0, buffer, sizeof(buffer));
        sip_uac_add_header(new_t, "Authorization", buffer);
        sip_uac_send(new_t, NULL, 0, schedule->GetTransport(), param);

        sip_uac_transaction_release(new_t);

    }
    return 0;
}

SipSchedule::SipSchedule()
{
    s_sip_schedule = this;
}

bool SipSchedule::Start(const char* self_sip_ip, unsigned int self_sip_port, const char* self_sip_domain
    , const char* remote_sip_ip, unsigned int remote_sip_port, const char* remote_sip_domain)
{
    Close();

    m_self_sip_ip = self_sip_ip;
    m_self_sip_domain = self_sip_domain;
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
    m_remote_sip_domain = remote_sip_domain;
    m_remote_sip_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(remote_sip_ip), remote_sip_port);

    sip_uas_handler_t handler = {0};
    handler.onregister = sip_uas_onregister;
    handler.oninvite = sip_uas_oninvite;
    handler.onack = sip_uas_onack;
    handler.onbye = sip_uas_onbye;
    handler.oncancel = sip_uas_oncancel;
    handler.onmessage = sip_uas_onmessage;
    handler.send = sip_uas_transport_send;
    handler.onprack = sip_uas_onprack;
    handler.onpublish = sip_uas_onpublish;
    handler.onupdate = sip_uas_onupdate;
    handler.oninfo = sip_uas_oninfo;
    handler.onrefer = sip_uas_onrefer;
    handler.onsubscribe = sip_uas_onsubscribe;
    handler.onnotify = sip_uas_onnotify;
    m_agent = sip_agent_create(&handler, this);
    if (m_agent == nullptr)
    {
        Close();
        return false;
    }
    m_uac.send = sip_uac_transport_send;
    m_uac.via = sip_uac_transport_via;

    Run(true);

    // 更新时间
    m_timer.UpdateCurTime();
    // 启动定时器
    TimerLoop(5, [this](time_t cur_time)
        {
            m_timer.UpdateCurTime();

            while (true)
            {
                const auto id = m_timer.Poll();
                if (id == 0) break;

                auto it = m_timer_map.find(std::abs(id));
                if (it != m_timer_map.end())
                {
                    const auto node = it->second;
                    node.handle(node.usrptr);
                    if (id > 0) m_timer_map.erase(it);
                }
            }
        });
    return true;
}

void SipSchedule::Close()
{
    if (m_udp_self_sip) m_udp_self_sip->Close();
    m_udp_self_sip = CarpUdpServerPtr();

    if (m_agent) sip_agent_destroy(m_agent);
    m_agent = nullptr;

    m_timer_map.clear();
    m_timer.Clear();
}

void SipSchedule::Send(void* memory, size_t size)
{
    CARP_INFO("SEND ---->\n" << std::string(static_cast<char*>(memory), size));
    m_udp_self_sip->Send(memory, size, m_remote_sip_endpoint);
}

int SipSchedule::AddTimer(int time_out, sip_timer_handle handle, void* usrptr)
{
    const auto id = m_timer.Add(time_out, 1, 0);
    if (id == 0) return 0;

    auto& node = m_timer_map[id];
    node.timer_id = id;
    node.handle = handle;
    node.usrptr = usrptr;

    return id;
}

void SipSchedule::RemoveTimer(int id)
{
    const auto it = m_timer_map.find(id);
    if (it == m_timer_map.end()) return;

    m_timer.Remove(id);
    m_timer_map.erase(it);
}

void SipSchedule::Register(const std::string& nickname, const std::string& account, const std::string& password)
{
    auto& info = m_register_map[nickname];
    info.account = account;
    info.password = password;
    info.nickname = nickname;

    const std::string sip_account = "sip:" + nickname + "@" + m_remote_sip_domain;
    const std::string registerar = "sip:" + m_remote_sip_domain;
    sip_uac_transaction_t* t = sip_uac_register(m_agent, sip_account.c_str(), registerar.c_str(), 3600, sip_uac_onregister, this);
    sip_uac_send(t, NULL, 0, &m_uac, this);
    sip_uac_transaction_release(t);
}

const SipSchedule::RegisterInfo* SipSchedule::GetRegisterInfo(const std::string& account) const
{
    auto it = m_register_map.find(account);
    if (it == m_register_map.end()) return nullptr;
    return &it->second;
}

void SipSchedule::HandleRemoteSip(CarpUdpServer::HandleInfo& info)
{
    CARP_INFO("RECEIVE ---->\n" << info.memory);

    const int response = 0 == strncasecmp("SIP", info.memory, 3) ? 1 : 0;

    http_parser_t* parser = http_parser_create(response ? HTTP_PARSER_RESPONSE : HTTP_PARSER_REQUEST, NULL, NULL);
    do
    {
        size_t n = info.memory_size;
        if (0 != http_parser_input(parser, info.memory, &n))
        {
            CARP_ERROR("http_parser_input failed! message:" << info.memory);
            break;
        }

        struct sip_message_t* msg = sip_message_create(response ? SIP_MESSAGE_REPLY : SIP_MESSAGE_REQUEST);
        do
        {
            if (0 != sip_message_load(msg, parser))
            {
                CARP_ERROR("sip_message_load failed! message:" << info.memory);
                break;
            }

            if (0 != sip_agent_input(m_agent, msg))
            {
                CARP_ERROR("sip_agent_input failed! message:" << info.memory);
                break;
            }
        } while (false);
        sip_message_destroy(msg);

    } while (false);

    http_parser_destroy(parser);
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
