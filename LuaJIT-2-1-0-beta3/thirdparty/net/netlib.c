
#include "netlib.h"
#include "net.h"

#include "../../src/lua.h"
#include "../../src/lauxlib.h"

#define NET_MODNAME "net"

static int netlib_destroy(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    if (c) net_clear(c);
    return 0;
}

static int netlib_create(lua_State* L)
{
    net* c = (net*)lua_newuserdata(L, sizeof(net));
    lua_newtable(L);
    lua_pushcfunction(L, netlib_destroy);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    net_init(c);
    return 1;
}

static int netlib_httpget(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checknumber(L, 2);
    const char* url = luaL_checkstring(L, 3);
    net_httpget(c, id, url);
    return 0;
}

static int netlib_httpdownload(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checknumber(L, 2);
    const char* url = luaL_checkstring(L, 3);
    const char* file_path = luaL_checkstring(L, 4);
    net_httpdownload(c, id, url, file_path);
    return 0;
}

static int netlib_httppost(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checknumber(L, 2);
    const char* url = luaL_checkstring(L, 3);
    const char* type = luaL_checkstring(L, 4);
    const char* content = luaL_checkstring(L, 5);
    net_httppost(c, id, url, type, content);
    return 0;
}

static int netlib_httpupload(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checknumber(L, 2);
    const char* url = luaL_checkstring(L, 3);
    const char* file_path = luaL_checkstring(L, 4);
    net_httpupload(c, id, url, file_path);
    return 0;
}

static int netlib_poll(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    net_event* event = net_runone(c);
    if (event == 0)
    {
        lua_pushnil(L);
    }
    else
    {
        lua_newtable(L);
        lua_pushinteger(L, (int)event->type);
        lua_setfield(L, -2, "type");
        lua_pushinteger(L, (int)event->id);
        lua_setfield(L, -2, "id");
        if (event->content)
        {
            lua_pushstring(L, ks_str(event->content));
            lua_setfield(L, -2, "content");
        }
        lua_pushinteger(L, (int)event->cur_size);
        lua_setfield(L, -2, "cur_size");
        lua_pushinteger(L, (int)event->total_size);
        lua_setfield(L, -2, "total_size");

        net_freeevent(event);
    }
    return 1;
}

static int netlib_exit(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    net_exit(c);
    return 0;
}

/*
** Assumes the table is on top of the stack.
*/
static void set_info(lua_State* L) {
    lua_pushliteral(L, "_COPYRIGHT");
    lua_pushliteral(L, "Copyright (C) 2003-2019 ALittle");
    lua_settable(L, -3);
    lua_pushliteral(L, "_DESCRIPTION");
    lua_pushliteral(L, "net for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "net 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg netlib[] = {
  {"create", netlib_create},
  {"poll", netlib_poll},
  {"get", netlib_httpget},
  {"post", netlib_httppost},
  {"download", netlib_httpdownload},
  {"upload", netlib_httpupload},
  {"exit", netlib_exit},
  {NULL, NULL}
};

int luaopen_net(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, netlib, 0);
    set_info(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, NET_MODNAME);
    return 1;
}
