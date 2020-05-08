
#include "memorylib.h"

#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>

#define MEMORY_MODNAME "memory"

static int memorylib_create(lua_State* L)
{
    lua_Integer size = luaL_checkinteger(L, 1);
    lua_pushlightuserdata(L, malloc(size));
    return 1;
}

static int memorylib_free(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    if (m) free(m);
    return 0;
}

/*
** Assumes the table is on top of the stack.
*/
static void set_info(lua_State* L) {
    lua_pushliteral(L, "_COPYRIGHT");
    lua_pushliteral(L, "Copyright (C) 2003-2019 ALittle");
    lua_settable(L, -3);
    lua_pushliteral(L, "_DESCRIPTION");
    lua_pushliteral(L, "memory for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "memory 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg memorylib[] = {
    {"create", memorylib_create},
    {"free", memorylib_free},

    {NULL, NULL}
};

int luaopen_memory(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, memorylib, 0);
    set_info(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, MEMORY_MODNAME);
    return 1;
}
