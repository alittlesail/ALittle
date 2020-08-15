
#ifndef _ALITTLE_MESSAGEWRITEFACTORY_H_
#define _ALITTLE_MESSAGEWRITEFACTORY_H_

#include "ALittle/LibCommon/Protocol/Message.h"
#include <vector>

namespace ALittle
{

class MessageWriteFactory : public Message
{
public:
	MessageWriteFactory();
	~MessageWriteFactory();

public:
	/**
	 * get message ID
	 * @return message ID
	 */
	MESSAGE_ID GetID() const { return m_id; }
	/**
	 * set message ID
	 * @param id message ID
	 */
	void SetID(MESSAGE_ID id) { m_id = id; }
#ifdef __EMSCRIPTEN__
	void SetRpcID(MESSAGE_RPCID rpc_id) { Message::SetRpcID(rpc_id); }
#endif

	/**
	 * get total size
	 * @return total size
	 */
	int GetTotalSize() const;

	/**
	 * Serialize
	 * @param data
	 * @return -1:failed, otherwise is serialize size
	 */
	int Serialize(void* data) const;

	/**
	 * write factory not do deserialize
	 */
	int Deserialize(const void* data, int len) { return -1; }

	/**
	 * write to file
	 * @param file_path
	 */
	bool WriteToStdFile(const char* file_path);

	/**
	 * reset offset
	 */
	void ResetOffset() { m_size = 0; }
	MESSAGE_SIZE GetOffset() { return m_size; }

public:
	template<typename T>
	inline int WritePrimaryType(T value)
	{
		ResizeMemory(sizeof(value));
		m_size += Message_Serialize(value, m_memory.data() + m_size);
		return static_cast<int>(sizeof(value));
	}

public:
	int WriteBool(bool value) { return WritePrimaryType(value); }
    int WriteChar(char value) { return WritePrimaryType(value); }
    int WriteUChar(unsigned char value) { return WritePrimaryType(value); }
    int WriteShort(short value) { return WritePrimaryType(value); }
    int WriteUShort(unsigned short value) { return WritePrimaryType(value); }
    int WriteInt(int value) { return WritePrimaryType(value); }
    int WriteUInt(unsigned int value) { return WritePrimaryType(value); }
    int WriteLong(long value) { return WritePrimaryType(value); }
    int WriteULong(unsigned long value) { return WritePrimaryType(value); }
    int WriteLongLong(long long value) { return WritePrimaryType(value); }
    int WriteULongLong(unsigned long long value) { return WritePrimaryType(value); }
    int WriteFloat(float value) { return WritePrimaryType(value); }
    int WriteDouble(double value) { return WritePrimaryType(value); }
	void SetInt(int offset, int value);
	int WriteString(const char* value);

private:
	/**
	 * add memory size
	 * @param add_size
	 */
	inline void ResizeMemory(size_t add_size)
	{
		if (m_memory.size() >= m_size + add_size) return;
		m_memory.resize(m_size + add_size, 0);
	}

public:
	std::vector<char> m_memory;

	MESSAGE_ID m_id;		// id
	MESSAGE_SIZE m_size;	// size
};

} // Protocol

#endif // _ALITTLE_MESSAGEWRITEFACTORY_H_