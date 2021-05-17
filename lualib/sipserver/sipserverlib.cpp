
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "sipserverlib.h"
}
#include <LuaBridge/LuaBridge.h>

int luaopen_deeplearning(lua_State* l_state) {
	luabridge::getGlobalNamespace(l_state)
		.beginNamespace("sipserver")
		.endNamespace();
	lua_getglobal(l_state, "sipserver");
	return 1;
}
