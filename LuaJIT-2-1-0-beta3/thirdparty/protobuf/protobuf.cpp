
extern "C" {
    #include "protobuf.h"
}

#include "google/protobuf/compiler/importer.h"
#include "google/protobuf/dynamic_message.h"

void* protobuf_createimporter(const char* path)
{
    google::protobuf::compiler::DiskSourceTree sourceTree;
    sourceTree.MapPath("", path);
    return new google::protobuf::compiler::Importer(&sourceTree, nullptr);
}

void protobuf_freeimporter(void* c)
{
    delete ((google::protobuf::compiler::Importer*)c);
}

void* protobuf_importerimport(void* c, const char* path)
{
    return (void*)((google::protobuf::compiler::Importer*)c)->Import(path);
}

int protobuf_getfiledescriptmessagetypecount(void* descriptor)
{
    return ((const google::protobuf::FileDescriptor*)descriptor)->message_type_count();
}
void* protobuf_getfiledescriptmessagetype(void* descriptor, int index)
{
    return (void*)((const google::protobuf::FileDescriptor*)descriptor)->message_type(index);
}
const char* protobuf_getmessagename(void* descriptor)
{
    return ((const google::protobuf::Descriptor*)descriptor)->name().c_str();
}
const char* protobuf_getmessagefullname(void* descriptor)
{
    return ((const google::protobuf::Descriptor*)descriptor)->full_name().c_str();
}
int protobuf_getmessagefieldcount(void* descriptor)
{
    return ((const google::protobuf::Descriptor*)descriptor)->field_count();
}
void* protobuf_getmessagefield(void* descriptor, int index)
{
    return (void*)((const google::protobuf::Descriptor*)descriptor)->field(index);
}
void* protobuf_findmessagefieldbyname(void* descriptor, const char* name)
{
    return (void*)((const google::protobuf::Descriptor*)descriptor)->FindFieldByName(name);
}

void* protobuf_createfactory()
{
    return new google::protobuf::DynamicMessageFactory();
}

void protobuf_freefactory(void* c)
{
    delete ((google::protobuf::DynamicMessageFactory*)c);
}

void* protobuf_factorycreatemessage(void* c, void* descriptor)
{
    return ((google::protobuf::DynamicMessageFactory*)c)->GetPrototype((const google::protobuf::Descriptor*)descriptor)->New();
}
