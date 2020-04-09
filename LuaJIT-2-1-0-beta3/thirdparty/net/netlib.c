
#include "netlib.h"
#include "net.h"

#include "lua.h"
#include "lauxlib.h"

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

static int netlib_connect(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    const char* ip = luaL_checkstring(L, 3);
    int port = (int)luaL_checkinteger(L, 4);
    net_connect(c, id, ip, port);
    return 0;
}

static int netlib_isconnected(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    lua_pushboolean(L, net_isconnected(c, id));
    return 1;
}

static int netlib_isconnecting(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    lua_pushboolean(L, net_isconnecting(c, id));
    return 1;
}

static int netlib_close(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    net_close(c, id);
    return 0;
}

static int netlib_send(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    write_factory* factory = (write_factory*)lua_touserdata(L, 3);
    luaL_argcheck(L, factory != 0, 2, "write factory object is null");
    net_send(c, id, factory);
    return 0;
}

static int netlib_httpget(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    const char* url = luaL_checkstring(L, 3);
    net_httpget(c, id, url);
    return 0;
}

static int netlib_httpdownload(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    const char* url = luaL_checkstring(L, 3);
    const char* file_path = luaL_checkstring(L, 4);
    net_httpdownload(c, id, url, file_path);
    return 0;
}

static int netlib_httppost(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
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
    int id = (int)luaL_checkinteger(L, 2);
    const char* url = luaL_checkstring(L, 3);
    const char* file_path = luaL_checkstring(L, 4);
    net_httpupload(c, id, url, file_path);
    return 0;
}

static int netlib_httpstopget(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    net_httpstopget(c, id);
    return 0;
}

static int netlib_httpstoppost(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    net_httpstoppost(c, id);
    return 0;
}

static int netlib_httpstopdownload(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    net_httpstopdownload(c, id);
    return 0;
}

static int netlib_httpstopupload(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int id = (int)luaL_checkinteger(L, 2);
    net_httpstopupload(c, id);
    return 0;
}

