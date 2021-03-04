
#ifndef _ALITTLE_RTPSCHEDULE_H_
#define _ALITTLE_RTPSCHEDULE_H_

#include "carp_schedule.hpp"
#include "carp_lua.hpp"
#include "carp_string.hpp"
#include "RtpTransfer.h"

class RtpSchedule : public CarpSchedule
{
public:
    ~RtpSchedule();

	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginNamespace("rtp")
			.beginClass<RtpSchedule>("RtpSchedule")
			.addConstructor<void(*)()>()
			.addFunction("ReleaseRtp", &RtpSchedule::ReleaseRtpForLua)
            .addFunction("SetRemoteRtp", &RtpSchedule::SetRemoteRtpForLua)
            .addFunction("SetInnerRtp", &RtpSchedule::SetInnerRtpForLua)
            .addFunction("TransClient", &RtpSchedule::TransClientForLua)
            .addFunction("ClearIdleRtp", &RtpSchedule::ClearIdleRtpForLua)
            .addCFunction("UseRtp", &RtpSchedule::UseRtpForLua)
			.endClass()
            .addFunction("Setup", RtpSchedule::Setup)
			.endNamespace();
	}

    static void Setup(const char* log_path, const char* log_name)
	{
        s_carp_log.Setup(log_path, log_name, false);
	}

    void ReleaseRtpForLua(int first_port) { Execute(std::bind(&RtpSchedule::ReleaseRtp, this, first_port)); }
    void ReleaseAllRtpForLua() { Execute(std::bind(&RtpSchedule::ReleaseAllRtp, this)); }
    void SetRemoteRtpForLua(int first_port, const char* target_remote_rtp_ip, int target_remote_rtp_port) { Execute(std::bind(&RtpSchedule::SetRemoteRtp, this, first_port, std::string(target_remote_rtp_ip), target_remote_rtp_port)); }
    void SetInnerRtpForLua(int first_port, const char* inner_rtp_ip, int inner_rtp_port) { Execute(std::bind(&RtpSchedule::SetInnerRtp, this, first_port, std::string(inner_rtp_ip), inner_rtp_port)); }
    void TransClientForLua(int first_port, int client_id) { Execute(std::bind(&RtpSchedule::TransClient, this, first_port, client_id)); }
    void ClearIdleRtpForLua() { Execute(std::bind(&RtpSchedule::ClearIdleRtp, this)); }

    int UseRtpForLua(lua_State* L)
	{
        // 读取参数
        int index = 2;
        int first_port = static_cast<int>(luaL_checkinteger(L, index++));
        const char* client_rtp_ip_string = luaL_checkstring(L, index++);
        std::vector<std::string> client_rtp_ip_list;
        CarpString::Split(client_rtp_ip_string, ";", client_rtp_ip_list);
        int client_rtp_port = static_cast<int>(luaL_checkinteger(L, index++));
        const char* remote_rtp_ip = luaL_checkstring(L, index++);
        int remote_rtp_port = static_cast<int>(luaL_checkinteger(L, index++));
        const char* inner_rtp_ip = luaL_checkstring(L, index++);
        int inner_rtp_port = static_cast<int>(luaL_checkinteger(L, index++));
        const char* target_remote_rtp_ip = luaL_checkstring(L, index++);
        int target_remote_rtp_port = static_cast<int>(luaL_checkinteger(L, index++));
        const char* call_id = luaL_checkstring(L, index++);
        int client_id = static_cast<int>(luaL_checkinteger(L, index++));
        unsigned int ssrc = static_cast<int>(luaL_checkinteger(L, index++));

        // 执行
        Execute(std::bind(&RtpSchedule::UseRtp, this, first_port
            , client_rtp_ip_list, client_rtp_port
            , remote_rtp_ip, remote_rtp_port
            , inner_rtp_ip, inner_rtp_port
            , target_remote_rtp_ip, target_remote_rtp_port
            , call_id, client_id, ssrc));

        return 0;
	}

public:
    // 释放rtp
    void ReleaseRtp(int first_port);
    void ReleaseAllRtp();

    // 开始使用rtp
    void UseRtp(int first_port
        , const std::vector<std::string>& client_rtp_ip_list, int client_rtp_port
        , const std::string& remote_rtp_ip, int remote_rtp_port
        , const std::string& inner_rtp_ip, int inner_rtp_port
        , const std::string& target_remote_rtp_ip, int target_remote_rtp_port
        , const std::string& call_id, int client_id, unsigned int ssrc);

    // 设置线路的rtp
    void SetRemoteRtp(int first_port, const std::string& target_remote_rtp_ip, int target_remote_rtp_port);

    // 设置内部转接rtp
    void SetInnerRtp(int first_port, const std::string& inner_rtp_ip, int inner_rtp_port);

    // 转接到客户端
    void TransClient(int first_port, int client_id);

    // 清理空闲的rtp
    void ClearIdleRtp();

private:
    // 所有的rtp
    std::map<int, RtpTransferPtr> m_use_map_rtp;

    // 等待释放的rtp
    std::map<int, RtpTransferPtr> m_release_map_rtp;
};

#endif
