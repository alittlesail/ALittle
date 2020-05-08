
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

void* protobuf_importer_import(void* c, const char* path)
{
    return (void*)((google::protobuf::compiler::Importer*)c)->Import(path);
}

int protobuf_filedescriptor_messagetypecount(void* descriptor)
{
    return ((const google::protobuf::FileDescriptor*)descriptor)->message_type_count();
}
void* protobuf_filedescriptor_messagetype(void* descriptor, int index)
{
    return (void*)((const google::protobuf::FileDescriptor*)descriptor)->message_type(index);
}
int protobuf_filedescriptor_enumtypecount(void* descriptor)
{
    return ((const google::protobuf::FileDescriptor*)descriptor)->enum_type_count();
}
void* protobuf_filedescriptor_enumtype(void* descriptor, int index)
{
    return (void*)((const google::protobuf::FileDescriptor*)descriptor)->enum_type(index);
}
const char* protobuf_messagedescriptor_name(void* descriptor)
{
    return ((const google::protobuf::Descriptor*)descriptor)->name().c_str();
}
const char* protobuf_messagedescriptor_fullname(void* descriptor)
{
    return ((const google::protobuf::Descriptor*)descriptor)->full_name().c_str();
}
int protobuf_messagedescriptor_fieldcount(void* descriptor)
{
    return ((const google::protobuf::Descriptor*)descriptor)->field_count();
}
void* protobuf_messagedescriptor_field(void* descriptor, int index)
{
    return (void*)((const google::protobuf::Descriptor*)descriptor)->field(index);
}
void* protobuf_messagedescriptor_findfieldbyname(void* descriptor, const char* name)
{
    return (void*)((const google::protobuf::Descriptor*)descriptor)->FindFieldByName(name);
}
void* protobuf_messagedescriptor_findfieldbynumber(void* descriptor, int number)
{
    return (void*)((const google::protobuf::Descriptor*)descriptor)->FindFieldByNumber(number);
}
const char* protobuf_enumdescriptor_name(void* descriptor)
{
    return ((const google::protobuf::EnumDescriptor*)descriptor)->name().c_str();
}
const char* protobuf_enumdescriptor_fullname(void* descriptor)
{
    return ((const google::protobuf::EnumDescriptor*)descriptor)->full_name().c_str();
}
int protobuf_enumdescriptor_valuecount(void* descriptor)
{
    return ((const google::protobuf::EnumDescriptor*)descriptor)->value_count();
}
void* protobuf_enumdescriptor_value(void* descriptor, int index)
{
    return (void*)((const google::protobuf::EnumDescriptor*)descriptor)->value(index);
}
void* protobuf_enumdescriptor_findvaluebyname(void* descriptor, const char* name)
{
    return (void*)((const google::protobuf::EnumDescriptor*)descriptor)->FindValueByName(name);
}
void* protobuf_enumdescriptor_findvaluebynumber(void* descriptor, int number)
{
    return (void*)((const google::protobuf::EnumDescriptor*)descriptor)->FindValueByNumber(number);
}
const char* protobuf_enumvaluedescriptor_name(void* descriptor)
{
    return ((const google::protobuf::EnumValueDescriptor*)descriptor)->name().c_str();
}
int protobuf_enumvaluedescriptor_number(void* descriptor)
{
    return ((const google::protobuf::EnumValueDescriptor*)descriptor)->number();
}
int protobuf_fielddescriptor_cpptype(void* descriptor)
{
    return ((const google::protobuf::FieldDescriptor*)descriptor)->cpp_type();
}

const char* protobuf_fielddescriptor_name(void* descriptor)
{
    return ((const google::protobuf::FieldDescriptor*)descriptor)->name().c_str();
}

const char* protobuf_fielddescriptor_cpptypename(void* descriptor)
{
    return ((const google::protobuf::FieldDescriptor*)descriptor)->cpp_type_name();
}

