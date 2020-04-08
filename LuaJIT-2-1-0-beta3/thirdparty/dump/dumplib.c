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

#include "dumplib.h"
#include "dump.h"

static int dumplib_setup(lua_State* L)
{
    const char* name = luaL_checkstring(L, 1);
    dump_setup(name);
    return 0;
}

static struct luaL_Reg dumplib[] = {
  {"setup", dumplib_setup},
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
    lua_pushliteral(L, "dump for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "dump 1.0");
    lua_settable(L, -3);
}

int luaopen_dump(lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, dumplib, 0);
  set_info(L);
  lua_pushvalue(L, -1);
  lua_setglobal(L, "dump");
  return 1;
}
