
#ifndef _ALITTLE_PROTOBUF_H_
#define _ALITTLE_PROTOBUF_H_

typedef struct _importer
{
	void* source_tree;
	void* error_collector;
	void* importer;
} importer;

void protobuf_shutdown();

// importer
void* protobuf_createimporter(const char* path);
void protobuf_freeimporter(void* c);
void* protobuf_importer_import(void* c, const char* path);
void* protobuf_importer_getpool(void* c);

// descripor pool
void* protobuf_descriptorpool_findmessagetypebyname(void* pool, const char* name);
void* protobuf_descriptorpool_findfieldbyname(void* pool, const char* name);
void* protobuf_descriptorpool_findoneofbyname(void* pool, const char* name);
void* protobuf_descriptorpool_findenumtypebyname(void* pool, const char* name);
void* protobuf_descriptorpool_findenumvaluebyname(void* pool, const char* name);

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
void* protobuf_fielddescriptor_enumtype(void* descriptor);

// factory
void* protobuf_createfactory();
void protobuf_freefactory(void* c);
void* protobuf_factory_createmessage(void* c, void* message_descriptor);

// message
void protobuf_freemessage(void* m);
void* protobuf_clonemessage(void* m);
void* protobuf_message_getdescriptor(void* m);
void* protobuf_message_getreflection(void* m);
int protobuf_message_getbytesize(void* m);
int protobuf_message_serializetoarray(void* m, void* buffer, int size);
int protobuf_message_parsefromarray(void* m, void* buffer, int size);
const char* protobuf_message_jsonencode(void* m);
const char* protobuf_message_jsondecode(void* m, const char* json);

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

void protobuf_reflection_clearfield(void* r, void* m, void* field);

int protobuf_reflection_getrepeatedmessagecount(void* r, void* m, void* field);
int protobuf_reflection_getrepeatedboolcount(void* r, void* m, void* field);
int protobuf_reflection_getrepeatedint32count(void* r, void* m, void* field);
int protobuf_reflection_getrepeateduint32count(void* r, void* m, void* field);
int protobuf_reflection_getrepeatedint64count(void* r, void* m, void* field);
int protobuf_reflection_getrepeateduint64count(void* r, void* m, void* field);
int protobuf_reflection_getrepeateddoublecount(void* r, void* m, void* field);
int protobuf_reflection_getrepeatedfloatcount(void* r, void* m, void* field);
int protobuf_reflection_getrepeatedstringcount(void* r, void* m, void* field);

void* protobuf_reflection_getrepeatedmessage(void* r, void* m, void* field, int index);
int protobuf_reflection_getrepeatedbool(void* r, void* m, void* field, int index);
int protobuf_reflection_getrepeatedint32(void* r, void* m, void* field, int index);
unsigned int protobuf_reflection_getrepeateduint32(void* r, void* m, void* field, int index);
long long protobuf_reflection_getrepeatedint64(void* r, void* m, void* field, int index);
unsigned long long protobuf_reflection_getrepeateduint64(void* r, void* m, void* field, int index);
double protobuf_reflection_getrepeateddouble(void* r, void* m, void* field, int index);
float protobuf_reflection_getrepeatedfloat(void* r, void* m, void* field, int index);
const char* protobuf_reflection_getrepeatedstring(void* r, void* m, void* field, int index);

void protobuf_reflection_setrepeatedbool(void* r, void* m, void* field, int index, int value);
void protobuf_reflection_setrepeatedint32(void* r, void* m, void* field, int index, int value);
void protobuf_reflection_setrepeateduint32(void* r, void* m, void* field, int index, unsigned int value);
void protobuf_reflection_setrepeatedint64(void* r, void* m, void* field, int index, long long value);
void protobuf_reflection_setrepeateduint64(void* r, void* m, void* field, int index, unsigned long long value);
void protobuf_reflection_setrepeateddouble(void* r, void* m, void* field, int index, double value);
void protobuf_reflection_setrepeatedfloat(void* r, void* m, void* field, int index, float value);
void protobuf_reflection_setrepeatedstring(void* r, void* m, void* field, int index, const char* value);

void* protobuf_reflection_insertrepeatedmessage(void* r, void* m, void* field, int index);
void protobuf_reflection_insertrepeatedbool(void* r, void* m, void* field, int index, int value);
void protobuf_reflection_insertrepeatedint32(void* r, void* m, void* field, int index, int value);
void protobuf_reflection_insertrepeateduint32(void* r, void* m, void* field, int index, unsigned int value);
void protobuf_reflection_insertrepeatedint64(void* r, void* m, void* field, int index, long long value);
void protobuf_reflection_insertrepeateduint64(void* r, void* m, void* field, int index, unsigned long long value);
void protobuf_reflection_insertrepeateddouble(void* r, void* m, void* field, int index, double value);
void protobuf_reflection_insertrepeatedfloat(void* r, void* m, void* field, int index, float value);
void protobuf_reflection_insertrepeatedstring(void* r, void* m, void* field, int index, const char* value);

void protobuf_reflection_removerepeatedmessage(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeatedbool(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeatedint32(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeateduint32(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeatedint64(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeateduint64(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeateddouble(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeatedfloat(void* r, void* m, void* field, int index);
void protobuf_reflection_removerepeatedstring(void* r, void* m, void* field, int index);

#endif // _ALITTLE_PROTOBUF_H_
