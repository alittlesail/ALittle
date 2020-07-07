
extern "C" {
    #include "protobuf.h"
}

#include "google/protobuf/compiler/importer.h"
#include "google/protobuf/dynamic_message.h"
#include "google/protobuf/reflection.h"
#include "google/protobuf/util/json_util.h"

class MultiFileErrorCollector : public google::protobuf::compiler::MultiFileErrorCollector
{
public:
    void AddError(const std::string& filename, int line, int column,
                  const std::string& message) {
    }
};

void protobuf_shutdown() {
    google::protobuf::ShutdownProtobufLibrary();
}

void* protobuf_createimporter(const char* path) {
    importer* m = (importer*)malloc(sizeof(importer));
    auto source_tree = new google::protobuf::compiler::DiskSourceTree();
    auto error_collector = new MultiFileErrorCollector();
    m->source_tree = source_tree;
    m->error_collector = error_collector;
    source_tree->MapPath("", path);
    m->importer = new google::protobuf::compiler::Importer(source_tree, error_collector);
    return m;
}

void protobuf_freeimporter(void* c) {
    importer* m = (importer*)c;
    delete ((MultiFileErrorCollector*)m->error_collector);
    delete ((google::protobuf::compiler::DiskSourceTree*)m->source_tree);
    delete ((google::protobuf::compiler::Importer*)m->importer);
    free(m);
}

void* protobuf_importer_import(void* c, const char* path) {
    importer* m = (importer*)c;
    return (void*)((google::protobuf::compiler::Importer*)m->importer)->Import(path);
}

void* protobuf_importer_getpool(void* c) {
    importer* m = (importer*)c;
    return (void*)((google::protobuf::compiler::Importer*)m->importer)->pool();
}

void* protobuf_descriptorpool_findmessagetypebyname(void* pool, const char* name) {
    return (void*)((google::protobuf::DescriptorPool*)(pool))->FindMessageTypeByName(name);
}

void* protobuf_descriptorpool_findfieldbyname(void* pool, const char* name) {
    return (void*)((google::protobuf::DescriptorPool*)(pool))->FindFieldByName(name);
}

void* protobuf_descriptorpool_findoneofbyname(void* pool, const char* name) {
    return (void*)((google::protobuf::DescriptorPool*)(pool))->FindOneofByName(name);
}

void* protobuf_descriptorpool_findenumtypebyname(void* pool, const char* name) {
    return (void*)((google::protobuf::DescriptorPool*)(pool))->FindEnumTypeByName(name);
}

void* protobuf_descriptorpool_findenumvaluebyname(void* pool, const char* name) {
    return (void*)((google::protobuf::DescriptorPool*)(pool))->FindEnumValueByName(name);
}

