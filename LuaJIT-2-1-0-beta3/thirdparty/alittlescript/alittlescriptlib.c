
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"
#include "lauxlib.h"

#include "alittlescriptlib.h"
#include "alittlescript.h"

#define ALITTLESCRIPT_MODNAME "alittlescript"

static int alittlescriptlib_destroy_alittlescript_project(lua_State* L)
{
	void** c = (void**)lua_touserdata(L, 1);
	if (c) delete_alittlescript_project(*c);
	return 0;
}

static int alittlescriptlib_create_alittlescript_project(lua_State* L)
{
	const char* abnf_buffer = luaL_checkstring(L, 1);
	luaL_argcheck(L, abnf_buffer != 0, 1, "abnf buffer is null");

	void** c = (void**)lua_newuserdata(L, sizeof(void**));
	lua_newtable(L);
	lua_pushcfunction(L, alittlescriptlib_destroy_alittlescript_project);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	*c = create_alittlescript_project(abnf_buffer);
	return 1;
}

static int alittlescriptlib_alittlescriptproject_settargetlanguage(lua_State* L)
{
	void** c = (void**)lua_touserdata(L, 1);
	luaL_argcheck(L, c != 0, 1, "alittlescript project object is null");
	const char* target_language = luaL_checkstring(L, 2);
	luaL_argcheck(L, target_language != 0, 2, "target_language is null");

	alittlescriptproject_settargetlanguage(*c, target_language);
	return 0;
}

static int alittlescriptlib_alittlescriptproject_gettargetlanguage(lua_State* L)
{
	void** c = (void**)lua_touserdata(L, 1);
	luaL_argcheck(L, c != 0, 1, "alittlescript project object is null");

	const char* target_language = alittlescriptproject_gettargetlanguage(*c);
	if (target_language == 0) lua_pushnil(L);
	else lua_pushstring(L, target_language);
	return 1;
}

static int alittlescriptlib_alittlescriptproject_generate(lua_State* L)
{
	void** c = (void**)lua_touserdata(L, 1);
	luaL_argcheck(L, c != 0, 1, "alittlescript project object is null");
	int query_id = (int)luaL_checkinteger(L, 2);
	const char* full_path = luaL_checkstring(L, 3);
	luaL_argcheck(L, full_path != 0, 2, "full_path is null");

	alittlescriptproject_generate(*c, query_id, full_path);
	return 0;
}

static int alittlescriptlib_destroy_alittlescript_file(lua_State* L)
{
	void** c = (void**)lua_touserdata(L, 1);
	if (c) delete_alittlescript_file(*c);
	return 0;
}

static int alittlescriptlib_create_alittlescript_file(lua_State* L)
{
	void** project = (void**)lua_touserdata(L, 1);
	luaL_argcheck(L, project != 0, 1, "alittlescript project is null");
	const char* module_path = luaL_checkstring(L, 2);
	luaL_argcheck(L, module_path != 0, 2, "module_path is null");
	const char* full_path = luaL_checkstring(L, 3);
	luaL_argcheck(L, full_path != 0, 3, "full_path is null");

	size_t len;
	const char* text = luaL_checklstring(L, 4, &len);
	luaL_argcheck(L, text != 0, 4, "text is null");

	void** c = (void**)lua_newuserdata(L, sizeof(void**));
	lua_newtable(L);
	lua_pushcfunction(L, alittlescriptlib_destroy_alittlescript_file);
	lua_setfield(L, -2, "__gc");
	lua_setmetatable(L, -2);
	*c = create_alittlescript_file(*project, module_path, full_path, text, len);
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
	lua_pushliteral (L, "alittlescript for Lua");
	lua_settable (L, -3);
	lua_pushliteral (L, "_VERSION");
	lua_pushliteral (L, "alittlescript 1.3");
	lua_settable (L, -3);
}

static struct luaL_Reg alittlescriptlib[] = {
  {"create_alittlescript_project", alittlescriptlib_create_alittlescript_project},
  {"create_alittlescript_file", alittlescriptlib_create_alittlescript_file},
  {"alittlescriptproject_settargetlanguage", alittlescriptlib_alittlescriptproject_settargetlanguage},
  {"alittlescriptproject_gettargetlanguage", alittlescriptlib_alittlescriptproject_gettargetlanguage},
  {"alittlescriptproject_generate", alittlescriptlib_alittlescriptproject_generate},
  {NULL, NULL}
};

int luaopen_alittlescript(lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, alittlescriptlib, 0);
  set_info (L);
  lua_pushvalue(L, -1);
  lua_setglobal(L, ALITTLESCRIPT_MODNAME);
  return 1;
}
