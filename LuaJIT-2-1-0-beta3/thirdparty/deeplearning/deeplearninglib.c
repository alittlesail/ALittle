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

#include "deeplearninglib.h"
#include "tensorflow/c/c_api.h"

static struct luaL_Reg deeplearninglib[] = {
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
    lua_pushliteral(L, "deeplearning for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "deeplearning 1.0");
    lua_settable(L, -3);
}

int luaopen_deeplearning (lua_State *L) {
  lua_newtable(L);
  luaL_setfuncs(L, deeplearninglib, 0);
  set_info(L);
  lua_pushvalue(L, -1);
  lua_setglobal(L, "deeplearning");
  return 1;
}
