
#include "protobuflib.h"
#include "protobuf.h"

#include "lua.h"
#include "lauxlib.h"

#define PROTOBUF_MODNAME "protobuf"

static int protobuflib_shutdown(lua_State* L)
{
    protobuf_shutdown();
    return 0;
}

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

static int protobuflib_importer_import(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "importer object is null");
    const char* path = luaL_checkstring(L, 2);
    lua_pushlightuserdata(L, protobuf_importer_import(*c, path));
    return 1;
}

// file descriptor
static int protobuflib_filedescriptor_messagetypecount(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "file descriptor object is null");
    lua_pushinteger(L, protobuf_filedescriptor_messagetypecount(c));
    return 1;
}

static int protobuflib_filedescriptor_messagetype(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "file descriptor object is null");
    int index = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_filedescriptor_messagetype(c, index));
    return 1;
}
static int protobuflib_filedescriptor_enumtypecount(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "file descriptor object is null");
    lua_pushinteger(L, protobuf_filedescriptor_enumtypecount(c));
    return 1;
}

static int protobuflib_filedescriptor_enumtype(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "file descriptor object is null");
    int index = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_filedescriptor_enumtype(c, index));
    return 1;
}

// message descriptor
static int protobuflib_messagedescriptor_name(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushstring(L, protobuf_messagedescriptor_name(c));
    return 1;
}

static int protobuflib_messagedescriptor_fullname(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushstring(L, protobuf_messagedescriptor_fullname(c));
    return 1;
}

static int protobuflib_messagedescriptor_fieldcount(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushinteger(L, protobuf_messagedescriptor_fieldcount(c));
    return 1;
}

static int protobuflib_messagedescriptor_field(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    int index = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_messagedescriptor_field(c, index));
    return 1;
}

static int protobuflib_messagedescriptor_findfieldbyname(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    const char* name = luaL_checkstring(L, 2);
    lua_pushlightuserdata(L, protobuf_messagedescriptor_findfieldbyname(c, name));
    return 1;
}

static int protobuflib_messagedescriptor_findfieldbynumber(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    int number = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_messagedescriptor_findfieldbynumber(c, number));
    return 1;
}

// enum descriptor
static int protobuflib_enumdescriptor_name(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushstring(L, protobuf_enumdescriptor_name(c));
    return 1;
}

static int protobuflib_enumdescriptor_fullname(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushstring(L, protobuf_enumdescriptor_fullname(c));
    return 1;
}

static int protobuflib_enumdescriptor_valuecount(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    lua_pushinteger(L, protobuf_enumdescriptor_valuecount(c));
    return 1;
}

static int protobuflib_enumdescriptor_value(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    int index = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_enumdescriptor_value(c, index));
    return 1;
}

static int protobuflib_enumdescriptor_findvaluebyname(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    const char* name = luaL_checkstring(L, 2);
    lua_pushlightuserdata(L, protobuf_enumdescriptor_findvaluebyname(c, name));
    return 1;
}

static int protobuflib_enumdescriptor_findvaluebynumber(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "descriptor object is null");
    int number = (int)luaL_checkinteger(L, 2);
    lua_pushlightuserdata(L, protobuf_enumdescriptor_findvaluebynumber(c, number));
    return 1;
}

// enum value descriptor
static int protobuflib_enumvaluedescriptor_name(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "enum value descriptor object is null");
    lua_pushstring(L, protobuf_enumvaluedescriptor_name(c));
    return 1;
}
static int protobuflib_enumvaluedescriptor_number(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "enum value descriptor object is null");
    lua_pushinteger(L, protobuf_enumvaluedescriptor_number(c));
    return 1;
}