int protobuf_fielddescriptor_ismap(void* descriptor)
{
    return ((const google::protobuf::FieldDescriptor*)descriptor)->is_map() ? 1 : 0;
}

int protobuf_fielddescriptor_isrepeated(void* descriptor)
{
    return ((const google::protobuf::FieldDescriptor*)descriptor)->is_repeated() ? 1 : 0;
}

void* protobuf_fielddescriptor_messagetype(void* descriptor)
{
    return (void*)((const google::protobuf::FieldDescriptor*)descriptor)->message_type();
}

void* protobuf_createfactory()
{
    return new google::protobuf::DynamicMessageFactory();
}

void protobuf_freefactory(void* c)
{
    delete ((google::protobuf::DynamicMessageFactory*)c);
}

void* protobuf_factory_createmessage(void* c, void* descriptor)
{
    return ((google::protobuf::DynamicMessageFactory*)c)->GetPrototype((const google::protobuf::Descriptor*)descriptor)->New();
}

void protobuf_freemessage(void* m)
{
    delete ((google::protobuf::Message*)m);
}

void* protobuf_message_getdescriptor(void* m)
{
    return (void*)((google::protobuf::Message*)m)->GetDescriptor();
}

void* protobuf_message_getreflection(void* m)
{
    return (void*)((google::protobuf::Message*)m)->GetReflection();
}

int protobuf_message_getbytesize(void* m)
{
    return (int)((google::protobuf::Message*)m)->ByteSizeLong();
}

int protobuf_message_serializetoarray(void* m, void* buffer, int size)
{
    return ((google::protobuf::Message*)m)->SerializeToArray(buffer, size) ? 1 : 0;
}

int protobuf_message_parsefromarray(void* m, void* buffer, int size)
{
    return ((google::protobuf::Message*)m)->ParseFromArray(buffer, size) ? 1 : 0;
}

int protobuf_reflection_getbool(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetBool(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field) ? 1 : 0;
}

