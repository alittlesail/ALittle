
#include "siplib.h"

#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>

#define SIP_MODNAME "sip"

/*
** Assumes the table is on top of the stack.
*/
static void set_info(lua_State* L) {
    lua_pushliteral(L, "_COPYRIGHT");
    lua_pushliteral(L, "Copyright (C) 2003-2019 ALittle");
    lua_settable(L, -3);
    lua_pushliteral(L, "_DESCRIPTION");
    lua_pushliteral(L, "sip for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "sip 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg siplib[] = {
    {NULL, NULL}
};

int luaopen_sip(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, siplib, 0);
    set_info(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, SIP_MODNAME);
    return 1;
}