int protobuf_filedescriptor_messagetypecount(void* descriptor) {
    return ((const google::protobuf::FileDescriptor*)descriptor)->message_type_count();
}
void* protobuf_filedescriptor_messagetype(void* descriptor, int index) {
    return (void*)((const google::protobuf::FileDescriptor*)descriptor)->message_type(index);
}
int protobuf_filedescriptor_enumtypecount(void* descriptor) {
    return ((const google::protobuf::FileDescriptor*)descriptor)->enum_type_count();
}
void* protobuf_filedescriptor_enumtype(void* descriptor, int index) {
    return (void*)((const google::protobuf::FileDescriptor*)descriptor)->enum_type(index);
}
const char* protobuf_messagedescriptor_name(void* descriptor) {
    return ((const google::protobuf::Descriptor*)descriptor)->name().c_str();
}
const char* protobuf_messagedescriptor_fullname(void* descriptor) {
    return ((const google::protobuf::Descriptor*)descriptor)->full_name().c_str();
}
int protobuf_messagedescriptor_fieldcount(void* descriptor) {
    return ((const google::protobuf::Descriptor*)descriptor)->field_count();
}
void* protobuf_messagedescriptor_field(void* descriptor, int index) {
    return (void*)((const google::protobuf::Descriptor*)descriptor)->field(index);
}
void* protobuf_messagedescriptor_findfieldbyname(void* descriptor, const char* name) {
    return (void*)((const google::protobuf::Descriptor*)descriptor)->FindFieldByName(name);
}
void* protobuf_messagedescriptor_findfieldbynumber(void* descriptor, int number) {
    return (void*)((const google::protobuf::Descriptor*)descriptor)->FindFieldByNumber(number);
}
const char* protobuf_enumdescriptor_name(void* descriptor) {
    return ((const google::protobuf::EnumDescriptor*)descriptor)->name().c_str();
}
const char* protobuf_enumdescriptor_fullname(void* descriptor) {
    return ((const google::protobuf::EnumDescriptor*)descriptor)->full_name().c_str();
}
int protobuf_enumdescriptor_valuecount(void* descriptor) {
    return ((const google::protobuf::EnumDescriptor*)descriptor)->value_count();
}
void* protobuf_enumdescriptor_value(void* descriptor, int index) {
    return (void*)((const google::protobuf::EnumDescriptor*)descriptor)->value(index);
}
void* protobuf_enumdescriptor_findvaluebyname(void* descriptor, const char* name) {
    return (void*)((const google::protobuf::EnumDescriptor*)descriptor)->FindValueByName(name);
}
void* protobuf_enumdescriptor_findvaluebynumber(void* descriptor, int number) {
    return (void*)((const google::protobuf::EnumDescriptor*)descriptor)->FindValueByNumber(number);
}
const char* protobuf_enumvaluedescriptor_name(void* descriptor) {
    return ((const google::protobuf::EnumValueDescriptor*)descriptor)->name().c_str();
}
int protobuf_enumvaluedescriptor_number(void* descriptor) {
    return ((const google::protobuf::EnumValueDescriptor*)descriptor)->number();
}
int protobuf_fielddescriptor_cpptype(void* descriptor) {
    return ((const google::protobuf::FieldDescriptor*)descriptor)->cpp_type();
}

const char* protobuf_fielddescriptor_name(void* descriptor) {
    return ((const google::protobuf::FieldDescriptor*)descriptor)->name().c_str();
}

const char* protobuf_fielddescriptor_cpptypename(void* descriptor) {
    return ((const google::protobuf::FieldDescriptor*)descriptor)->cpp_type_name();
}

int protobuf_fielddescriptor_ismap(void* descriptor) {
    return ((const google::protobuf::FieldDescriptor*)descriptor)->is_map() ? 1 : 0;
}

int protobuf_fielddescriptor_isrepeated(void* descriptor) {
    return ((const google::protobuf::FieldDescriptor*)descriptor)->is_repeated() ? 1 : 0;
}

void* protobuf_fielddescriptor_messagetype(void* descriptor) {
    return (void*)((const google::protobuf::FieldDescriptor*)descriptor)->message_type();
}

void* protobuf_fielddescriptor_enumtype(void* descriptor) {
    return (void*)((const google::protobuf::FieldDescriptor*)descriptor)->enum_type();
}

void* protobuf_createfactory() {
    return new google::protobuf::DynamicMessageFactory();
}

void protobuf_freefactory(void* c) {
    delete ((google::protobuf::DynamicMessageFactory*)c);
}

void* protobuf_factory_createmessage(void* c, void* descriptor) {
    return ((google::protobuf::DynamicMessageFactory*)c)->GetPrototype((const google::protobuf::Descriptor*)descriptor)->New();
}

void protobuf_freemessage(void* m) {
    delete ((google::protobuf::Message*)m);
}

void* protobuf_clonemessage(void* m) {
    auto* new_msg = ((const google::protobuf::Message*)m)->New();
    new_msg->CopyFrom(*(const google::protobuf::Message*)m);
    return new_msg;
}

void* protobuf_message_getdescriptor(void* m) {
    return (void*)((google::protobuf::Message*)m)->GetDescriptor();
}

void* protobuf_message_getreflection(void* m) {
    return (void*)((google::protobuf::Message*)m)->GetReflection();
}

int protobuf_message_getbytesize(void* m) {
    return (int)((google::protobuf::Message*)m)->ByteSizeLong();
}

