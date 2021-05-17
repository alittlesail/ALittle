
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "sipserverlib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "sipserver.hpp"

int luaopen_deeplearning(lua_State* l_state) {
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("sipserver")
		.beginClass<SipServer>("SipServer")
		.addConstructor<void(*)()>()
	    .endClass()
		.endNamespace();
	lua_getglobal(l_state, "sipserver");
	return 1;
}