int protobuf_reflection_getint32(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetInt32(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

unsigned int protobuf_reflection_getuint32(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetUInt32(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

long long protobuf_reflection_getint64(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetInt64(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

unsigned long long protobuf_reflection_getuint64(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetUInt64(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

double protobuf_reflection_getdouble(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetDouble(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

float protobuf_reflection_getfloat(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetFloat(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

int protobuf_reflection_getenumvalue(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->GetEnumValue(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

const char* protobuf_reflection_getstring(void* r, void* m, void* field)
{
    static std::string temp;
    temp = ((google::protobuf::Reflection*)r)->GetString(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    return temp.c_str();
}

void* protobuf_reflection_getmessage(void* r, void* m, void* field)
{
    return ((google::protobuf::Reflection*)r)->MutableMessage((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

void protobuf_reflection_setbool(void* r, void* m, void* field, int value)
{
    return ((google::protobuf::Reflection*)r)->SetBool((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value != 0);
}

void protobuf_reflection_setint32(void* r, void* m, void* field, int value)
{
    return ((google::protobuf::Reflection*)r)->SetInt32((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setuint32(void* r, void* m, void* field, unsigned int value)
{
    return ((google::protobuf::Reflection*)r)->SetUInt32((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setint64(void* r, void* m, void* field, long long value)
{
    return ((google::protobuf::Reflection*)r)->SetInt64((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setuint64(void* r, void* m, void* field, unsigned long long value)
{
    return ((google::protobuf::Reflection*)r)->SetUInt64((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setdouble(void* r, void* m, void* field, double value)
{
    return ((google::protobuf::Reflection*)r)->SetDouble((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setfloat(void* r, void* m, void* field, float value)
{
    return ((google::protobuf::Reflection*)r)->SetFloat((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setenumvalue(void* r, void* m, void* field, int value)
{
    return ((google::protobuf::Reflection*)r)->SetEnumValue((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setstring(void* r, void* m, void* field, const char* value)
{
    return ((google::protobuf::Reflection*)r)->SetString((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void** protobuf_reflection_getrepeatedmessage(void* r, void* m, void* field, int* size)
{
    static std::vector<const google::protobuf::Message*> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::Message>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(&(*it));
    if (size != nullptr) *size = (int)temp.size();
    return (void**)temp.data();
}

int* protobuf_reflection_getrepeatedbool(void* r, void* m, void* field, int* size)
{
    static std::vector<int> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<bool>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(*it ? 1 : 0);
    if (size != nullptr) *size = (int)temp.size();
    return temp.data();
}

int* protobuf_reflection_getrepeatedint32(void* r, void* m, void* field, int* size)
{
    static std::vector<int> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::int32>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(*it);
    if (size != nullptr) *size = (int)temp.size();
    return temp.data();
}

unsigned int* protobuf_reflection_getrepeateduint32(void* r, void* m, void* field, int* size)
{
    static std::vector<unsigned int> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::uint32>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(*it);
    if (size != nullptr) *size = (int)temp.size();
    return temp.data();
}

long long* protobuf_reflection_getrepeatedint64(void* r, void* m, void* field, int* size)
{
    static std::vector<long long> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::int64>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(*it);
    if (size != nullptr) *size = (int)temp.size();
    return temp.data();
}

unsigned long long* protobuf_reflection_getrepeateduint64(void* r, void* m, void* field, int* size)
{
    static std::vector<unsigned long long> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::uint64>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(*it);
    if (size != nullptr) *size = (int)temp.size();
    return temp.data();
}

double* protobuf_reflection_getrepeateddouble(void* r, void* m, void* field, int* size)
{
    static std::vector<double> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<double>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(*it);
    if (size != nullptr) *size = (int)temp.size();
    return temp.data();
}

float* protobuf_reflection_getrepeatedfloat(void* r, void* m, void* field, int* size)
{
    static std::vector<float> temp;
    temp.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<float>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
        temp.push_back(*it);
    if (size != nullptr) *size = (int)temp.size();
    return temp.data();
}

const char** protobuf_reflection_getrepeatedstring(void* r, void* m, void* field, int* size)
{
    static std::vector<std::string> temp1;
    static std::vector<const char*> temp2;
    temp1.clear();
    temp2.clear();
    auto repeated = ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<std::string>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    for (auto it = repeated.begin(); it != repeated.end(); ++it)
    {
        temp1.push_back(*it);
        temp2.push_back(temp1.back().c_str());
    }
    if (size != nullptr) *size = (int)temp2.size();
    return temp2.data();
}

void protobuf_reflection_clearfield(void* r, void* m, void* field)
{
    ((google::protobuf::Reflection*)r)->ClearField((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

void protobuf_reflection_addrepeatedmessage(void* r, void* m, void* field, void* value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::Message>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(*((const google::protobuf::Message*)value));
}

void protobuf_reflection_addrepeatedbool(void* r, void* m, void* field, int value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<bool>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value != 0);
}

void protobuf_reflection_addrepeatedint32(void* r, void* m, void* field, int value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::int32>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value);
}

void protobuf_reflection_addrepeateduint32(void* r, void* m, void* field, unsigned int value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::uint32>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value);
}

void protobuf_reflection_addrepeatedint64(void* r, void* m, void* field, long long value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::int64>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value);
}

void protobuf_reflection_addrepeateduint64(void* r, void* m, void* field, unsigned long long value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::uint64>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value);
}

void protobuf_reflection_addrepeateddouble(void* r, void* m, void* field, double value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<double>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value);
}

void protobuf_reflection_addrepeatedfloat(void* r, void* m, void* field, float value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<float>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value);
}

void protobuf_reflection_addrepeatedstring(void* r, void* m, void* field, const char* value)
{
    ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<std::string>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).Add(value);
}