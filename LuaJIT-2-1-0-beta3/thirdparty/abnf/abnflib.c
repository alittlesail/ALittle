
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lua.h"
#include "lauxlib.h"

#include "abnflib.h"

#define ABNF_MODNAME "abnf"

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
