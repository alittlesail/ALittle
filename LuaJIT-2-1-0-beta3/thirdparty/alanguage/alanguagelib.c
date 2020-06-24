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

#include "alanguagelib.h"

#define ALANGUAGE_MODNAME "alanguage"

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
