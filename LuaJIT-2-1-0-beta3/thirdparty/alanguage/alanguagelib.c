
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"
#include "lauxlib.h"

#include "alanguage.h"
#include "alanguagelib.h"

#define ALANGUAGE_MODNAME "alanguage"

static int alanguagelib_project_pollone(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf project object is null");
    return alanguage_project_pollone(*c, L);
}

static int alanguagelib_destroy_abnfproject(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    if (c) delete_abnfproject(*c);
    return 0;
}

static int alanguagelib_create_abnfproject(lua_State* L)
{
    const char* abnf_buffer = luaL_checkstring(L, 1);
    luaL_argcheck(L, abnf_buffer != 0, 1, "abnf buffer is null");

    void** c = (void**)lua_newuserdata(L, sizeof(void**));
    lua_newtable(L);
    lua_pushcfunction(L, alanguagelib_destroy_abnfproject);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    *c = create_abnfproject(abnf_buffer);
    return 1;
}

static int alanguagelib_abnfproject_queryrulecolor(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf project object is null");

    return abnfproject_queryrulecolor(*c, L);
}

static int alanguagelib_destroy_abnffile(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    if (c) delete_abnffile(*c);
    return 0;
}

static int alanguagelib_create_abnffile(lua_State* L)
{
    void** project = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, project != 0, 1, "abnfproject is null");
    const char* full_path = luaL_checkstring(L, 2);
    luaL_argcheck(L, full_path != 0, 2, "full_path is null");

    size_t len;
    const char* text = luaL_checklstring(L, 3, &len);
    luaL_argcheck(L, text != 0, 3, "text is null");

    void** c = (void**)lua_newuserdata(L, sizeof(void**));
    lua_newtable(L);
    lua_pushcfunction(L, alanguagelib_destroy_abnffile);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    *c = create_abnffile(*project, full_path, text, len);
    return 1;
}

static int alanguagelib_project_updatefile(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf project object is null");
    const char* module_path = luaL_checkstring(L, 2);
    luaL_argcheck(L, module_path != 0, 2, "module_path is null");
    const char* full_path = luaL_checkstring(L, 3);
    luaL_argcheck(L, full_path != 0, 3, "full_path is null");
    int version = (int)luaL_checkinteger(L, 4);
    alanguage_project_updatefile(*c, module_path, full_path, version);
    return 0;
}

static int alanguagelib_project_tempfile(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf project object is null");
    const char* module_path = luaL_checkstring(L, 2);
    luaL_argcheck(L, module_path != 0, 2, "module_path is null");
    const char* full_path = luaL_checkstring(L, 3);
    luaL_argcheck(L, full_path != 0, 3, "full_path is null");
    size_t len = 0;
    const char* text = luaL_checklstring(L, 4, &len);
    luaL_argcheck(L, text != 0, 4, "text is null");
    int version = (int)luaL_checkinteger(L, 5);
    alanguage_project_tempfile(*c, module_path, full_path, text, len, version);
    return 0;
}

static int alanguagelib_project_removefile(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf project object is null");
    const char* full_path = luaL_checkstring(L, 2);
    luaL_argcheck(L, full_path != 0, 2, "full_path is null");

    alanguage_project_removefile(*c, full_path);
    return 0;
}

static int alanguagelib_project_clear(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf project object is null");

    alanguage_project_clear(*c);
    return 0;
}

static int alanguagelib_abnffile_settext(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    size_t len = 0;
    const char* text = luaL_checklstring(L, 3, &len);
    luaL_argcheck(L, text != 0, 3, "text is null");
    abnffile_settext(*c, version, text, len);
    return 0;
}

static int alanguagelib_abnffile_inserttext(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    size_t len = 0;
    const char* text = luaL_checklstring(L, 3, &len);
    luaL_argcheck(L, text != 0, 3, "text is null");
    int it_line = (int)luaL_checkinteger(L, 4);
    int it_char = (int)luaL_checkinteger(L, 5);
    abnffile_inserttext(*c, version, text, len, it_line - 1, it_char);
    return 0;
}

static int alanguagelib_abnffile_deletetext(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int it_line_start = (int)luaL_checkinteger(L, 3);
    int it_char_start = (int)luaL_checkinteger(L, 4);
    int it_line_end = (int)luaL_checkinteger(L, 5);
    int it_char_end = (int)luaL_checkinteger(L, 6);
    abnffile_deletetext(*c, version, it_line_start-1, it_char_start, it_line_end - 1, it_char_end);
    return 0;
}

