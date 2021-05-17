
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "sipserverlib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "sipserver.hpp"

int luaopen_sipserver(lua_State* l_state) {
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("sipserver")
		.beginClass<SipServer>("SipServer")
		.addConstructor<void(*)()>()
		.addFunction("Run", &SipServer::Run)
	    .addFunction("SetRemoteInfo", &SipServer::SetRemoteInfo)
		.addFunction("SetSelfInfo", &SipServer::SetSelfInfo)
		.addFunction("SetRegisterInfo", &SipServer::SetRegisterInfo)
		.addFunction("RegisterAccount", &SipServer::RegisterAccount)
	    .addCFunction("PullSendInfo", &SipServer::PullSendInfo)
		.addFunction("PushReceiveInfo", &SipServer::PushReceiveInfo)
	    .endClass()
		.endNamespace();
	lua_getglobal(l_state, "sipserver");
	return 1;
}
