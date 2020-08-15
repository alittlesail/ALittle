
#ifndef _ALITTLE_MESSAGE_H_
#define _ALITTLE_MESSAGE_H_

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

namespace ALittle
{

#define DATA_OFSSET(data, offset) static_cast<void*>(static_cast<char*>(data) + offset)
#define CONST_DATA_OFSSET(data, offset) static_cast<const void*>(static_cast<const char*>(data) + offset)

enum MessageDeserializeResult
{
    MDR_NO_DATA                 =  0,  // 当要反序列化时，没有数据了，这个主要是兼容协议向下兼容
    MDR_DATA_NOT_ENOUGH         = -1,  // 实际的数据长度比需要的小
    MDR_FLAG_LEN_NOT_ENOUGH     = -2,  // 前缀长度不足
};

typedef unsigned int MESSAGE_SIZE;
typedef int MESSAGE_ID;
typedef int MESSAGE_RPCID;

const static int PROTOCOL_HEAD_SIZE = sizeof(MESSAGE_SIZE) + sizeof(MESSAGE_ID) + sizeof(MESSAGE_RPCID);

class Message
{
public:
	Message() : __rpc_id(0) {}
	virtual ~Message() { }
	typedef MESSAGE_ID ID_TYPE;

public:
	virtual MESSAGE_ID GetID() const { return 0; }
	virtual int GetTotalSize() const { return 0; }
	virtual int Serialize(void* data) const { return 0; }
	virtual int Deserialize(const void* data, int len) { return 0; }

public:
    inline MESSAGE_RPCID GetRpcID() const { return __rpc_id; }
    inline void SetRpcID(MESSAGE_RPCID rpc_id) { __rpc_id = rpc_id; }

private:
    MESSAGE_RPCID __rpc_id;
};

template <typename T>
class MessagePtrWaper : public Message
{
public:
	MessagePtrWaper() : ptr(0) {}
	MessagePtrWaper(T* o) : ptr(o) {}

public:
	MESSAGE_ID GetID() const
	{
		if (ptr == 0) return 0;
		return ptr->GetID();
	}
	int GetTotalSize() const
	{
		if (ptr == 0) return 0;
		return ptr->GetTotalSize();
	}
	int Serialize(void* data) const
	{
		if (ptr == 0) return 0;
		return ptr->Serialize(data);
	}
	int Deserialize(const void* data, int len)
	{
		if (ptr == 0) return 0;
		return ptr->Deserialize(data, len);
	}

public:
	T* ptr;
};

// ------------------------------------------------------------------------------------
template <typename T> int Message_GetTotalSize(const T& object)
{
    return object.GetTotalSize() + sizeof(int);
}
template <typename T> int Message_GetTotalSize(const std::set<T>& object)
{
	int total_size = sizeof(int);

	for (auto it = object.begin(); it != object.end(); ++it)
		total_size += Message_GetTotalSize(*it);

	return total_size;
}
template <typename T> int Message_GetTotalSize(const std::list<T>& object)
{
	int total_size = sizeof(int);

	for (auto it = object.begin(); it != object.end(); ++it)
		total_size += Message_GetTotalSize(*it);

	return total_size;
}
template <typename T> int Message_GetTotalSize(const std::vector<T>& object)
{
	int total_size = sizeof(int);

	for (size_t i = 0; i < object.size(); ++i)
		total_size += Message_GetTotalSize(object[i]);

	return total_size;
}
template <typename K, typename V> int Message_GetTotalSize(const std::map<K, V>& object)
{
	int total_size = sizeof(int);

	for (auto it = object.begin(); it != object.end(); ++it)
	{
		total_size += Message_GetTotalSize(it->first);
		total_size += Message_GetTotalSize(it->second);
	}

	return total_size;
}

template <> int Message_GetTotalSize<std::string>(const std::string& object); // include '\0'
template <> int Message_GetTotalSize<bool>(const bool& object);
template <> int Message_GetTotalSize<char>(const char& object);
template <> int Message_GetTotalSize<unsigned char>(const unsigned char& object);
template <> int Message_GetTotalSize<short>(const short& object);
template <> int Message_GetTotalSize<unsigned short>(const unsigned short& object);
template <> int Message_GetTotalSize<int>(const int& object);
template <> int Message_GetTotalSize<unsigned int>(const unsigned int& object);
template <> int Message_GetTotalSize<long>(const long& object);
template <> int Message_GetTotalSize<unsigned long>(const unsigned long& object);
template <> int Message_GetTotalSize<long long>(const long long& object);
template <> int Message_GetTotalSize<unsigned long long>(const unsigned long long& object);
template <> int Message_GetTotalSize<float>(const float& object);
template <> int Message_GetTotalSize<double>(const double& object);

// ------------------------------------------------------------------------------------
template <typename T> int Message_SerializePrimary(const T& object, void* data)
{
	*static_cast<T*>(data) = object;
	return static_cast<int>(sizeof(T));
}

template <typename T> int Message_Serialize(const T& object, void* data)
{
    int result = object.Serialize(DATA_OFSSET(data, sizeof(int)));
    *static_cast<int*>(data) = result;
    return result + sizeof(int);
}
template <typename T> int Message_Serialize(const std::set<T>& object, void* data)
{
	// get size
	int len = static_cast<int>(object.size());
	*static_cast<int*>(data) = len;
	// offset current data
	char* current_data = static_cast<char*>(data) + sizeof(int);
	for (auto it = object.begin(); it != object.end(); ++it)
		current_data += Message_Serialize(*it, current_data);

	// return serialize size
	return static_cast<int>(static_cast<char*>(current_data) - static_cast<char*>(data));
}
template <typename T> int Message_Serialize(const std::list<T>& object, void* data)
{
	// get size
	int len = static_cast<int>(object.size());
	*static_cast<int*>(data) = len;
	// offset current data
	char* current_data = static_cast<char*>(data) + sizeof(int);
	for (auto it = object.begin(); it != object.end(); ++it)
		current_data += Message_Serialize(*it, current_data);

	// return serialize size
	return static_cast<int>(static_cast<char*>(current_data) - static_cast<char*>(data));
}
template <typename T> int Message_Serialize(const std::vector<T>& object, void* data)
{
	// get size
	int len = static_cast<int>(object.size());
	*static_cast<int*>(data) = len;
	// offset current data
	char* current_data = static_cast<char*>(data) + sizeof(int);
	for (int i = 0; i < len; ++i)
		current_data += Message_Serialize(object[i], current_data);

	// return serialize size
	return static_cast<int>(static_cast<char*>(current_data) - static_cast<char*>(data));
}
template <typename K, typename V> int Message_Serialize(const std::map<K,V>& object, void* data)
{
	int len = static_cast<int>(object.size());
	*static_cast<int*>(data) = len;

	char* current_data = static_cast<char*>(data) + sizeof(int);
	for (auto it = object.begin(); it != object.end(); ++it)
	{
		current_data += Message_Serialize(it->first, current_data);
		current_data += Message_Serialize(it->second, current_data);
	}

	return static_cast<int>(static_cast<char*>(current_data) - static_cast<char*>(data));
}

template <> int Message_Serialize<std::string>(const std::string& object, void* data);
template <> int Message_Serialize<bool>(const bool& object, void* data);
template <> int Message_Serialize<char>(const char& object, void* data);
template <> int Message_Serialize<unsigned char>(const unsigned char& object, void* data);
template <> int Message_Serialize<short>(const short& object, void* data);
template <> int Message_Serialize<unsigned short>(const unsigned short& object, void* data);
template <> int Message_Serialize<int>(const int& object, void* data);
template <> int Message_Serialize<unsigned int>(const unsigned int& object, void* data);
template <> int Message_Serialize<long>(const long& object, void* data);
template <> int Message_Serialize<unsigned long>(const unsigned long& object, void* data);
template <> int Message_Serialize<long long>(const long long& object, void* data);
template <> int Message_Serialize<unsigned long long>(const unsigned long long& object, void* data);
template <> int Message_Serialize<float>(const float& object, void* data);
template <> int Message_Serialize<double>(const double& object, void* data);

// ------------------------------------------------------------------------------------
template <typename T> int Message_DeserializePrimary(T& object, const void* data, int len)
{
	if (len == 0)
	{
		object = 0;
		return MDR_NO_DATA;
	}
	if (len < static_cast<int>(sizeof(T))) return MDR_DATA_NOT_ENOUGH;
	object = *static_cast<const T*>(data);
	return static_cast<int>(sizeof(T));
}

template <typename T> int Message_Deserialize(T& object, const void* data, int len)
{
    if (len == 0)
    {
        object = T();
        return MDR_NO_DATA;
    }

    // check size enough
    if (len < static_cast<int>(sizeof(int))) return MDR_DATA_NOT_ENOUGH;
    len -= static_cast<int>(sizeof(int)); // desc size of head

    int object_len = *static_cast<const int*>(data);
    if (object_len < 0) return MDR_FLAG_LEN_NOT_ENOUGH;

    // if length > remain length, then analysis error
    if (object_len > len) return MDR_DATA_NOT_ENOUGH;

    int result = object.Deserialize(CONST_DATA_OFSSET(data, sizeof(int)), object_len);
    if (result < MDR_NO_DATA) return result;

    return object_len + static_cast<int>(sizeof(int));
}
template <typename T> int Message_Deserialize(std::set<T>& object, const void* data, int len)
{
    if (len == 0)
    {
        object.clear();
        return MDR_NO_DATA;
    }

	if (len < static_cast<int>(sizeof(int))) return MDR_DATA_NOT_ENOUGH;
	len -= static_cast<int>(sizeof(int));

	// clear self
	object.clear();

	// get array length and check
	int array_len = *static_cast<const int*>(data);
	if (array_len < 0) return MDR_FLAG_LEN_NOT_ENOUGH;

	// offset target data position
	const char* current_data = static_cast<const char*>(data) + sizeof(int);
	for (int i = 0; i < array_len; ++i)
	{
		T t;
		int result = Message_Deserialize(t, current_data, len);
		if (result < MDR_NO_DATA) return result; current_data += result; len -= result;
		object.insert(t);
	}

	// calc final length
	return static_cast<int>(static_cast<const char*>(current_data) - static_cast<const char*>(data));
}
template <typename T> int Message_Deserialize(std::list<T>& object, const void* data, int len)
{
    if (len == 0)
    {
        object.clear();
        return MDR_NO_DATA;
    }

	if (len < static_cast<int>(sizeof(int))) return MDR_DATA_NOT_ENOUGH;
	len -= static_cast<int>(sizeof(int));

	// clear self
	object.clear();

	// get array length and check
	int array_len = *static_cast<const int*>(data);
	if (array_len < 0) return MDR_FLAG_LEN_NOT_ENOUGH;

	// offset target data position
	const char* current_data = static_cast<const char*>(data) + sizeof(int);
	for (int i = 0; i < array_len; ++i)
	{
		object.push_back(T());
		int result = Message_Deserialize(object.back(), current_data, len);
		if (result < MDR_NO_DATA) return result; current_data += result; len -= result;
	}

	// calc final length
	return static_cast<int>(static_cast<const char*>(current_data) - static_cast<const char*>(data));
}
template <typename T> int Message_Deserialize(std::vector<T>& object, const void* data, int len)
{
    if (len == 0)
    {
        object.clear();
        return MDR_NO_DATA;
    }

	if (len < static_cast<int>(sizeof(int))) return MDR_DATA_NOT_ENOUGH;
	len -= static_cast<int>(sizeof(int));

	// clear self
	object.resize(0);

	// define max len
	const int len_max = 1024;

	// get array length and check
	int array_len = *static_cast<const int*>(data);
	if (array_len < 0) return MDR_FLAG_LEN_NOT_ENOUGH;
	if (array_len < len_max) object.reserve(array_len);

	// offset target data position
	const char* current_data = static_cast<const char*>(data) + sizeof(int);
	for (int i = 0; i < array_len; ++i)
	{
		object.push_back(T());
		int result = Message_Deserialize(object.back(), current_data, len);
		if (result < MDR_NO_DATA) return result; current_data += result; len -= result;
	}

	// calc final length
	return static_cast<int>(static_cast<const char*>(current_data) - static_cast<const char*>(data));
}
template <typename K, typename V> int Message_Deserialize(std::map<K,V>& object, const void* data, int len)
{
    if (len == 0)
    {
        object.clear();
        return MDR_NO_DATA;
    }

	// check length last
	if (len < static_cast<int>(sizeof(int))) return MDR_DATA_NOT_ENOUGH;
	len -= static_cast<int>(sizeof(int));

	// clear self
	object.clear();

	// get length
	int map_len = *static_cast<const int*>(data);
    if (map_len < 0) return MDR_FLAG_LEN_NOT_ENOUGH;

	// offset to data position
	const char* current_data = static_cast<const char*>(data) + sizeof(int);
	for (int i = 0; i < map_len; ++i)
	{
		// deserialize key
		K key;
		int key_result = Message_Deserialize(key, current_data, len);
		if (key_result < MDR_NO_DATA) return key_result; current_data += key_result; len -= key_result;
		// deserialize value
		V& value = object[key] = V();
		int value_result = Message_Deserialize(value, current_data, len);
		if (value_result < MDR_NO_DATA) return value_result; current_data += value_result; len -= value_result;
	}

	return static_cast<int>(static_cast<const char*>(current_data) - static_cast<const char*>(data));
}
template <> int Message_Deserialize<std::string>(std::string& object, const void* data, int len);
template <> int Message_Deserialize<bool>(bool& object, const void* data, int len);
template <> int Message_Deserialize<char>(char& object, const void* data, int len);
template <> int Message_Deserialize<unsigned char>(unsigned char& object, const void* data, int len);
template <> int Message_Deserialize<short>(short& object, const void* data, int len);
template <> int Message_Deserialize<unsigned short>(unsigned short& object, const void* data, int len);
template <> int Message_Deserialize<int>(int& object, const void* data, int len);
template <> int Message_Deserialize<unsigned int>(unsigned int& object, const void* data, int len);
template <> int Message_Deserialize<long>(long& object, const void* data, int len);
template <> int Message_Deserialize<unsigned long>(unsigned long& object, const void* data, int len);
template <> int Message_Deserialize<long long>(long long& object, const void* data, int len);
template <> int Message_Deserialize<unsigned long long>(unsigned long long& object, const void* data, int len);
template <> int Message_Deserialize<float>(float& object, const void* data, int len);
template <> int Message_Deserialize<double>(double& object, const void* data, int len);

// ------------------------------------------------------------------------------------

// 边界条件
inline int Template_Message_GetTotalSize(int cur_size)
{
	return cur_size;
}

// 必须使用尾递归的写法，否则调用会产生非常大的代价
template<typename T1, typename ...T2>
inline int Template_Message_GetTotalSize(int cur_size, const T1& t0, const T2& ...args)
{
	int result = Message_GetTotalSize(t0);
	return Template_Message_GetTotalSize(cur_size + result, args...);
}

// 边界条件
inline int Template_Message_Serialize(int cur_size, void* data)
{
	return cur_size;
}

// 必须使用尾递归的写法，否则调用会产生非常大的代价
template<typename T1, typename ...T2>
inline int Template_Message_Serialize(int cur_size, void* data, const T1& t0, const T2& ...args)
{
	int result = Message_Serialize(t0, data);
	return Template_Message_Serialize(cur_size + result, DATA_OFSSET(data, result), args...);
}

// 边界条件
inline int Template_Message_Deserialize(int cur_size, const void* data, int len)
{
	return cur_size;
}

// 必须使用尾递归的写法，否则调用会产生非常大的代价
template<typename T1, typename ...T2>
inline int Template_Message_Deserialize(int cur_size, const void* data, int len, T1& t0, T2& ...args)
{
	int result = Message_Deserialize(t0, (const char*)data, len);
	if (result < MDR_NO_DATA) return result;
	
	return Template_Message_Deserialize(cur_size + result, (const char*)data + result, len - result, args...);
}

} // ALittle

