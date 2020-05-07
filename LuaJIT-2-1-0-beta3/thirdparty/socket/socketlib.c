
#include "socketlib.h"
#include "socket.h"

#include "lua.h"
#include "lauxlib.h"

#define SOCKET_MODNAME "socket"

static int socketlib_destroy(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    if (c) socket_clear(c);
    return 0;
}

static int socketlib_create(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_newuserdata(L, sizeof(struct _socket));
    lua_newtable(L);
    lua_pushcfunction(L, socketlib_destroy);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    socket_init(c);
    return 1;
}

static int socketlib_connect(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    const char* ip = luaL_checkstring(L, 3);
    int port = (int)luaL_checkinteger(L, 4);
    socket_connect(c, id, ip, port);
    return 0;
}

static int socketlib_close(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_close(c, id);
    return 0;
}

static int socketlib_readuint8(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readuint8(c, id);
    return 0;
}

static int socketlib_readint8(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readint8(c, id);
    return 0;
}

static int socketlib_readuint16(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readuint16(c, id);
    return 0;
}

static int socketlib_readint16(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readint16(c, id);
    return 0;
}

static int socketlib_readuint32(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readuint32(c, id);
    return 0;
}

static int socketlib_readint32(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readint32(c, id);
    return 0;
}

static int socketlib_readuint64(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readuint64(c, id);
    return 0;
}

static int socketlib_readint64(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readint64(c, id);
    return 0;
}

static int socketlib_readfloat(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readfloat(c, id);
    return 0;
}

static int socketlib_readdouble(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    socket_readdouble(c, id);
    return 0;
}

static int socketlib_readprotobuf(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    const char* name = luaL_checkstring(L, 3);
    int len = (int)luaL_checkinteger(L, 4);
    socket_readprotobuf(c, id, name, len);
    return 0;
}

static int socketlib_writeuint8(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    unsigned char value = (unsigned char)luaL_checkinteger(L, 3);
    socket_writeuint8(c, id, value);
    return 0;
}

static int socketlib_writeint8(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    char value = (char)luaL_checkinteger(L, 3);
    socket_writeint8(c, id, value);
    return 0;
}

static int socketlib_writeuint16(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    unsigned short value = (unsigned short)luaL_checkinteger(L, 3);
    socket_writeuint16(c, id, value);
    return 0;
}

static int socketlib_writeint16(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    short value = (short)luaL_checkinteger(L, 3);
    socket_writeint16(c, id, value);
    return 0;
}

static int socketlib_writeuint32(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    unsigned int value = (unsigned int)luaL_checkinteger(L, 3);
    socket_writeuint32(c, id, value);
    return 0;
}

static int socketlib_writeint32(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    int value = (int)luaL_checkinteger(L, 3);
    socket_writeint32(c, id, value);
    return 0;
}

static int socketlib_writeuint64(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    unsigned long long value = (unsigned long long)luaL_checkinteger(L, 3);
    socket_writeuint64(c, id, value);
    return 0;
}

static int socketlib_writeint64(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    long long value = (long long)luaL_checkinteger(L, 3);
    socket_writeint64(c, id, value);
    return 0;
}

static int socketlib_writefloat(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    float value = (float)luaL_checknumber(L, 3);
    socket_writefloat(c, id, value);
    return 0;
}

static int socketlib_writedouble(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    double value = (double)luaL_checknumber(L, 3);
    socket_writedouble(c, id, value);
    return 0;
}

static int socketlib_writeprotobuf(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int id = (int)luaL_checkinteger(L, 2);
    const char* name = luaL_checkstring(L, 3);
    luaL_argcheck(L, lua_istable(L, 4), 4, "table is null");
    socket_writeprotobuf(c, id, name, L, 4);
    return 0;
}

static int socketlib_calcprotobufsize(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    const char* name = luaL_checkstring(L, 2);
    luaL_argcheck(L, lua_istable(L, 3), 3, "table is null");
    lua_pushinteger(L, socket_calcprotobufsize(c, name, L, 3));
    return 1;
}

static int socketlib_timer(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    int delay_ms = (int)luaL_checkinteger(L, 2);
    socket_timer(c, delay_ms);
    return 0;
}

static int socketlib_poll(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    socket_event* event = socket_runone(c);
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
        if (event->type == TIMER)
        {
            lua_pushinteger(L, event->time);
            lua_setfield(L, -2, "time");
        }
        socket_releaseevent(c, event);
    }
    return 1;
}

static int socketlib_exit(lua_State* L)
{
    struct _socket* c = (struct _socket*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "socket object is null");
    socket_exit(c);
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
    lua_pushliteral(L, "socket for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "socket 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg socketlib[] = {
    {"create", socketlib_create},
    {"poll", socketlib_poll},
    {"timer", socketlib_timer},

    {"connect", socketlib_connect},
    {"close", socketlib_close},

    {"readuint8", socketlib_readuint8},
    {"readint8", socketlib_readint8},
    {"readuint16", socketlib_readuint16},
    {"readint16", socketlib_readint16},
    {"readuint32", socketlib_readuint32},
    {"readint32", socketlib_readint32},
    {"readuint64", socketlib_readuint64},
    {"readint64", socketlib_readint64},
    {"readfloat", socketlib_readfloat},
    {"readdouble", socketlib_readdouble},
    {"readprotobuf", socketlib_readprotobuf},

    {"writeuint8", socketlib_writeuint8},
    {"writeint8", socketlib_writeint8},
    {"writeuint16", socketlib_writeuint16},
    {"writeint16", socketlib_writeint16},
    {"writeuint32", socketlib_writeuint32},
    {"writeint32", socketlib_writeint32},
    {"writeuint64", socketlib_writeuint64},
    {"writeint64", socketlib_writeint64},
    {"writefloat", socketlib_writefloat},
    {"writedouble", socketlib_writedouble},
    {"writeprotobuf", socketlib_writeprotobuf},

    {"calcprotobufsize", socketlib_calcprotobufsize},

    {NULL, NULL}
};

int luaopen_socket(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, socketlib, 0);
    set_info(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, SOCKET_MODNAME);
    return 1;
}