// field descriptor
static int protobuflib_fielddescriptor_cpptype(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "field descriptor object is null");
    lua_pushinteger(L, protobuf_fielddescriptor_cpptype(c));
    return 1;
}
static int protobuflib_fielddescriptor_name(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "field descriptor object is null");
    lua_pushstring(L, protobuf_fielddescriptor_name(c));
    return 1;
}
static int protobuflib_fielddescriptor_cpptypename(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "field descriptor object is null");
    lua_pushstring(L, protobuf_fielddescriptor_cpptypename(c));
    return 1;
}
static int protobuflib_fielddescriptor_ismap(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "field descriptor object is null");
    lua_pushboolean(L, protobuf_fielddescriptor_ismap(c));
    return 1;
}
static int protobuflib_fielddescriptor_isrepeated(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "field descriptor object is null");
    lua_pushboolean(L, protobuf_fielddescriptor_isrepeated(c));
    return 1;
}
static int protobuflib_fielddescriptor_messagetype(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "field descriptor object is null");
    lua_pushlightuserdata(L, protobuf_fielddescriptor_messagetype(c));
    return 1;
}
static int protobuflib_fielddescriptor_enumtype(lua_State* L)
{
    void* c = lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "field descriptor object is null");
    lua_pushlightuserdata(L, protobuf_fielddescriptor_enumtype(c));
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

static int protobuflib_freemessage(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    if (m) protobuf_freemessage(m);
    return 0;
}

static int protobuflib_clonemessage(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "factory object is null");
    lua_pushlightuserdata(L, protobuf_clonemessage(L, m));
    return 1;
}

static int protobuflib_factory_createmessage(lua_State* L)
{
    void** c = (void**)lua_touserdata(L, 1);
    luaL_argcheck(L, c != 0, 1, "factory object is null");
    void* descriptor = lua_touserdata(L, 2);
    luaL_argcheck(L, descriptor != 0, 2, "descriptor object is null");
    lua_pushlightuserdata(L, protobuf_factory_createmessage(*c, descriptor));
    return 1;
}

// message
static int protobuflib_message_getdescriptor(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "message object is null");
    lua_pushlightuserdata(L, protobuf_message_getdescriptor(m));
    return 1;
}
static int protobuflib_message_getreflection(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "message object is null");
    lua_pushlightuserdata(L, protobuf_message_getreflection(m));
    return 1;
}
static int protobuflib_message_getbytesize(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "message object is null");
    lua_pushinteger(L, protobuf_message_getbytesize(m));
    return 1;
}
static int protobuflib_message_serializetoarray(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "message object is null");
    void* buffer = lua_touserdata(L, 2);
    luaL_argcheck(L, buffer != 0, 2, "buffer object is null");
    int size = (int)luaL_checkinteger(L, 3);
    lua_pushboolean(L, protobuf_message_serializetoarray(m, buffer, size));
    return 1;
}
static int protobuflib_message_parsefromarray(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "message object is null");
    void* buffer = lua_touserdata(L, 2);
    luaL_argcheck(L, buffer != 0, 2, "buffer object is null");
    int size = (int)luaL_checkinteger(L, 3);
    lua_pushboolean(L, protobuf_message_parsefromarray(m, buffer, size));
    return 1;
}

static int protobuflib_message_jsonencode(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "message object is null");
    const char* json = protobuf_message_jsonencode(m);
    if (json) lua_pushstring(L, json);
    else lua_pushnil(L);
    return 1;
}

static int protobuflib_message_jsondecode(lua_State* L)
{
    void* m = lua_touserdata(L, 1);
    luaL_argcheck(L, m != 0, 1, "message object is null");
    const char* json = luaL_checkstring(L, 2);
    lua_pushstring(L, protobuf_message_jsondecode(m, json));
    return 1;
}

