/**
*  $Id: md5lib.c,v 1.10 2008/05/12 20:51:27 carregal Exp $
*  Cryptographic and Hash functions for Lua
*  @author  Roberto Ierusalimschy
*/


#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../src/lua.h"
#include "../../src/lauxlib.h"

#include "utf8lib.h"

int GetByteCountOfOneWord(unsigned char first_char)
{
    unsigned char temp = 0x80;
    int num = 0;

    unsigned char char_value = first_char;

    if (char_value < 0x80) // ascii code.(0-127)
        return 1;
    while (temp & char_value)
    {
        ++num;
        temp = temp >> 1;
    }

    return num;
}

static int CalcWordCount(lua_State* L)
{
    size_t l = 0;
    const char* str = luaL_checklstring(L, 1, &l);
    int count = 0;

    size_t index = 0;
    while (index < l)
    {
        index += GetByteCountOfOneWord(str[index]);
        ++count;
    }

    lua_pushnumber(L, count);
    return 1;
}

static int CalcByteCountByWordCount(lua_State* L)
{
    size_t l = 0;
    const char* str = luaL_checkstring(L, 1, &l);
    int word_count = (int)luaL_checknumber(L, 2);

    const char* old_str = str;
    int length = 0;

    size_t index = 0;
    while (index < l)
    {
        index += GetByteCountOfOneWord(str[index]);
        ++length;
        if (length >= word_count) break;
    }
    lua_pushnumber(L, (int)index);
    return 1;
}

static struct luaL_Reg utf8lib[] = {
  {"wordcount", CalcWordCount},
  {"bytecount", CalcByteCountByWordCount},
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
