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

private:
    osip_t* m_osip = nullptr;

private:
    std::list<SendInfo> m_send_list;
};

#endif
