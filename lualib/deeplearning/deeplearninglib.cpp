
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "deeplearninglib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "Carp/carp_robot_bind.hpp"

int luaopen_deeplearning(lua_State* l_state)
{
	CarpRobotBind::Bind(l_state);
    lua_getglobal(l_state, "carp");
    return 1;
}
