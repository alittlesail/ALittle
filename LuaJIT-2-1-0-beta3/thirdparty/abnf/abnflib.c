
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"
#include "lauxlib.h"

#include "abnflib.h"
#include "abnf_c.h"

#define ABNF_MODNAME "abnf"

static int abnflib_destroy_abnf_factory(lua_State* L)
{
	void** c = (void**)lua_touserdata(L, 1);
	if (c) delete_abnf_factory(*c);
	return 0;
}

static int abnflib_create_abnf_factory(lua_State* L)
{
	void** c = (void**)lua_newuserdata(L, sizeof(void**));
	lua_newtable(L);
	lua_pushcfunction(L, abnflib_destroy_abnf_factory);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	*c = create_abnf_factory();
	return 1;
}

static int abnflib_destroy_abnf_file(lua_State* L)
{
	void** c = (void**)lua_touserdata(L, 1);
	if (c) delete_abnf_file(*c);
	return 0;
}

static int abnflib_create_abnf_file(lua_State* L)
{
	const char* full_path = luaL_checkstring(L, 1);
	luaL_argcheck(L, full_path != 0, 1, "full_path is null");
	void** abnf = (void**)lua_touserdata(L, 2);
	luaL_argcheck(L, abnf != 0, 2, "abnf is null");

	size_t len;
	const char* text = luaL_checklstring(L, 3, &len);
	luaL_argcheck(L, text != 0, 3, "text is null");

	void** c = (void**)lua_newuserdata(L, sizeof(void**));
	lua_newtable(L);
	lua_pushcfunction(L, abnflib_destroy_abnf_file);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	*c = create_abnf_file(full_path, *abnf, text, len);
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
	lua_pushliteral (L, "ABnf for Lua");
	lua_settable (L, -3);
	lua_pushliteral (L, "_VERSION");
	lua_pushliteral (L, "ABnf 1.3");
	lua_settable (L, -3);
}

static struct luaL_Reg abnflib[] = {
  {"create_abnf_factory", abnflib_create_abnf_factory},
  {"create_abnf_file", abnflib_create_abnf_file},
  {NULL, NULL}
};

int luaopen_abnf(lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, abnflib, 0);
  set_info (L);
  lua_pushvalue(L, -1);
  lua_setglobal(L, ABNF_MODNAME);
  return 1;
}
