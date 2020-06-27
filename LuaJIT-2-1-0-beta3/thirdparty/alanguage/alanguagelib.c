
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"
#include "lauxlib.h"

#include "alanguage.h"
#include "alanguagelib.h"

#define ALANGUAGE_MODNAME "alanguage"

static int alanguagelib_destroy_abnf(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    if (c) delete_abnf(*c);
    return 0;
}

static int alanguagelib_create_abnf(lua_State* L)
{
    void** c = (void*)lua_newuserdata(L, sizeof(void**));
    lua_newtable(L);
    lua_pushcfunction(L, alanguagelib_destroy_abnf);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
	*c = create_abnf();
    return 1;
}

static int alanguagelib_abnf_load(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf object is null");
    const char* buffer = luaL_checkstring(L, 2);
    void* factory = lua_touserdata(L, 3);
    luaL_argcheck(L, factory != 0, 3, "factory object is null");
    const char* r = abnf_load(*c, buffer, factory);
    if (r) lua_pushstring(L, r);
    else lua_pushnil(L);
    return 1;
}

/*
** Assumes the table is on top of the stack.
*/
static void set_info (lua_State *L) {
	lua_pushliteral (L, "_COPYRIGHT");
	lua_pushliteral (L, "Copyright (C) 2003-2019 PUC-Rio");
	lua_settable (L, -3);
	lua_pushliteral (L, "_DESCRIPTION");
	lua_pushliteral (L, "ALanguage for Lua");
	lua_settable (L, -3);
	lua_pushliteral (L, "_VERSION");
	lua_pushliteral (L, "ALanguage 1.3");
	lua_settable (L, -3);
}

static struct luaL_Reg alanguagelib[] = {
  {"create_abnf", alanguagelib_create_abnf},
  {"abnf_load", alanguagelib_abnf_load},
  {NULL, NULL}
};

int luaopen_alanguage(lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, alanguagelib, 0);
  set_info (L);
  lua_pushvalue(L, -1);
  lua_setglobal(L, ALANGUAGE_MODNAME);
  return 1;
}
