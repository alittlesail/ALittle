
#include "protobuflib.h"
#include "protobuf.h"

#include "lua.h"
#include "lauxlib.h"

#define PROTOBUF_MODNAME "protobuf"

// importer
static int protobuflib_destroyimporter(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    if (c) protobuf_freeimporter(*c);
    return 0;
}

static int protobuflib_createimporter(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    void** c = (void**)lua_newuserdata(L, sizeof(void**));
    lua_newtable(L);
    lua_pushcfunction(L, protobuflib_destroyimporter);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    *c = protobuf_createimporter(path);
    return 1;
}

static int protobuflib_importerimport(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "importer object is null");
    const char* path = luaL_checkstring(L, 2);
    lua_pushlightuserdata(L, protobuf_importerimport(c, path));
    return 1;
}

// file descriptor
static int protobuflib_getfiledescriptmessagetypecount(lua_State* L)
{
    void* c = (void*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "file descriptor object is null");
    lua_pushinteger(L, protobuf_getfiledescriptmessagetypecount(c));
    return 1;
}

static int protobuflib_getfiledescriptmessagetype(lua_State* L)
{
    void* c = (void*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "file descriptor object is null");
    int index = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_getfiledescriptmessagetype(c, index));
    return 1;
}

// message
static int protobuflib_getmessagename(lua_State* L)
{
    void* c = (void*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushstring(L, protobuf_getmessagename(c));
    return 1;
}

static int protobuflib_getmessagefullname(lua_State* L)
{
    void* c = (void*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushstring(L, protobuf_getmessagefullname(c));
    return 1;
}

static int protobuflib_getmessagefieldcount(lua_State* L)
{
    void* c = (void*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushinteger(L, protobuf_getmessagefieldcount(c));
    return 1;
}

static int protobuflib_getmessagefield(lua_State* L)
{
    void* c = (void*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    int index = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_getmessagefield(c, index));
    return 1;
}

static int protobuflib_findmessagefieldbyname(lua_State* L)
{
    void* c = (void*)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    const char* name = luaL_checkstring(L, 2);
    lua_pushlightuserdata(L, protobuf_findmessagefieldbyname(c, name));
    return 1;
}

// factory
static int protobuflib_destroyfactory(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    if (c) protobuf_freefactory(*c);
    return 0;
}

static int protobuflib_createfactory(lua_State* L)
{
    void** c = (void**)lua_newuserdata(L, sizeof(void**));
    lua_newtable(L);
    lua_pushcfunction(L, protobuflib_destroyfactory);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    *c = protobuf_createfactory();
    return 1;
}

static int protobuflib_factorycreatemessage(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "factory object is null");
    void* descriptor = lua_touserdata(L, 2);
    luaL_argcheck(L, descriptor != 0, 2, "descriptor object is null");
    lua_pushlightuserdata(L, protobuf_factorycreatemessage(c, descriptor));
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
    lua_pushliteral(L, "protobuf for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "protobuf 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg protobuflib[] = {
    {"create_importer", protobuflib_createimporter},
    {"importerimport", protobuflib_importerimport},

    {"get_file_descript_message_type_count", protobuflib_getfiledescriptmessagetypecount},
    {"get_file_descript_message_type", protobuflib_getfiledescriptmessagetype},
    {"get_message_name", protobuflib_getmessagename},
    {"get_message_full_name", protobuflib_getmessagefullname},
    {"get_message_field_count", protobuflib_getmessagefieldcount},
    {"get_message_field", protobuflib_getmessagefield},
    {"find_message_field_by_name", protobuflib_findmessagefieldbyname},

    {"createfactory", protobuflib_createfactory},
    {"factorycreatemessage", protobuflib_factorycreatemessage},

    {NULL, NULL}
};

int luaopen_protobuf(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, protobuflib, 0);
    set_info(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, PROTOBUF_MODNAME);
    return 1;
}
