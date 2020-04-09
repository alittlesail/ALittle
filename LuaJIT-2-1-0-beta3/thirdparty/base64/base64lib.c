
#include "base64lib.h"
#include "base64.h"
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"

static int base64lib_encode(lua_State* L)
{
    size_t l;
    const char* message = luaL_checklstring(L, 1, &l);
    char* out = (char*)malloc(BASE64_ENCODE_OUT_SIZE(l));
    base64_encode(message, l, out);
    lua_pushstring(L, out);
    free(out);
    return 1;
}

static int base64lib_decode(lua_State* L)
{
    size_t l;
    const char* message = luaL_checklstring(L, 1, &l);
    char* out = (char*)malloc(BASE64_DECODE_OUT_SIZE(l));
    base64_decode(message, l, out);
    lua_pushstring(L, out);
    free(out);
    return 1;
}

static struct luaL_Reg base64lib[] = {
  {"encode", base64lib_encode},
  {"decode", base64lib_decode},
  {NULL, NULL}
};

static void set_info(lua_State* L) {
    lua_pushliteral(L, "_COPYRIGHT");
    lua_pushliteral(L, "Copyright (C) 2003-2019 WEI Zhicheng");
    lua_settable(L, -3);
    lua_pushliteral(L, "_DESCRIPTION");
    lua_pushliteral(L, "base64 for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "base64 1.0");
    lua_settable(L, -3);
}

int luaopen_base64(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, base64lib, 0);
    set_info(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, "base64");
    return 1;
}
