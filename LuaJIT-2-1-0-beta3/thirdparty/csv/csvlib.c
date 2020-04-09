
#include "csvlib.h"
#include "csv.h"

#include "lua.h"
#include "lauxlib.h"

#define CSV_MODNAME "csv"

static int csvlib_destroy(lua_State* L)
{
    csv* c = (csv*)lua_touserdata(L, 1);
    if (c) csv_clear(c);
    return 0;
}

static int csvlib_create(lua_State* L)
{
    csv* ts = (csv*)lua_newuserdata(L, sizeof(csv));
    lua_newtable(L);
    lua_pushcfunction(L, csvlib_destroy);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    csv_init(ts);
    return 1;
}

static int csvlib_clear(lua_State* L)
{
    csv* c = (csv*)lua_touserdata(L, 1);
    if (c) csv_clear(c);
    return 0;
}

static int csvlib_load(lua_State* L)
{
    csv* c = (csv*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "csv object is null");
    const char* path = luaL_checkstring(L, 2);
    int loop = (int)luaL_checkinteger(L, 3);
    kstring_t* error = (kstring_t*)calloc(1, sizeof(kstring_t));
    if (!csv_load(c, path, error))
        lua_pushstring(L, ks_str(error));
    else
        lua_pushnil(L);
    free(error->s); free(error);
    return 1;
}

static int csvlib_getpath(lua_State* L)
{
    csv* c = (csv*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "csv object is null");
    const char* path = csv_getpath(c);
    if (path)
        lua_pushstring(L, path);
    else
        lua_pushstring(L, "");
    return 1;
}

static int csvlib_readcell(lua_State* L)
{
    csv* c = (csv*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "csv object is null");
    int row = (int)luaL_checkinteger(L, 2);
    int col = (int)luaL_checkinteger(L, 3);
    const char* data = csv_readcell(c, row - 1, col - 1);
    if (data)
        lua_pushstring(L, data);
    else
        lua_pushstring(L, "");
    return 1;
}

static int csvlib_rowcount(lua_State* L)
{
    csv* c = (csv*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "csv object is null");
    lua_pushinteger(L, csv_rowcount(c));
    return 1;
}

static int csvlib_colcount(lua_State* L)
{
    csv* c = (csv*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "csv object is null");
    lua_pushinteger(L, csv_colcount(c));
    return 1;
}

/*
** Assumes the table is on top of the stack.
*/
static void set_info(lua_State* L) {
    lua_pushliteral(L, "_COPYRIGHT");
    lua_pushliteral(L, "Copyright (C) 2003-2019 ALittle");
    lua_settable(L, -3);
    lua_pushliteral(L, "_DESCRIPTION");
    lua_pushliteral(L, "csv for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "csv 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg csvlib[] = {
  {"create", csvlib_create},
  {"load", csvlib_load},
  {"clear", csvlib_clear},
  {"getpath", csvlib_getpath},
  {"readcell", csvlib_readcell},
  {"rowcount", csvlib_rowcount},
  {"colcount", csvlib_colcount},
  {NULL, NULL}
};

int luaopen_csv(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, csvlib, 0);
    set_info(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, CSV_MODNAME);
    return 1;
}
