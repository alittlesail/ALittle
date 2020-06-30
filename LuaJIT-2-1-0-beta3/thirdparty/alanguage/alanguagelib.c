
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
    void** c = (void**)lua_newuserdata(L, sizeof(void**));
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
    void** factory = lua_touserdata(L, 3);
    luaL_argcheck(L, factory != 0, 3, "factory object is null");
    const char* r = abnf_load(*c, buffer, *factory);
    if (r) lua_pushstring(L, r);
    else lua_pushnil(L);
    return 1;
}

static int alanguagelib_abnffile_settext(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    size_t len = 0;
    const char* text = luaL_checklstring(L, 2, &len);
    luaL_argcheck(L, text != 0, 2, "text is null");
    abnffile_settext(*c, text, len);
    return 0;
}

static int alanguagelib_abnffile_inserttext(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    size_t len = 0;
    const char* text = luaL_checklstring(L, 2, &len);
    luaL_argcheck(L, text != 0, 2, "text is null");
    int it_line = (int)luaL_checkinteger(L, 3);
    int it_char = (int)luaL_checkinteger(L, 4);
    abnffile_inserttext(*c, text, len, it_line - 1, it_char);
    return 0;
}

static int alanguagelib_abnffile_deletetext(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int it_line_start = (int)luaL_checkinteger(L, 2);
    int it_char_start = (int)luaL_checkinteger(L, 3);
    int it_line_end = (int)luaL_checkinteger(L, 4);
    int it_char_end = (int)luaL_checkinteger(L, 5);
    abnffile_deletetext(*c, it_line_start-1, it_char_start, it_line_end - 1, it_char_end);
    return 0;
}

static int alanguagelib_abnffile_querycolor(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int line = (int)luaL_checkinteger(L, 3);
    int count = 0;
    const struct ABnfQueryColor** list = abnffile_querycolor(*c, version, line - 1, &count);
    lua_newtable(L);
    for (int i = 0; i < count; ++i)
    {
        const struct ABnfQueryColor* color = list[i];
        lua_newtable(L);
        lua_pushinteger(L, color->line_start + 1);
        lua_setfield(L, -2, "line_start");
        lua_pushinteger(L, color->char_start + 1);
        lua_setfield(L, -2, "char_start");
        lua_pushinteger(L, color->line_end + 1);
        lua_setfield(L, -2, "line_end");
        lua_pushinteger(L, color->char_end);
        lua_setfield(L, -2, "char_end");
        lua_pushinteger(L, color->tag);
        lua_setfield(L, -2, "tag");
        lua_pushboolean(L, color->blur);
        lua_setfield(L, -2, "blur");
        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

static int alanguagelib_abnffile_queryinfo(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int it_line = (int)luaL_checkinteger(L, 3);
    int it_char = (int)luaL_checkinteger(L, 4);

    struct ABnfQueryInfo info;
    int result = abnffile_queryinfo(*c, version, it_line - 1, it_char, &info);
    if (result == 0) lua_pushnil(L);
    else
    {
        lua_newtable(L);
        lua_pushinteger(L, info.line_start + 1);
        lua_setfield(L, -2, "line_start");
        lua_pushinteger(L, info.char_start + 1);
        lua_setfield(L, -2, "char_start");
        lua_pushinteger(L, info.line_end + 1);
        lua_setfield(L, -2, "line_end");
        lua_pushinteger(L, info.char_end);
        lua_setfield(L, -2, "char_end");
        lua_pushstring(L, info.info);
        lua_setfield(L, -2, "info");
    }
    return 1;
}

static int alanguagelib_abnffile_querygoto(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int it_line = (int)luaL_checkinteger(L, 3);
    int it_char = (int)luaL_checkinteger(L, 4);

    struct ABnfQueryGoto info;
    int result = abnffile_querygoto(*c, version, it_line - 1, it_char, &info);
    if (result == 0) lua_pushnil(L);
    else
    {
        lua_newtable(L);
        lua_pushinteger(L, info.line_start + 1);
        lua_setfield(L, -2, "line_start");
        lua_pushinteger(L, info.char_start + 1);
        lua_setfield(L, -2, "char_start");
        lua_pushinteger(L, info.line_end + 1);
        lua_setfield(L, -2, "line_end");
        lua_pushinteger(L, info.char_end);
        lua_setfield(L, -2, "char_end");
        lua_pushstring(L, info.file_path);
        lua_setfield(L, -2, "file_path");
    }
    return 1;
}

static int alanguagelib_abnffile_querycomplete(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "abnf file object is null");
    int version = (int)luaL_checkinteger(L, 2);
    int it_line = (int)luaL_checkinteger(L, 3);
    int it_char = (int)luaL_checkinteger(L, 4);

    int count = 0;
    int line_start = 0;
    int char_start = 0;
    int line_end = 0;
    int char_end = 0;
    const struct ABnfQueryComplete* list = abnffile_querycomplete(*c, version, it_line - 1, it_char
        , &count, &line_start, &char_start, &line_end, &char_end);
    if (count <= 0)
    {
        lua_pushnil(L);
    }
    else
    {
        lua_newtable(L);
        lua_pushinteger(L, line_start + 1);
        lua_setfield(L, -2, "line_start");
        lua_pushinteger(L, char_start + 1);
        lua_setfield(L, -2, "char_start");
        lua_pushinteger(L, line_end + 1);
        lua_setfield(L, -2, "line_end");
        lua_pushinteger(L, char_end);
        lua_setfield(L, -2, "char_end");

        lua_newtable(L);
        for (int i = 0; i < count; ++i)
        {
            const struct ABnfQueryComplete* complete = list + i;
            lua_newtable(L);
            lua_pushstring(L, complete->complete);
            lua_setfield(L, -2, "complete");
            lua_pushstring(L, complete->descriptor);
            lua_setfield(L, -2, "descriptor");
            lua_pushinteger(L, complete->tag);
            lua_setfield(L, -2, "tag");
            lua_rawseti(L, -2, i + 1);
        }
        lua_setfield(L, -2, "complete_list");
    }
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
  {"abnffile_settext", alanguagelib_abnffile_settext},
  {"abnffile_inserttext", alanguagelib_abnffile_inserttext},
  {"abnffile_deletetext", alanguagelib_abnffile_deletetext},
  {"abnffile_querycolor", alanguagelib_abnffile_querycolor},
  {"abnffile_queryinfo", alanguagelib_abnffile_queryinfo},
  {"abnffile_querygoto", alanguagelib_abnffile_querygoto},
  {"abnffile_querycomplete", alanguagelib_abnffile_querycomplete},
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
