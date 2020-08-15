
#include "Message.h"

namespace ALittle
{

template <>
int Message_GetTotalSize(const std::string& object)
{
	return static_cast<int>(object.size()) + static_cast<int>(sizeof(int)) + 1;
}

template <>
int Message_GetTotalSize(const bool& object)
{
	return static_cast<int>(sizeof(bool));
}

template <>
int Message_GetTotalSize(const char& object)
{
	return static_cast<int>(sizeof(char));
}

template <>
int Message_GetTotalSize(const unsigned char& object)
{
	return static_cast<int>(sizeof(unsigned char));
}

template <>
int Message_GetTotalSize(const short& object)
{
	return static_cast<int>(sizeof(short));
}

template <>
int Message_GetTotalSize(const unsigned short& object)
{
	return static_cast<int>(sizeof(unsigned short));
}

template <>
int Message_GetTotalSize(const int& object)
{
	return static_cast<int>(sizeof(int));
}

template <>
int Message_GetTotalSize(const unsigned int& object)
{
	return static_cast<int>(sizeof(unsigned int));
}

template <>
int Message_GetTotalSize(const long& object)
{
	return static_cast<int>(sizeof(long));
}

template <>
int Message_GetTotalSize(const unsigned long& object)
{
	return static_cast<int>(sizeof(unsigned long));
}

template <>
int Message_GetTotalSize(const long long& object)
{
	return static_cast<int>(sizeof(long long));
}

template <>
int Message_GetTotalSize(const unsigned long long& object)
{
	return static_cast<int>(sizeof(unsigned long long));
}

template <>
int Message_GetTotalSize(const float& object)
{
	return static_cast<int>(sizeof(float));
}
template <>
int Message_GetTotalSize(const double& object)
{
	return static_cast<int>(sizeof(double));
}

template <>
int Message_Serialize(const std::string& object, void* data)
{
	// get string length
	int len = static_cast<int>(object.size());
	// add '\0' to length
	*static_cast<int*>(data) = len + 1;
	// offset to string position
	char* data_string = static_cast<char*>(data) + sizeof(int);
	// copy string
	for (int i = 0; i < len; ++i) data_string[i] = object.at(i);
	// set tail of string to 0
	data_string[len] = 0;
	// return length
	return len + static_cast<int>(sizeof(int)) + 1;
}

template <>
int Message_Serialize(const bool& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const char& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const unsigned char& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const short& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const unsigned short& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const int& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const unsigned int& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const long& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const unsigned long& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const long long& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const unsigned long long& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const float& object, void* data) { return Message_SerializePrimary(object, data); }
template <>
int Message_Serialize(const double& object, void* data) { return Message_SerializePrimary(object, data); }

template <>
int Message_Deserialize(std::string& object, const void* data, int len)
{
	if (len == 0)
	{
		object.clear();
		return MDR_NO_DATA;
	}

	// check size enough
	if (len <= static_cast<int>(sizeof(int))) return MDR_DATA_NOT_ENOUGH;
	len -= sizeof(int); // desc size of head

	// get string length(include '\0')
	int str_len = *static_cast<const int*>(data);
	if (str_len <= 0) return MDR_FLAG_LEN_NOT_ENOUGH;

	// if length > remain length, then analysis error
	if (str_len > len) return MDR_DATA_NOT_ENOUGH;

	// offset to string position
	const char* str = (const char*)data;
	str += sizeof(int);

	// check real length
	while (*str && len > 0) { ++str; --len; }
	if (len <= 0) return MDR_DATA_NOT_ENOUGH;

	// check completed and copy string
	object.assign(static_cast<const char*>(data) + sizeof(int));
	return str_len + static_cast<int>(sizeof(int));
}

template <>
int Message_Deserialize(bool& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(char& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(unsigned char& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(short& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(unsigned short& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(int& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(unsigned int& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(long& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(unsigned long& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(long long& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(unsigned long long& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(float& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }
template <>
int Message_Deserialize(double& object, const void* data, int len) { return Message_DeserializePrimary(object, data, len); }

} // ALittle
