#ifndef SIPSERVER_INCLUDED
#define SIPSERVER_INCLUDED

#include <list>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "sipserverlib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "osip2/osip.h"

class SipServer
{
public:
    SipServer()
    {
        osip_init(&m_osip);
        osip_set_application_context(m_osip, this);
        osip_set_cb_send_message(m_osip, cb_send_message);

        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_1XX_RECEIVED, &cb_rcv1xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_2XX_RECEIVED, &cb_rcv2xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_3XX_RECEIVED, &cb_rcv3456xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_4XX_RECEIVED, &cb_rcv3456xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_5XX_RECEIVED, &cb_rcv3456xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_6XX_RECEIVED, &cb_rcv3456xx);
    }

    ~SipServer()
    {
        osip_release(m_osip);
    }

    int PullSendInfo(lua_State* l_state)
    {
        if (m_send_list.empty()) return 0;

        auto& info = m_send_list.front();
        lua_newtable(l_state);

        lua_pushlstring(l_state, info.message.c_str(), info.message.size());
        lua_setfield(l_state, -2, "message");

        lua_pushlstring(l_state, info.ip.c_str(), info.ip.size());
        lua_setfield(l_state, -2, "ip");

        lua_pushinteger(l_state, info.port);
        lua_setfield(l_state, -2, "port");

        m_send_list.pop_front();

        return 1;
    }

    void PushReceiveInfo(const char* message) const
    {
        auto* evt = osip_parse(message, strlen(message));
        if (evt == nullptr) return;

        if (osip_find_transaction_and_add_event(m_osip, evt) != OSIP_SUCCESS)
            osip_free(evt);
    }

    int NewTransaction(const char* content, bool is_invite)
    {
        osip_message_t* message = nullptr;
        if (osip_message_init(&message) != OSIP_SUCCESS) return 0;
        if (osip_message_parse(message, content, strlen(content)) != OSIP_SUCCESS)
        {
            osip_message_free(message);
            return 0;
        }

        osip_transaction_t* transaction = nullptr;
        if (osip_transaction_init(&transaction, is_invite ? ICT : NICT, m_osip, message) != OSIP_SUCCESS)
        {
            osip_message_free(message);
            return false;
        }
        const int transaction_id = transaction->transactionid;
        osip_transaction_set_your_instance(transaction, this);

        // 构建发送消息
        auto* evt = osip_new_outgoing_sipmessage(message);
        if (evt == nullptr)
        {
            osip_message_free(message);
            osip_transaction_free(transaction);
            return false;
        }

        // 关联所在的会话
        evt->transactionid = transaction->transactionid;
        //  添加事件
        osip_transaction_add_event(transaction, evt);

        return transaction_id;
    }

private:
    struct SendInfo
    {
        std::string message;
        std::string ip;
        int port = 0;
    };

    static int cb_send_message(osip_transaction_t* transaction, osip_message_t* message, char* dest, int port, int sock)
    {
        auto* self = static_cast<SipServer*>(osip_transaction_get_your_instance(transaction));
        if (self == nullptr) return OSIP_NO_NETWORK;

        char* str = nullptr;
        size_t len = 0;
        osip_message_to_str(message, &str, &len);

        SendInfo info;
        info.message.assign(str, len);
        info.ip = dest;
        info.port = port;

        osip_free(str);

        self->m_send_list.emplace_back(info);

        return OSIP_SUCCESS;
    }

    static void cb_rcv1xx(int type, osip_transaction_t* transaction, osip_message_t* message)
    {
        
    }

    static void cb_rcv2xx(int type, osip_transaction_t* transaction, osip_message_t* message)
    {

    }

    static void cb_rcv3456xx(int type, osip_transaction_t* transaction, osip_message_t* message)
    {

    }

private:
    osip_t* m_osip = nullptr;

private:
    std::list<SendInfo> m_send_list;
};

#endif
