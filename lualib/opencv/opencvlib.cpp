
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include "opencvlib.h"
}
#include <LuaBridge/LuaBridge.h>
#include "Carp/carp_opencv_bind.hpp"

int luaopen_opencv(lua_State* l_state)
{
    CarpOpenCVBind::Bind(l_state);
    lua_getglobal(l_state, "carp");
    return 1;
}