static int netlib_timer(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    int delay_ms = (int)luaL_checkinteger(L, 2);
    net_timer(c, delay_ms);
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
        lua_pushinteger(L, event->type);
        lua_setfield(L, -2, "type");
        lua_pushinteger(L, event->id);
        lua_setfield(L, -2, "id");
        if (event->content)
        {
            if (ks_str(event->content))
                lua_pushstring(L, ks_str(event->content));
            else
                lua_pushstring(L, "");
            lua_setfield(L, -2, "content");
        }
        if (event->error)
        {
            if (ks_str(event->error))
                lua_pushstring(L, ks_str(event->error));
            else
                lua_pushstring(L, "");
            lua_setfield(L, -2, "error");
        }
        if (event->type == TIMER)
        {
            lua_pushinteger(L, event->time);
            lua_setfield(L, -2, "time");
        }
        else if (event->type == HTTP_FILE_PROGRESS)
        {
            lua_pushinteger(L, event->cur_size);
            lua_setfield(L, -2, "cur_size");
            lua_pushinteger(L, event->total_size);
            lua_setfield(L, -2, "total_size");
        }
        else if (event->type == MSG_MESSAGE)
        {
            lua_pushlightuserdata(L, event->rfactory);
            lua_setfield(L, -2, "rfactory");
        }
        net_releaseevent(c, event);
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

static int netlib_wfactorydestroy(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    if (c) net_wfactoryclear(c);
    return 0;
}

static int netlib_createwfactory(lua_State* L)
{
    write_factory* c = (write_factory*)lua_newuserdata(L, sizeof(write_factory));
    lua_newtable(L);
    lua_pushcfunction(L, netlib_wfactorydestroy);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    net_wfactoryinit(c);
    return 1;
}

static int netlib_wfactorysetid(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    int id = (int)luaL_checkinteger(L, 2);
    net_wfactorysetid(c, id);
    return 0;
}

static int netlib_wfactorysetrpcid(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    int id = (int)luaL_checkinteger(L, 2);
    net_wfactorysetrpcid(c, id);
    return 0;
}

static int netlib_wfactoryresetoffset(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    net_wfactoryresetoffset(c);
    return 0;
}

static int netlib_wfactorygetoffset(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    lua_pushinteger(L, net_wfactorygetoffset(c));
    return 1;
}

static int netlib_wfactorysetint(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    int offset = (int)luaL_checkinteger(L, 2);
    int value = (int)luaL_checkinteger(L, 3);
    net_wfactorysetint(c, offset, value);
    return 0;
}

static int netlib_wfactorywritebool(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    char value = (char)luaL_checkinteger(L, 2);
    lua_pushinteger(L, net_wfactorywritebool(c, value));
    return 1;
}

static int netlib_wfactorywriteint(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    int value = (int)luaL_checkinteger(L, 2);
    lua_pushinteger(L, net_wfactorywriteint(c, value));
    return 1;
}

static int netlib_wfactorywritelong(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    int value = (int)luaL_checkinteger(L, 2);
    lua_pushinteger(L, net_wfactorywritelong(c, value));
    return 1;
}

static int netlib_wfactorywritedouble(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    double value = luaL_checknumber(L, 2);
    lua_pushinteger(L, net_wfactorywritedouble(c, value));
    return 1;
}

static int netlib_wfactorywritestring(lua_State* L)
{
    write_factory* c = (write_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "write_factory object is null");
    size_t l;
    const char* value = luaL_checklstring(L, 2, &l);
    lua_pushinteger(L, net_wfactorywritestring(c, value, (int)l));
    return 1;
}

static int netlib_releaserfactory(lua_State* L)
{
    net* c = (net*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "net object is null");
    read_factory* r = (read_factory*)lua_touserdata(L, 2);
    luaL_argcheck(L, r != 0, 2, "read_factory object is null");
    net_releaserfactory(c, r);
    return 0;
}

static int netlib_rfactorygettotalsize(lua_State* L)
{
    read_factory* c = (read_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "read_factory object is null");
    lua_pushinteger(L, net_rfactorygettotalsize(c));
    return 1;
}

static int netlib_rfactoryreadbool(lua_State* L)
{
    read_factory* c = (read_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "read_factory object is null");
    lua_pushboolean(L, net_rfactoryreadbool(c));
    return 1;
}

static int netlib_rfactoryreadint(lua_State* L)
{
    read_factory* c = (read_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "read_factory object is null");
    lua_pushinteger(L, net_rfactoryreadint(c));
    return 1;
}

static int netlib_rfactoryreadlong(lua_State* L)
{
    read_factory* c = (read_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "read_factory object is null");
    lua_pushinteger(L, (int)net_rfactoryreadlong(c));
    return 1;
}

static int netlib_rfactoryreadstring(lua_State* L)
{
    read_factory* c = (read_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "read_factory object is null");
    lua_pushstring(L, net_rfactoryreadstring(c));
    return 1;
}

static int netlib_rfactoryreaddouble(lua_State* L)
{
    read_factory* c = (read_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "read_factory object is null");
    lua_pushnumber(L, net_rfactoryreaddouble(c));
    return 1;
}

static int netlib_rfactorygetreadsize(lua_State* L)
{
    read_factory* c = (read_factory*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "read_factory object is null");
    lua_pushinteger(L, net_rfactorygetreadsize(c));
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
    lua_pushliteral(L, "net for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "net 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg netlib[] = {
    {"create", netlib_create},
    {"poll", netlib_poll},
    {"exit", netlib_exit},

    {"get", netlib_httpget},
    {"post", netlib_httppost},
    {"download", netlib_httpdownload},
    {"upload", netlib_httpupload},
    {"stopget", netlib_httpstopget},
    {"stoppost", netlib_httpstoppost},
    {"stopdownload", netlib_httpstopdownload},
    {"stopupload", netlib_httpstopupload},

    {"connect", netlib_connect},
    {"isconnected", netlib_isconnected},
    {"isconnecting", netlib_isconnecting},
    {"close", netlib_close},
    {"send", netlib_send},

    {"timer", netlib_timer},

    {"createwfactory", netlib_createwfactory},
    {"wfactorysetid", netlib_wfactorysetid},
    {"wfactorysetrpcid", netlib_wfactorysetrpcid},
    {"wfactoryresetoffset", netlib_wfactoryresetoffset},
    {"wfactorygetoffset", netlib_wfactorygetoffset},
    {"wfactorysetint", netlib_wfactorysetint},
    {"wfactorywriteint", netlib_wfactorywriteint},
    {"wfactorywritelong", netlib_wfactorywritelong},
    {"wfactorywritestring", netlib_wfactorywritestring},
    {"wfactorywritedouble", netlib_wfactorywritedouble},

    {"rfactoryrelease", netlib_releaserfactory},
    {"rfactorygettotalsize", netlib_rfactorygettotalsize},
    {"rfactoryreadbool", netlib_rfactoryreadbool},
    {"rfactoryreadint", netlib_rfactoryreadint},
    {"rfactoryreadlong", netlib_rfactoryreadlong},
    {"rfactoryreadstring", netlib_rfactoryreadstring},
    {"rfactoryreaddouble", netlib_rfactoryreaddouble},
    {"rfactorygetreadsize", netlib_rfactorygetreadsize},

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
