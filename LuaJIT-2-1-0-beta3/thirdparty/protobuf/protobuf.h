
#ifndef _ALITTLE_PROTOBUF_H_
#define _ALITTLE_PROTOBUF_H_

#include "lua.h"

// importer
void* protobuf_createimporter(const char* path);
void protobuf_freeimporter(void* c);
void* protobuf_importerimport(void* c, const char* path);

// file descriptor
int protobuf_getfiledescriptmessagetypecount(void* descriptor);
void* protobuf_getfiledescriptmessagetype(void* descriptor, int index);

// message
const char* protobuf_getmessagename(void* descriptor);
const char* protobuf_getmessagefullname(void* descriptor);
int protobuf_getmessagefieldcount(void* descriptor);
void* protobuf_getmessagefield(void* descriptor, int index);
void* protobuf_findmessagefieldbyname(void* descriptor, const char* name);

// factory
void* protobuf_createfactory();
void protobuf_freefactory(void* c);
void* protobuf_factorycreatemessage(void* c, void* descriptor);



#endif // _ALITTLE_PROTOBUF_H_