//===========================================================================================================

#define VA_MESSAGE_EXPAND(...)      __VA_ARGS__

#define VA_MESSAGE_FILTER_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_N,...) _N
#define VA_MESSAGE_NUMBER_()        52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1
#define VA_MESSAGE_HELPER(...)      VA_MESSAGE_EXPAND(VA_MESSAGE_FILTER_(__VA_ARGS__))
#define VA_MESSAGE_COUNT(...)       VA_MESSAGE_HELPER(__VA_ARGS__, VA_MESSAGE_NUMBER_())

#define VA_MESSAGE_CAT(X, Y)        X##Y
#define VA_MESSAGE_JOIN(X, Y)       VA_MESSAGE_CAT(X, Y)
#define VA_MESSAGE_PROXY(F, ...)    VA_MESSAGE_EXPAND(F(__VA_ARGS__))

#define MESSAGE_MACRO_1(Name) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
}
#define MESSAGE_MACRO_3(Name, t0, m0) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0); } \
	Name() : m0() {} \
	t0 m0; \
}
#define MESSAGE_MACRO_5(Name, t0, m0, t1, m1) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1); } \
    Name() : m0(), m1() {} \
	t0 m0; t1 m1; \
}
#define MESSAGE_MACRO_7(Name, t0, m0, t1, m1, t2, m2) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2); } \
    Name() : m0(), m1(), m2() {} \
	t0 m0; t1 m1; t2 m2; \
}
#define MESSAGE_MACRO_9(Name, t0, m0, t1, m1, t2, m2, t3, m3) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3); } \
    Name() : m0(), m1(), m2(), m3() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; \
}
#define MESSAGE_MACRO_11(Name, t0, m0, t1, m1, t2, m2, t3, m3, t4, m4) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3, m4); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3, m4); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3, m4); } \
    Name() : m0(), m1(), m2(), m3(), m4() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; t4 m4; \
}
#define MESSAGE_MACRO_13(Name, t0, m0, t1, m1, t2, m2, t3, m3, t4, m4, t5, m5) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3, m4, m5); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3, m4, m5); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3, m4, m5); } \
    Name() : m0(), m1(), m2(), m3(), m4(), m5() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; t4 m4; t5 m5; \
}
#define MESSAGE_MACRO_15(Name, t0, m0, t1, m1, t2, m2, t3, m3, t4, m4, t5, m5, t6, m6) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3, m4, m5, m6); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3, m4, m5, m6); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3, m4, m5, m6); } \
    Name() : m0(), m1(), m2(), m3(), m4(), m5(), m6() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; t4 m4; t5 m5; t6 m6; \
}
#define MESSAGE_MACRO_17(Name, t0, m0, t1, m1, t2, m2, t3, m3, t4, m4, t5, m5, t6, m6, t7, m7) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3, m4, m5, m6, m7); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3, m4, m5, m6, m7); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3, m4, m5, m6, m7); } \
    Name() : m0(), m1(), m2(), m3(), m4(), m5(), m6(), m7() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; t4 m4; t5 m5; t6 m6; t7 m7; \
}
#define MESSAGE_MACRO_19(Name, t0, m0, t1, m1, t2, m2, t3, m3, t4, m4, t5, m5, t6, m6, t7, m7, t8, m8) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3, m4, m5, m6, m7, m8); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3, m4, m5, m6, m7, m8); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3, m4, m5, m6, m7, m8); } \
    Name() : m0(), m1(), m2(), m3(), m4(), m5(), m6(), m7(), m8() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; t4 m4; t5 m5; t6 m6; t7 m7; t8 m8; \
}
#define MESSAGE_MACRO_21(Name, t0, m0, t1, m1, t2, m2, t3, m3, t4, m4, t5, m5, t6, m6, t7, m7, t8, m8, t9, m9) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9); } \
    Name() : m0(), m1(), m2(), m3(), m4(), m5(), m6(), m7(), m8(), m9() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; t4 m4; t5 m5; t6 m6; t7 m7; t8 m8; t9 m9; \
}
#define MESSAGE_MACRO_23(Name, t0, m0, t1, m1, t2, m2, t3, m3, t4, m4, t5, m5, t6, m6, t7, m7, t8, m8, t9, m9, t10, m10) \
class Name : public ALittle::Message { \
public: \
	ALittle::MESSAGE_ID GetID() const { return _##Name; } \
	inline static ALittle::MESSAGE_ID GetStaticID() { return _##Name; } \
	inline static ALittle::Message* Create() { return new Name; } \
public: \
	int GetTotalSize() const { return ALittle::Template_Message_GetTotalSize(0, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10); } \
	int Serialize(void* _data) const { return ALittle::Template_Message_Serialize(0, _data, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10); } \
	int Deserialize(const void* _data, int _len) { return ALittle::Template_Message_Deserialize(0, _data, _len, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10); } \
    Name() : m0(), m1(), m2(), m3(), m4(), m5(), m6(), m7(), m8(), m9(), m10() {} \
	t0 m0; t1 m1; t2 m2; t3 m3; t4 m4; t5 m5; t6 m6; t7 m7; t8 m8; t9 m9; t10 m10; \
}

// 后面可以按规律去增加
#define MESSAGE_MACRO(...)        VA_MESSAGE_PROXY(VA_MESSAGE_JOIN(MESSAGE_MACRO_, VA_MESSAGE_COUNT(__VA_ARGS__)), __VA_ARGS__)

enum
{
	_HeartbeatMessage = 0,
	_RpcErrorMessage = 1,
};

MESSAGE_MACRO(HeartbeatMessage);
MESSAGE_MACRO(RpcErrorMessage, std::string, reason);

#endif // _ALITTLE_MESSAGE_H_
