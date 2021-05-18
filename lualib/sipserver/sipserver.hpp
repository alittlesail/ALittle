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

#include "carp_string.hpp"
#include "carp_crypto.hpp"

class SipServer
{
public:
    SipServer()
    {
        osip_init(&m_osip);
        osip_set_application_context(m_osip, this);
        osip_set_cb_send_message(m_osip, cb_send_message);

        osip_set_kill_transaction_callback(m_osip, OSIP_ICT_KILL_TRANSACTION, cb_kill_transaction);
        osip_set_kill_transaction_callback(m_osip, OSIP_NIST_KILL_TRANSACTION, cb_kill_transaction);
        osip_set_kill_transaction_callback(m_osip, OSIP_NICT_KILL_TRANSACTION, cb_kill_transaction);
        osip_set_kill_transaction_callback(m_osip, OSIP_NIST_KILL_TRANSACTION, cb_kill_transaction);

        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_1XX_RECEIVED, cb_rcv1xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_2XX_RECEIVED, cb_rcv2xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_3XX_RECEIVED, cb_rcv3456xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_4XX_RECEIVED, cb_rcv3456xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_5XX_RECEIVED, cb_rcv3456xx);
        osip_set_message_callback(m_osip, OSIP_NICT_STATUS_6XX_RECEIVED, cb_rcv3456xx);
    }

    ~SipServer()
    {
        osip_release(m_osip);
    }

    void SetRemoteInfo(const char* remote_sip_domain, const char* remote_sip_ip, int remote_sip_port)
    {
        m_remote_sip_domain = remote_sip_domain;
        m_remote_sip_ip = remote_sip_ip;
        m_remote_sip_port = remote_sip_port;
    }

    void SetSelfInfo(const char* self_sip_ip, int self_sip_port)
    {
        m_self_sip_ip = self_sip_ip;
        m_self_sip_port = self_sip_port;
    }

    void SetRegisterInfo(int expires)
    {
        m_register_expires = expires;
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

    int PullResponseInfo(lua_State* l_state)
    {
        if (m_response_list.empty()) return 0;

        auto& info = m_response_list.front();
        lua_newtable(l_state);

        if (!info.register_account.empty())
        {
            lua_pushstring(l_state, info.register_account.c_str());
            lua_setfield(l_state, -2, "register_account");
        }

        lua_pushinteger(l_state, info.status);
        lua_setfield(l_state, -2, "status");

        m_response_list.pop_front();

        return 1;
    }

    void PushReceiveInfo(const char* message) const
    {
        auto* evt = osip_parse(message, strlen(message));
        if (evt == nullptr) return;

        if (osip_find_transaction_and_add_event(m_osip, evt) != OSIP_SUCCESS)
            osip_free(evt);
    }

    int GetTransactionCount() const { return m_transaction_count; }

public:
    class TransactionData
    {
    public:
        TransactionData(SipServer* s) : server(s) {}

        SipServer* server = nullptr;

        std::string register_account;
        std::string register_password;
    };

    void RegisterAccount(const char* account, const char* password)
    {
        auto* data = new TransactionData(this);
        data->register_account = account;
        data->register_password = password;

        const auto call_id = CarpCrypto::StringMd5(CarpString::GenerateID("call_id"));
        const auto from_tag = CarpCrypto::StringMd5(CarpString::GenerateID("from_tag"));
        const auto via_branch = CarpCrypto::StringMd5(CarpString::GenerateID("via_branch"));

        const auto sip = GenRegister(account, call_id, via_branch, from_tag, 1, "");
        NewTransaction(sip, false, data);
    }

    void AuthorizateAccount(osip_transaction_t* transaction, osip_message_t* message)
    {
        auto* data = static_cast<TransactionData*>(osip_transaction_get_your_instance(transaction));
        if (data == nullptr) return;

        std::string call_id;
        {
            char* dest = nullptr;
            osip_call_id_to_str(osip_message_get_call_id(message), &dest);
            if (dest != nullptr)
            {
                call_id = dest;
                osip_free(dest);
            }
        }

        std::string from_tag;
        {
            auto* from = osip_message_get_from(message);
            if (from != nullptr)
            {
                osip_uri_param_t* param = nullptr;
                osip_from_get_tag(from, &param);
                if (param != nullptr && param->gvalue)
                    from_tag = param->gvalue;
            }
        }

        int cseq = 0;
        char* c_cseq = osip_cseq_get_number(osip_message_get_cseq(message));
        if (c_cseq != nullptr) cseq = std::atoi(c_cseq);

        // 定义对端域名
        auto remote_sip_domain = m_remote_sip_domain;
        if (remote_sip_domain.empty()) remote_sip_domain = m_remote_sip_ip + ":" + std::to_string(m_remote_sip_port);

        osip_www_authenticate_t* authenticate = nullptr;
        osip_message_get_www_authenticate(message, 0, &authenticate);
        if (authenticate == nullptr) return;

        std::string nonce;
        const auto* c_nonce = osip_www_authenticate_get_nonce(authenticate);
        if (c_nonce != nullptr)
        {
            nonce = c_nonce;
            if (!nonce.empty() && nonce.back() == '"') nonce.pop_back();
            if (!nonce.empty() && nonce[0] == '"') nonce = nonce.substr(1);
        }

        std::string realm;
        const auto* c_realm = osip_www_authenticate_get_realm(authenticate);
        if (c_realm != nullptr)
        {
            realm = c_realm;
            if (!realm.empty() && realm.back() == '"') realm.pop_back();
            if (!realm.empty() && realm[0] == '"') realm = realm.substr(1);
        }

        const auto auth = GenAuth(nonce, realm, data->register_account, data->register_password, "REGISTER", remote_sip_domain);
        const auto via_branch = CarpCrypto::StringMd5(CarpString::GenerateID("via_branch"));

        const auto sip = GenRegister(data->register_account, call_id, via_branch, from_tag, cseq + 1, auth);

        auto* new_data = new TransactionData(this);
        new_data->register_account = data->register_account;
        new_data->register_password = data->register_password;
        NewTransaction(sip, false, new_data);
    }

    std::string GenRegister(const std::string& account, const std::string& call_id, const std::string& via_branch, const std::string& from_tag, int cseq, const std::string& auth)
    {
        // 计算域
        auto remote_sip_domain = m_remote_sip_domain;
        if (remote_sip_domain.empty()) remote_sip_domain = m_remote_sip_ip + ":" + std::to_string(m_remote_sip_port);
        auto self_sip_domain = m_self_sip_ip + ":" + std::to_string(m_self_sip_port);

        std::string sip = "REGISTER sip:" + remote_sip_domain + " SIP/2.0\r\n";
        sip += "Via: SIP/2.0/UDP " + self_sip_domain + ";rport;branch=z9hG4bK-" + via_branch + "\r\n";
        sip += "Max-Forwards: 70\r\n";
        sip += "Contact: <sip:" + account + "@" + self_sip_domain + ">\r\n";
        sip += "From: <sip:" + account + "@" + remote_sip_domain + ">;tag=" + from_tag + "\r\n";
        sip += "To: <sip:" + account + "@" + remote_sip_domain + ">\r\n";
        sip += "Call-ID: " + call_id + "\r\n";
        sip += "CSeq: " + std::to_string(cseq) + " REGISTER\r\n";
        sip += "Expires: " + std::to_string(m_register_expires) + "\r\n";
        if (!auth.empty()) sip += "Authorization: " + auth + "\r\n";
        sip += "Allow: INVITE,ACK,CANCEL,OPTIONS,BYE,REFER,NOTIFY,INFO,MESSAGE,SUBSCRIBE,INFO\r\n";
        sip += "User-Agent: ALittle\r\n";
        sip += "Content-Length: 0\r\n";
        sip += "\r\n";

        return sip;
    }

    std::string GenAuth(const std::string& nonce, const std::string& realm, const std::string& account, const std::string& password, const std::string& method, const std::string& uri)
    {
        const auto response_1 = CarpCrypto::StringMd5(account + ":" + realm + ":" + password);
        const auto response_2 = CarpCrypto::StringMd5(method + ":" + uri);
        const auto response = CarpCrypto::StringMd5(response_1 + ":" + nonce + ":" + response_2);

        return "Digest username=\"" + account + "\",realm=\"" + realm + "\",nonce=\"" + nonce + "\",uri=\"" + uri + "\",response=\"" + response + "\",algorithm=MD5";
    }

    void Run()
    {
        osip_timers_ict_execute(m_osip);
        osip_timers_nict_execute(m_osip);

        osip_timers_ist_execute(m_osip);
        osip_timers_nist_execute(m_osip);

        osip_ict_execute(m_osip);
        osip_nict_execute(m_osip);

        osip_ist_execute(m_osip);
        osip_nist_execute(m_osip);

        osip_retransmissions_execute(m_osip);
    }

private:
    int NewTransaction(const std::string& content, bool is_invite, TransactionData* data)
    {
        osip_message_t* message = nullptr;
        if (osip_message_init(&message) != OSIP_SUCCESS) return 0;
        if (osip_message_parse(message, content.c_str(), content.size()) != OSIP_SUCCESS)
        {
            osip_message_free(message);
            return 0;
        }

        osip_transaction_t* transaction = nullptr;
        if (osip_transaction_init(&transaction, is_invite ? ICT : NICT, m_osip, message) != OSIP_SUCCESS)
        {
            osip_message_free(message);
            return 0;
        }
        const int transaction_id = transaction->transactionid;
        osip_transaction_set_your_instance(transaction, data);

        // 构建发送消息
        auto* evt = osip_new_outgoing_sipmessage(message);
        if (evt == nullptr)
        {
            osip_message_free(message);
            osip_transaction_free(transaction);
            return 0;
        }
        //  添加事件
        osip_transaction_add_event(transaction, evt);

        ++m_transaction_count;
        return transaction_id;
    }

    bool UseTransaction(osip_transaction_t* transaction, const std::string& content)
    {
        osip_message_t* message = nullptr;
        if (osip_message_init(&message) != OSIP_SUCCESS) return false;
        if (osip_message_parse(message, content.c_str(), content.size()) != OSIP_SUCCESS)
        {
            osip_message_free(message);
            return false;
        }

        // 构建发送消息
        auto* evt = osip_new_outgoing_sipmessage(message);
        if (evt == nullptr)
        {
            osip_message_free(message);
            osip_transaction_free(transaction);
            return false;
        }
        //  添加事件
        osip_transaction_add_event(transaction, evt);

        return true;
    }

private:
    struct SendInfo
    {
        std::string message;
        std::string ip;
        int port = 0;
    };

    struct ResponseInfo
    {
        std::string register_account;   // 注册账号

        int status = 0;
    };

    static int cb_send_message(osip_transaction_t* transaction, osip_message_t* message, char* dest, int port, int sock)
    {
        auto* data = static_cast<TransactionData*>(osip_transaction_get_your_instance(transaction));
        if (data == nullptr) return OSIP_NO_NETWORK;

        char* str = nullptr;
        size_t len = 0;
        osip_message_to_str(message, &str, &len);

        SendInfo info;
        info.message.assign(str, len);
        info.ip = dest;
        info.port = port;

        osip_free(str);

        data->server->m_send_list.emplace_back(info);

        return OSIP_SUCCESS;
    }

    static void cb_rcv1xx(int type, osip_transaction_t* transaction, osip_message_t* message)
    {
        
    }

    static void cb_rcv2xx(int type, osip_transaction_t* transaction, osip_message_t* message)
    {
        auto* data = static_cast<TransactionData*>(osip_transaction_get_your_instance(transaction));
        if (data == nullptr) return;

        // 处理注册的200
        const auto status = osip_message_get_status_code(message);
        if (status == 200 && MSG_IS_RESPONSE_FOR(message, "REGISTER"))
        {
            ResponseInfo info;
            info.register_account = data->register_account;
            info.status = status;
            data->server->m_response_list.emplace_back(info);
        }
    }

    static void cb_rcv3456xx(int type, osip_transaction_t* transaction, osip_message_t* message)
    {
        auto* data = static_cast<TransactionData*>(osip_transaction_get_your_instance(transaction));
        if (data == nullptr) return;

        // 处理注册的401
        const auto status = osip_message_get_status_code(message);
        if (status == 401 && MSG_IS_RESPONSE_FOR(message, "REGISTER"))
        {
            data->server->AuthorizateAccount(transaction, message);
        }
    }

    static void cb_kill_transaction(int type, osip_transaction_t* transaction)
    {
        auto* data = static_cast<TransactionData*>(osip_transaction_get_your_instance(transaction));
        if (data != nullptr)
        {
            osip_transaction_set_reserved2(transaction, nullptr);
            --data->server->m_transaction_count;
            delete data;
        }

        osip_remove_transaction(static_cast<osip_t*>(transaction->config), transaction);
    }

private:
    osip_t* m_osip = nullptr;
    int m_transaction_count = 0;

private:
    std::list<SendInfo> m_send_list;
    std::list<ResponseInfo> m_response_list;

private:
    std::string m_remote_sip_domain;
    std::string m_remote_sip_ip;
    int m_remote_sip_port = 0;

    std::string m_self_sip_ip;
    int m_self_sip_port = 0;

private:
    int m_register_expires = 3600;
};

#endif
