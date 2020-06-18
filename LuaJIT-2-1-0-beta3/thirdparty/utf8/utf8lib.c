/**
*  $Id: md5lib.c,v 1.10 2008/05/12 20:51:27 carregal Exp $
*  Cryptographic and Hash functions for Lua
*  @author  Roberto Ierusalimschy
*/


#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"
#include "lauxlib.h"

#include "utf8.h"
#include "utf8lib.h"

static int utf8lib_CalcWordCount(lua_State* L)
{
    const char* str = luaL_checkstring(L, 1);
    lua_pushinteger(L, utf8_CalcWordCount(str));
    return 1;
}

static int utf8lib_CalcByteCountByWordCount(lua_State* L)
{
    const char* str = luaL_checkstring(L, 1);
    int offset = (int)luaL_checkinteger(L, 2);
    int word_count = (int)luaL_checkinteger(L, 3);

    lua_pushinteger(L, utf8_CalcByteCountByWordCount(str, offset, word_count));
    return 1;
}

static int utf8lib_ANSI2UTF8(lua_State* L)
{
    const char* str = luaL_checkstring(L, 1);
    const char* res = utf8_ANSI2UTF8(str);
    if (res == 0)
        lua_pushstring(L, str);
    else
    {
        lua_pushstring(L, res);
        free((void*)res);
    }
    return 1;
}

static int utf8lib_UTF82ANSI(lua_State* L)
{
    const char* str = luaL_checkstring(L, 1);
    const char* res = utf8_UTF82ANSI(str);
    if (res == 0)
        lua_pushstring(L, str);
    else
    {
        lua_pushstring(L, res);
        free((void*)res);
    }   
    return 1;
}

static struct luaL_Reg utf8lib[] = {
  {"wordcount", utf8lib_CalcWordCount},
  {"bytecount", utf8lib_CalcByteCountByWordCount},
  {"ansi2utf8", utf8lib_ANSI2UTF8},
  {"utf82ansi", utf8lib_UTF82ANSI},
  {NULL, NULL}
};

/*
** Assumes the table is on top of the stack.
*/
static void set_info(lua_State* L) {
    lua_pushliteral(L, "_COPYRIGHT");
    lua_pushliteral(L, "Copyright (C) 2003-2019 ALittle");
    lua_settable(L, -3);
    lua_pushliteral(L, "_DESCRIPTION");
    lua_pushliteral(L, "utf8 for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "utf8 1.0");
    lua_settable(L, -3);
}

int luaopen_utf8 (lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, utf8lib, 0);
  set_info(L);
  lua_pushvalue(L, -1);
  lua_setglobal(L, "utf8");
  return 1;
}
