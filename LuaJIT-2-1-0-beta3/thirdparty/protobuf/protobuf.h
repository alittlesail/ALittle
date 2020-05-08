
#ifndef _ALITTLE_PROTOBUF_H_
#define _ALITTLE_PROTOBUF_H_

#include "lua.h"

// importer
void* protobuf_createimporter(const char* path);
void protobuf_freeimporter(void* c);
void* protobuf_importer_import(void* c, const char* path);

// file descriptor
int protobuf_filedescriptor_messagetypecount(void* descriptor);
void* protobuf_filedescriptor_messagetype(void* descriptor, int index);
int protobuf_filedescriptor_enumtypecount(void* descriptor);
void* protobuf_filedescriptor_enumtype(void* descriptor, int index);

// message descriptor
const char* protobuf_messagedescriptor_name(void* descriptor);
const char* protobuf_messagedescriptor_fullname(void* descriptor);
int protobuf_messagedescriptor_fieldcount(void* descriptor);
void* protobuf_messagedescriptor_field(void* descriptor, int index);
void* protobuf_messagedescriptor_findfieldbyname(void* descriptor, const char* name);
void* protobuf_messagedescriptor_findfieldbynumber(void* descriptor, int number);

// enum descriptor
const char* protobuf_enumdescriptor_name(void* descriptor);
const char* protobuf_enumdescriptor_fullname(void* descriptor);
int protobuf_enumdescriptor_valuecount(void* descriptor);
void* protobuf_enumdescriptor_value(void* descriptor, int index);
void* protobuf_enumdescriptor_findvaluebyname(void* descriptor, const char* name);
void* protobuf_enumdescriptor_findvaluebynumber(void* descriptor, int number);

// enum value descriptor
const char* protobuf_enumvaluedescriptor_name(void* descriptor);
int protobuf_enumvaluedescriptor_number(void* descriptor);

// field descriptor
int protobuf_fielddescriptor_cpptype(void* descriptor);
const char* protobuf_fielddescriptor_name(void* descriptor);
const char* protobuf_fielddescriptor_cpptypename(void* descriptor);
int protobuf_fielddescriptor_ismap(void* descriptor);
int protobuf_fielddescriptor_isrepeated(void* descriptor);
void* protobuf_fielddescriptor_messagetype(void* descriptor);

// factory
void* protobuf_createfactory();
void protobuf_freefactory(void* c);
void* protobuf_factory_createmessage(void* c, void* message_descriptor);

// message
void protobuf_freemessage(void* m);
void* protobuf_message_getdescriptor(void* m);
void* protobuf_message_getreflection(void* m);
int protobuf_message_getbytesize(void* m);
int protobuf_message_serializetoarray(void* m, void* buffer, int size);
int protobuf_message_parsefromarray(void* m, void* buffer, int size);

// reflection
void* protobuf_reflection_getmessage(void* r, void* m, void* field);
int protobuf_reflection_getbool(void* r, void* m, void* field);
int protobuf_reflection_getint32(void* r, void* m, void* field);
unsigned int protobuf_reflection_getuint32(void* r, void* m, void* field);
long long protobuf_reflection_getint64(void* r, void* m, void* field);
unsigned long long protobuf_reflection_getuint64(void* r, void* m, void* field);
double protobuf_reflection_getdouble(void* r, void* m, void* field);
float protobuf_reflection_getfloat(void* r, void* m, void* field);
int protobuf_reflection_getenumvalue(void* r, void* m, void* field);
const char* protobuf_reflection_getstring(void* r, void* m, void* field);

void protobuf_reflection_setbool(void* r, void* m, void* field, int value);
void protobuf_reflection_setint32(void* r, void* m, void* field, int value);
void protobuf_reflection_setuint32(void* r, void* m, void* field, unsigned int value);
void protobuf_reflection_setint64(void* r, void* m, void* field, long long value);
void protobuf_reflection_setuint64(void* r, void* m, void* field, unsigned long long value);
void protobuf_reflection_setdouble(void* r, void* m, void* field, double value);
void protobuf_reflection_setfloat(void* r, void* m, void* field, float value);
void protobuf_reflection_setenumvalue(void* r, void* m, void* field, int value);
void protobuf_reflection_setstring(void* r, void* m, void* field, const char* value);

void** protobuf_reflection_getrepeatedmessage(void* r, void* m, void* field, int* size);
int* protobuf_reflection_getrepeatedbool(void* r, void* m, void* field, int* size);
int* protobuf_reflection_getrepeatedint32(void* r, void* m, void* field, int* size);
unsigned int* protobuf_reflection_getrepeateduint32(void* r, void* m, void* field, int* size);
long long* protobuf_reflection_getrepeatedint64(void* r, void* m, void* field, int* size);
unsigned long long* protobuf_reflection_getrepeateduint64(void* r, void* m, void* field, int* size);
double* protobuf_reflection_getrepeateddouble(void* r, void* m, void* field, int* size);
float* protobuf_reflection_getrepeatedfloat(void* r, void* m, void* field, int* size);
const char** protobuf_reflection_getrepeatedstring(void* r, void* m, void* field, int* size);

void protobuf_reflection_clearfield(void* r, void* m, void* field);
void protobuf_reflection_addrepeatedmessage(void* r, void* m, void* field, void* value);
void protobuf_reflection_addrepeatedbool(void* r, void* m, void* field, int value);
void protobuf_reflection_addrepeatedint32(void* r, void* m, void* field, int value);
void protobuf_reflection_addrepeateduint32(void* r, void* m, void* field, unsigned int value);
void protobuf_reflection_addrepeatedint64(void* r, void* m, void* field, long long value);
void protobuf_reflection_addrepeateduint64(void* r, void* m, void* field, unsigned long long value);
void protobuf_reflection_addrepeateddouble(void* r, void* m, void* field, double value);
void protobuf_reflection_addrepeatedfloat(void* r, void* m, void* field, float value);
void protobuf_reflection_addrepeatedstring(void* r, void* m, void* field, const char* value);

#endif // _ALITTLE_PROTOBUF_H_