// reflection
static int protobuflib_reflection_getmessage(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushlightuserdata(L, protobuf_reflection_getmessage(r, m, field));
    return 1;
}
static int protobuflib_reflection_getbool(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushboolean(L, protobuf_reflection_getbool(r, m, field));
    return 1;
}
static int protobuflib_reflection_getint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getint32(r, m, field));
    return 1;
}
static int protobuflib_reflection_getuint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getuint32(r, m, field));
    return 1;
}
static int protobuflib_reflection_getint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getint64(r, m, field));
    return 1;
}
static int protobuflib_reflection_getuint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getuint64(r, m, field));
    return 1;
}
static int protobuflib_reflection_getdouble(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushnumber(L, protobuf_reflection_getdouble(r, m, field));
    return 1;
}
static int protobuflib_reflection_getfloat(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushnumber(L, protobuf_reflection_getfloat(r, m, field));
    return 1;
}
static int protobuflib_reflection_getenumvalue(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getenumvalue(r, m, field));
    return 1;
}
static int protobuflib_reflection_getstring(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushstring(L, protobuf_reflection_getstring(r, m, field));
    return 1;
}
static int protobuflib_reflection_setbool(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    luaL_argcheck(L, lua_isboolean(L, 4), 4, "not a boolean value");
    int value = (int)lua_toboolean(L, 4);
    protobuf_reflection_setbool(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int value = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_setint32(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setuint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    unsigned int value = (unsigned int)luaL_checkinteger(L, 4);
    protobuf_reflection_setuint32(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    long long value = (long long)luaL_checkinteger(L, 4);
    protobuf_reflection_setint64(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setuint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    unsigned long long value = (unsigned long long)luaL_checkinteger(L, 4);
    protobuf_reflection_setuint64(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setdouble(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    double value = (double)luaL_checknumber(L, 4);
    protobuf_reflection_setdouble(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setfloat(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    float value = (float)luaL_checknumber(L, 4);
    protobuf_reflection_setfloat(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setenumvalue(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int value = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_setenumvalue(r, m, field, value);
    return 0;
}
static int protobuflib_reflection_setstring(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    const char* value = luaL_checkstring(L, 4);
    protobuf_reflection_setstring(r, m, field, value);
    return 0;
}

// repeated count
static int protobuflib_reflection_getrepeatedmessagecount(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeatedmessagecount(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeatedboolcount(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeatedboolcount(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeatedint32count(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeatedint32count(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeateduint32count(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeateduint32count(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeatedint64count(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeatedint64count(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeateduint64count(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeateduint64count(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeateddoublecount(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeateddoublecount(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeatedfloatcount(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeatedfloatcount(r, m, field));
    return 1;
}
static int protobuflib_reflection_getrepeatedstringcount(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    lua_pushinteger(L, protobuf_reflection_getrepeatedstringcount(r, m, field));
    return 1;
}

// repeated get
static int protobuflib_reflection_getrepeatedmessage(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushlightuserdata(L, protobuf_reflection_getrepeatedmessage(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeatedbool(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushboolean(L, protobuf_reflection_getrepeatedbool(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeatedint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushinteger(L, protobuf_reflection_getrepeatedint32(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeateduint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushinteger(L, protobuf_reflection_getrepeateduint32(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeatedint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushinteger(L, protobuf_reflection_getrepeatedint64(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeateduint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushinteger(L, protobuf_reflection_getrepeateduint64(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeateddouble(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushnumber(L, protobuf_reflection_getrepeateddouble(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeatedfloat(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushnumber(L, protobuf_reflection_getrepeatedfloat(r, m, field, index));
    return 1;
}
static int protobuflib_reflection_getrepeatedstring(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushstring(L, protobuf_reflection_getrepeatedstring(r, m, field, index));
    return 1;
}

static int protobuflib_reflection_setrepeatedbool(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    luaL_argcheck(L, lua_isboolean(L, 5), 5, "not a boolean value");
    int value = (int)lua_toboolean(L, 5);
    protobuf_reflection_setrepeatedbool(r, m, field, index, value);
    return 0;
}
static int protobuflib_reflection_setrepeatedint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    int value = (int)luaL_checkinteger(L, 5);
    protobuf_reflection_setrepeatedint32(r, m, field, index, value);
    return 0;
}
static int protobuflib_reflection_setrepeateduint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    unsigned int value = (unsigned int)luaL_checkinteger(L, 5);
    protobuf_reflection_setrepeateduint32(r, m, field, index, value);
    return 0;
}
static int protobuflib_reflection_setrepeatedint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    long long value = (long long)luaL_checkinteger(L, 5);
    protobuf_reflection_setrepeatedint64(r, m, field, index, value);
    return 0;
}
static int protobuflib_reflection_setrepeateduint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    unsigned long long value = (unsigned long long)luaL_checkinteger(L, 5);
    protobuf_reflection_setrepeateduint64(r, m, field, index, value);
    return 0;
}
static int protobuflib_reflection_setrepeateddouble(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    double value = (double)luaL_checknumber(L, 5);
    protobuf_reflection_setrepeateddouble(r, m, field, index, value);
    return 0;
}
static int protobuflib_reflection_setrepeatedfloat(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    float value = (float)luaL_checknumber(L, 5);
    protobuf_reflection_setrepeatedfloat(r, m, field, index, value);
    return 0;
}
static int protobuflib_reflection_setrepeatedstring(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    const char* value = luaL_checkstring(L, 5);
    protobuf_reflection_setrepeatedstring(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_clearfield(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    protobuf_reflection_clearfield(r, m, field);
    return 0;
}

static int protobuflib_reflection_insertrepeatedmessage(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    lua_pushlightuserdata(L, protobuf_reflection_insertrepeatedmessage(r, m, field, index));
    return 1;
}

static int protobuflib_reflection_insertrepeatedbool(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    luaL_argcheck(L, lua_isboolean(L, 5), 5, "not a boolean value");
    int value = (int)lua_toboolean(L, 5);
    protobuf_reflection_insertrepeatedbool(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_insertrepeatedint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    int value = (int)luaL_checkinteger(L, 5);
    protobuf_reflection_insertrepeatedint32(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_insertrepeateduint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    unsigned int value = (unsigned int)luaL_checkinteger(L, 5);
    protobuf_reflection_insertrepeateduint32(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_insertrepeatedint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    long long value = (long long)luaL_checkinteger(L, 5);
    protobuf_reflection_insertrepeatedint64(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_insertrepeateduint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    unsigned long long value = (unsigned long long)luaL_checkinteger(L, 5);
    protobuf_reflection_insertrepeateduint64(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_insertrepeateddouble(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    double value = (double)luaL_checknumber(L, 5);
    protobuf_reflection_insertrepeateddouble(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_insertrepeatedfloat(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    float value = (float)luaL_checknumber(L, 5);
    protobuf_reflection_insertrepeatedfloat(r, m, field, index, value);
    return 0;
}

static int protobuflib_reflection_insertrepeatedstring(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    const char* value = luaL_checkstring(L, 5);
    protobuf_reflection_insertrepeatedstring(r, m, field, index, value);
    return 0;
}


static int protobuflib_reflection_removerepeatedmessage(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeatedmessage(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeatedbool(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeatedbool(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeatedint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeatedint32(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeateduint32(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    unsigned int value = (unsigned int)luaL_checkinteger(L, 4);
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeateduint32(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeatedint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeatedint64(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeateduint64(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeateduint64(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeateddouble(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeateddouble(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeatedfloat(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeatedfloat(r, m, field, index);
    return 0;
}

static int protobuflib_reflection_removerepeatedstring(lua_State* L)
{
    void* r = lua_touserdata(L, 1);
    luaL_argcheck(L, r != 0, 1, "reflection object is null");
    void* m = lua_touserdata(L, 2);
    luaL_argcheck(L, m != 0, 2, "message object is null");
    void* field = lua_touserdata(L, 3);
    luaL_argcheck(L, field != 0, 3, "field descriptor object is null");
    int index = (int)luaL_checkinteger(L, 4);
    protobuf_reflection_removerepeatedstring(r, m, field, index);
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
    lua_pushliteral(L, "protobuf for Lua");
    lua_settable(L, -3);
    lua_pushliteral(L, "_VERSION");
    lua_pushliteral(L, "protobuf 1.0");
    lua_settable(L, -3);
}

static struct luaL_Reg protobuflib[] = {
    {"shutdown", protobuflib_shutdown},

    {"createimporter", protobuflib_createimporter},
    {"importer_import", protobuflib_importer_import},

    {"filedescriptor_messagetypecount", protobuflib_filedescriptor_messagetypecount},
    {"filedescriptor_messagetype", protobuflib_filedescriptor_messagetype},
    {"filedescriptor_enumtypecount", protobuflib_filedescriptor_enumtypecount},
    {"filedescriptor_enumtype", protobuflib_filedescriptor_enumtype},

    {"messagedescriptor_name", protobuflib_messagedescriptor_name},
    {"messagedescriptor_fullname", protobuflib_messagedescriptor_fullname},
    {"messagedescriptor_fieldcount", protobuflib_messagedescriptor_fieldcount},
    {"messagedescriptor_field", protobuflib_messagedescriptor_field},
    {"messagedescriptor_findfieldbyname", protobuflib_messagedescriptor_findfieldbyname},
    {"messagedescriptor_findfieldbynumber", protobuflib_messagedescriptor_findfieldbynumber},
    
    {"enumdescriptor_name", protobuflib_enumdescriptor_name},
    {"enumdescriptor_fullname", protobuflib_enumdescriptor_fullname},
    {"enumdescriptor_valuecount", protobuflib_enumdescriptor_valuecount},
    {"enumdescriptor_value", protobuflib_enumdescriptor_value},
    {"enumdescriptor_findvaluebyname", protobuflib_enumdescriptor_findvaluebyname},
    {"enumdescriptor_findvaluebynumber", protobuflib_enumdescriptor_findvaluebynumber},

    {"enumvaluedescriptor_name", protobuflib_enumvaluedescriptor_name},
    {"enumvaluedescriptor_number", protobuflib_enumvaluedescriptor_number},

    {"fielddescriptor_cpptype", protobuflib_fielddescriptor_cpptype},
    {"fielddescriptor_name", protobuflib_fielddescriptor_name},
    {"fielddescriptor_cpptypename", protobuflib_fielddescriptor_cpptypename},
    {"fielddescriptor_ismap", protobuflib_fielddescriptor_ismap},
    {"fielddescriptor_isrepeated", protobuflib_fielddescriptor_isrepeated},
    {"fielddescriptor_messagetype", protobuflib_fielddescriptor_messagetype},
    {"fielddescriptor_enumtype", protobuflib_fielddescriptor_enumtype},

    {"createfactory", protobuflib_createfactory},
    {"createmessage", protobuflib_factory_createmessage},
    {"freemessage", protobuflib_freemessage},
    {"clonemessage", protobuflib_clonemessage},

    {"message_getdescriptor", protobuflib_message_getdescriptor},
    {"message_getreflection", protobuflib_message_getreflection},
    {"message_getbytesize", protobuflib_message_getbytesize},
    {"message_serializetoarray", protobuflib_message_serializetoarray},
    {"message_parsefromarray", protobuflib_message_parsefromarray},
    {"message_jsonencode", protobuflib_message_jsonencode},
    {"message_jsondecode", protobuflib_message_jsondecode},

    {"reflection_getmessage", protobuflib_reflection_getmessage},
    {"reflection_getbool", protobuflib_reflection_getbool},
    {"reflection_getint32", protobuflib_reflection_getint32},
    {"reflection_getuint32", protobuflib_reflection_getuint32},
    {"reflection_getint64", protobuflib_reflection_getint64},
    {"reflection_getuint64", protobuflib_reflection_getuint64},
    {"reflection_getdouble", protobuflib_reflection_getdouble},
    {"reflection_getfloat", protobuflib_reflection_getfloat},
    {"reflection_getenumvalue", protobuflib_reflection_getenumvalue},
    {"reflection_getstring", protobuflib_reflection_getstring},

    {"reflection_setbool", protobuflib_reflection_setbool},
    {"reflection_setint32", protobuflib_reflection_setint32},
    {"reflection_setuint32", protobuflib_reflection_setuint32},
    {"reflection_setint64", protobuflib_reflection_setint64},
    {"reflection_setuint64", protobuflib_reflection_setuint64},
    {"reflection_setdouble", protobuflib_reflection_setdouble},
    {"reflection_setfloat", protobuflib_reflection_setfloat},
    {"reflection_setenumvalue", protobuflib_reflection_setenumvalue},
    {"reflection_setstring", protobuflib_reflection_setstring},

    {"reflection_getrepeatedmessagecount", protobuflib_reflection_getrepeatedmessagecount},
    {"reflection_getrepeatedboolcount", protobuflib_reflection_getrepeatedboolcount},
    {"reflection_getrepeatedint32count", protobuflib_reflection_getrepeatedint32count},
    {"reflection_getrepeateduint32count", protobuflib_reflection_getrepeateduint32count},
    {"reflection_getrepeatedint64count", protobuflib_reflection_getrepeatedint64count},
    {"reflection_getrepeateduint64count", protobuflib_reflection_getrepeateduint64count},
    {"reflection_getrepeateddoublecount", protobuflib_reflection_getrepeateddoublecount},
    {"reflection_getrepeatedfloatcount", protobuflib_reflection_getrepeatedfloatcount},
    {"reflection_getrepeatedstringcount", protobuflib_reflection_getrepeatedstringcount},

    {"reflection_getrepeatedmessage", protobuflib_reflection_getrepeatedmessage},
    {"reflection_getrepeatedbool", protobuflib_reflection_getrepeatedbool},
    {"reflection_getrepeatedint32", protobuflib_reflection_getrepeatedint32},
    {"reflection_getrepeateduint32", protobuflib_reflection_getrepeateduint32},
    {"reflection_getrepeatedint64", protobuflib_reflection_getrepeatedint64},
    {"reflection_getrepeateduint64", protobuflib_reflection_getrepeateduint64},
    {"reflection_getrepeateddouble", protobuflib_reflection_getrepeateddouble},
    {"reflection_getrepeatedfloat", protobuflib_reflection_getrepeatedfloat},
    {"reflection_getrepeatedstring", protobuflib_reflection_getrepeatedstring},

    {"reflection_setrepeatedbool", protobuflib_reflection_setrepeatedbool},
    {"reflection_setrepeatedint32", protobuflib_reflection_setrepeatedint32},
    {"reflection_setrepeateduint32", protobuflib_reflection_setrepeateduint32},
    {"reflection_setrepeatedint64", protobuflib_reflection_setrepeatedint64},
    {"reflection_setrepeateduint64", protobuflib_reflection_setrepeateduint64},
    {"reflection_setrepeateddouble", protobuflib_reflection_setrepeateddouble},
    {"reflection_setrepeatedfloat", protobuflib_reflection_setrepeatedfloat},
    {"reflection_setrepeatedstring", protobuflib_reflection_setrepeatedstring},

    {"reflection_clearfield", protobuflib_reflection_clearfield},

    {"reflection_insertrepeatedmessage", protobuflib_reflection_insertrepeatedmessage},
    {"reflection_insertrepeatedbool", protobuflib_reflection_insertrepeatedbool},
    {"reflection_insertrepeatedint32", protobuflib_reflection_insertrepeatedint32},
    {"reflection_insertrepeateduint32", protobuflib_reflection_insertrepeateduint32},
    {"reflection_insertrepeatedint64", protobuflib_reflection_insertrepeatedint64},
    {"reflection_insertrepeateduint64", protobuflib_reflection_insertrepeateduint64},
    {"reflection_insertrepeateddouble", protobuflib_reflection_insertrepeateddouble},
    {"reflection_insertrepeatedfloat", protobuflib_reflection_insertrepeatedfloat},
    {"reflection_insertrepeatedstring", protobuflib_reflection_insertrepeatedstring},

    {"reflection_removerepeatedmessage", protobuflib_reflection_removerepeatedmessage},
    {"reflection_removerepeatedbool", protobuflib_reflection_removerepeatedbool},
    {"reflection_removerepeatedint32", protobuflib_reflection_removerepeatedint32},
    {"reflection_removerepeateduint32", protobuflib_reflection_removerepeateduint32},
    {"reflection_removerepeatedint64", protobuflib_reflection_removerepeatedint64},
    {"reflection_removerepeateduint64", protobuflib_reflection_removerepeateduint64},
    {"reflection_removerepeateddouble", protobuflib_reflection_removerepeateddouble},
    {"reflection_removerepeatedfloat", protobuflib_reflection_removerepeatedfloat},
    {"reflection_removerepeatedstring", protobuflib_reflection_removerepeatedstring},

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