static int alanguagelib_abnffile_querycolor(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int query_id = (int)luaL_checkinteger(L, 2);
    int version = (int)luaL_checkinteger(L, 3);
    int line = (int)luaL_checkinteger(L, 4);
    abnffile_querycolor(*c, query_id, version, line - 1);
    return 0;
}

static int alanguagelib_abnffile_queryinfo(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int query_id = (int)luaL_checkinteger(L, 2);
    int version = (int)luaL_checkinteger(L, 3);
    int it_line = (int)luaL_checkinteger(L, 4);
    int it_char = (int)luaL_checkinteger(L, 5);
    abnffile_queryinfo(*c, query_id, version, it_line - 1, it_char);
    return 0;
}

static int alanguagelib_abnffile_querygoto(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int query_id = (int)luaL_checkinteger(L, 2);
    int version = (int)luaL_checkinteger(L, 3);
    int it_line = (int)luaL_checkinteger(L, 4);
    int it_char = (int)luaL_checkinteger(L, 5);
    abnffile_querygoto(*c, query_id, version, it_line - 1, it_char);
    return 0;
}

static int alanguagelib_abnffile_querycomplete(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int query_id = (int)luaL_checkinteger(L, 2);
    int version = (int)luaL_checkinteger(L, 3);
    int it_line = (int)luaL_checkinteger(L, 4);
    int it_char = (int)luaL_checkinteger(L, 5);
    abnffile_querycomplete(*c, query_id, version, it_line - 1, it_char);
    return 0;
}

static int alanguagelib_abnffile_queryerror(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int query_id = (int)luaL_checkinteger(L, 2);
    int version = (int)luaL_checkinteger(L, 3);
    int force = lua_toboolean(L, 4);
    abnffile_queryerror(*c, query_id, version, force);
    return 0;
}

static int alanguagelib_abnffile_querydesiredindent(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int it_line = (int)luaL_checkinteger(L, 3);
    int it_char = (int)luaL_checkinteger(L, 4);

    int indent = abnffile_querydesiredindent(*c, version, it_line - 1, it_char);
    lua_pushinteger(L, indent);
    return 1;
}

static int alanguagelib_abnffile_queryformateindent(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int it_line = (int)luaL_checkinteger(L, 3);
    int it_char = (int)luaL_checkinteger(L, 4);

    int indent = abnffile_queryformateindent(*c, version, it_line - 1, it_char);
    lua_pushinteger(L, indent);
    return 1;
}

static int alanguagelib_abnffile_queryautopair(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int it_line = (int)luaL_checkinteger(L, 3);
    int it_char = (int)luaL_checkinteger(L, 4);
    const char* left_pair = luaL_checkstring(L, 5);
    luaL_argcheck(L, left_pair != 0, 5, "left_pair is null");
    const char* right_pair = luaL_checkstring(L, 6);
    luaL_argcheck(L, right_pair != 0, 6, "right_pair is null");
    lua_pushboolean(L, abnffile_queryautopair(*c, version, it_line - 1, it_char, left_pair, right_pair));
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
  {"abnfproject_pollone", alanguagelib_project_pollone},

  {"create_abnfproject", alanguagelib_create_abnfproject},
  {"abnfproject_queryrulecolor", alanguagelib_abnfproject_queryrulecolor},
  {"create_abnffile", alanguagelib_create_abnffile},

  {"abnfproject_updatefile", alanguagelib_project_updatefile},
  {"abnfproject_tempfile", alanguagelib_project_tempfile},
  {"abnfproject_removefile", alanguagelib_project_removefile},
  {"abnfproject_clear", alanguagelib_project_clear},

  {"abnffile_settext", alanguagelib_abnffile_settext},
  {"abnffile_inserttext", alanguagelib_abnffile_inserttext},
  {"abnffile_deletetext", alanguagelib_abnffile_deletetext},
  
  {"abnffile_querycolor", alanguagelib_abnffile_querycolor},
  {"abnffile_queryinfo", alanguagelib_abnffile_queryinfo},
  {"abnffile_querygoto", alanguagelib_abnffile_querygoto},
  {"abnffile_querycomplete", alanguagelib_abnffile_querycomplete},
  {"abnffile_queryerror", alanguagelib_abnffile_queryerror},

  {"abnffile_querydesiredindent", alanguagelib_abnffile_querydesiredindent},
  {"abnffile_queryformateindent", alanguagelib_abnffile_queryformateindent},
  {"abnffile_queryautopair", alanguagelib_abnffile_queryautopair},

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
