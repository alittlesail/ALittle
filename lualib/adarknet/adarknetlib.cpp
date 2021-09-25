
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "adarknetlib.h"
}
#include <LuaBridge/LuaBridge.h>

#include "carp_darknet_bind.hpp"

int luaopen_adarknet(lua_State* l_state)
{
    CarpDarknetBind::Bind(l_state);
    lua_getglobal(l_state, "carp");
    return 1;
}