int protobuf_message_serializetoarray(void* m, void* buffer, int size) {
    return ((google::protobuf::Message*)m)->SerializeToArray(buffer, size) ? 1 : 0;
}

int protobuf_message_parsefromarray(void* m, void* buffer, int size) {
    return ((google::protobuf::Message*)m)->ParseFromArray(buffer, size) ? 1 : 0;
}

const char* protobuf_message_jsonencode(void* m) {
    static std::string temp;
    temp.clear();
    google::protobuf::util::JsonOptions option;
    option.preserve_proto_field_names = true;
    option.always_print_primitive_fields = true;
    if (google::protobuf::util::MessageToJsonString(*(const google::protobuf::Message*)m, &temp, option).ok())
        return temp.c_str();
    return nullptr;
}

const char* protobuf_message_jsondecode(void* m, const char* json) {
    static std::string temp;
    temp.clear();
    google::protobuf::util::JsonParseOptions option;
    option.ignore_unknown_fields = true;
    auto status = google::protobuf::util::JsonStringToMessage(json, (google::protobuf::Message*)m, option);
    if (status.ok()) return nullptr;

    temp = status.error_message();
    return temp.c_str();
}

int protobuf_reflection_getbool(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetBool(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field) ? 1 : 0;
}

int protobuf_reflection_getint32(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetInt32(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

unsigned int protobuf_reflection_getuint32(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetUInt32(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

long long protobuf_reflection_getint64(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetInt64(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

unsigned long long protobuf_reflection_getuint64(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetUInt64(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

double protobuf_reflection_getdouble(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetDouble(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

float protobuf_reflection_getfloat(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetFloat(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

int protobuf_reflection_getenumvalue(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetEnumValue(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

const char* protobuf_reflection_getstring(void* r, void* m, void* field) {
    static std::string temp;
    temp = ((google::protobuf::Reflection*)r)->GetString(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    return temp.c_str();
}

void* protobuf_reflection_getmessage(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->MutableMessage((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

void protobuf_reflection_setbool(void* r, void* m, void* field, int value) {
    return ((google::protobuf::Reflection*)r)->SetBool((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value != 0);
}

void protobuf_reflection_setint32(void* r, void* m, void* field, int value) {
    return ((google::protobuf::Reflection*)r)->SetInt32((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setuint32(void* r, void* m, void* field, unsigned int value) {
    return ((google::protobuf::Reflection*)r)->SetUInt32((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setint64(void* r, void* m, void* field, long long value) {
    return ((google::protobuf::Reflection*)r)->SetInt64((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setuint64(void* r, void* m, void* field, unsigned long long value) {
    return ((google::protobuf::Reflection*)r)->SetUInt64((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setdouble(void* r, void* m, void* field, double value) {
    return ((google::protobuf::Reflection*)r)->SetDouble((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setfloat(void* r, void* m, void* field, float value) {
    return ((google::protobuf::Reflection*)r)->SetFloat((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setenumvalue(void* r, void* m, void* field, int value) {
    return ((google::protobuf::Reflection*)r)->SetEnumValue((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

void protobuf_reflection_setstring(void* r, void* m, void* field, const char* value) {
    return ((google::protobuf::Reflection*)r)->SetString((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, value);
}

int protobuf_reflection_getrepeatedmessagecount(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::Message>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeatedboolcount(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<bool>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeatedint32count(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::int32>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeateduint32count(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::uint32>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeatedint64count(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::int64>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeateduint64count(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<google::protobuf::uint64>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeateddoublecount(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<double>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeatedfloatcount(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<float>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

int protobuf_reflection_getrepeatedstringcount(void* r, void* m, void* field) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFieldRef<std::string>(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field).size();
}

void* protobuf_reflection_getrepeatedmessage(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->MutableRepeatedMessage((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
}

int protobuf_reflection_getrepeatedbool(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedBool(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index) ? 1 : 0;
}

int protobuf_reflection_getrepeatedint32(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedInt32(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
}

unsigned int protobuf_reflection_getrepeateduint32(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedUInt32(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
}

long long protobuf_reflection_getrepeatedint64(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedInt64(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
}

unsigned long long protobuf_reflection_getrepeateduint64(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedUInt64(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
}

double protobuf_reflection_getrepeateddouble(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedDouble(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
}

float protobuf_reflection_getrepeatedfloat(void* r, void* m, void* field, int index) {
    return ((google::protobuf::Reflection*)r)->GetRepeatedFloat(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
}

const char* protobuf_reflection_getrepeatedstring(void* r, void* m, void* field, int index) {
    static std::string temp;
    temp = ((google::protobuf::Reflection*)r)->GetRepeatedString(*(const google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index);
    return temp.c_str();
}

void protobuf_reflection_setrepeatedbool(void* r, void* m, void* field, int index, int value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedBool((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value != 0);
}

void protobuf_reflection_setrepeatedint32(void* r, void* m, void* field, int index, int value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedInt32((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value);
}

void protobuf_reflection_setrepeateduint32(void* r, void* m, void* field, int index, unsigned int value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedUInt32((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value);
}

void protobuf_reflection_setrepeatedint64(void* r, void* m, void* field, int index, long long value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedInt64((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value);
}

void protobuf_reflection_setrepeateduint64(void* r, void* m, void* field, int index, unsigned long long value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedUInt64((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value);
}

void protobuf_reflection_setrepeateddouble(void* r, void* m, void* field, int index, double value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedDouble((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value);
}

void protobuf_reflection_setrepeatedfloat(void* r, void* m, void* field, int index, float value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedFloat((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value);
}

void protobuf_reflection_setrepeatedstring(void* r, void* m, void* field, int index, const char* value) {
    ((google::protobuf::Reflection*)r)->SetRepeatedString((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field, index, value);
}

void protobuf_reflection_clearfield(void* r, void* m, void* field) {
    ((google::protobuf::Reflection*)r)->ClearField((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
}

void* protobuf_reflection_insertrepeatedmessage(void* r, void* m, void* field, int index) {
    auto message = ((google::protobuf::Reflection*)r)->AddMessage((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::Message>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (index < 0 || index >= repeated.size() - 1) return message;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
    return message;
}

void protobuf_reflection_insertrepeatedbool(void* r, void* m, void* field, int index, int value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<bool>(
        (google::protobuf::Message*)m
        , (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value != 0);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_insertrepeatedint32(void* r, void* m, void* field, int index, int value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::int32>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_insertrepeateduint32(void* r, void* m, void* field, int index, unsigned int value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::uint32>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_insertrepeatedint64(void* r, void* m, void* field, int index, long long value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::int64>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_insertrepeateduint64(void* r, void* m, void* field, int index, unsigned long long value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::uint64>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_insertrepeateddouble(void* r, void* m, void* field, int index, double value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<double>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_insertrepeatedfloat(void* r, void* m, void* field, int index, float value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<float>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_insertrepeatedstring(void* r, void* m, void* field, int index, const char* value) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<std::string>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    repeated.Add(value);
    if (index < 0 || index >= repeated.size() - 1) return;
    for (int i = repeated.size() - 1; i > index; --i)
        repeated.SwapElements(i, i - 1);
}

void protobuf_reflection_removerepeatedmessage(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::Message>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeatedbool(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<bool>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeatedint32(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::int32>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeateduint32(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::uint32>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeatedint64(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::int64>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeateduint64(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<google::protobuf::uint64>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeateddouble(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<double>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeatedfloat(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<float>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}

void protobuf_reflection_removerepeatedstring(void* r, void* m, void* field, int index) {
    auto repeated = ((google::protobuf::Reflection*)r)->GetMutableRepeatedFieldRef<std::string>((google::protobuf::Message*)m, (const google::protobuf::FieldDescriptor*)field);
    if (repeated.size() <= 0 || index < 0 || index >= repeated.size()) return;
    for (int i = index; i < repeated.size() - 1; ++i)
        repeated.SwapElements(i, i + 1);
    repeated.RemoveLast();
}