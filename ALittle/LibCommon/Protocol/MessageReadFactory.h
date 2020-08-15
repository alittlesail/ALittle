
#ifndef _ALITTLE_MESSAGEREADFACTORY_H_
#define _ALITTLE_MESSAGEREADFACTORY_H_

#include "ALittle/LibCommon/Protocol/Message.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

#include <vector>

namespace ALittle
{

class MessageReadFactory : public Message
{
public:
	MessageReadFactory();
	~MessageReadFactory();

public:
	/**
	 * set message ID
	 * @param id  message ID
	 */
	void SetID(MESSAGE_ID id) { m_id = id; }

	/**
	 * get message ID
	 * @return message ID
	 */
	MESSAGE_ID GetID() const { return m_id; }
	
	/**
	 * get total size
	 * @return total size
	 */
	int GetDataSize() const { return m_total_size; }
	
	/**
	 * read factory not do serialize
	 */
	int Serialize(void* data) const { return 0; }

	/**
	 * deserialize
	 * @param data
	 * @param len
	 */
	int Deserialize(const void* data, int len);

	/**
	 * read from file
	 * @param file_path
	 */
	bool ReadFromStdFile(const char* file_path);

public:
	template<typename T>
	inline T ReadPrimaryType()
	{
		if (m_read_size >= m_total_size || m_read_size < 0)
		{
			m_last_read_size = -1;
			ALITTLE_ERROR("id:" << m_id << " already read completed:" << m_total_size << ", " << m_read_size);
			return 0;
		}
		T value = 0;
		memcpy(&value, CONST_DATA_OFSSET(m_memory, m_read_size), sizeof(T));
		m_read_size += static_cast<int>(sizeof(T));
		m_last_read_size = static_cast<int>(sizeof(T));
		return value;
	}

public:
	bool ReadBool() { return ReadPrimaryType<bool>(); }
	char ReadChar() { return ReadPrimaryType<char>(); }
	unsigned char ReadUChar() { return ReadPrimaryType<unsigned char>(); }
	short ReadShort() { return ReadPrimaryType<short>(); }
	unsigned short ReadUShort() { return ReadPrimaryType<unsigned short>(); }
	int ReadInt() { return ReadPrimaryType<int>(); }
	unsigned int ReadUInt() { return ReadPrimaryType<unsigned int>(); }
	long ReadLong() { return ReadPrimaryType<long>(); }
	unsigned long ReadULong() { return ReadPrimaryType<unsigned long>(); }
	long long ReadLongLong() { return ReadPrimaryType<long long>(); }
	unsigned long long ReadULongLong() { return ReadPrimaryType<unsigned long long>(); }
	float ReadFloat() { return ReadPrimaryType<float>(); }
	double ReadDouble() { return ReadPrimaryType<double>(); }
	const char* ReadString();
	int GetReadSize() const { return m_last_read_size; }

private:
	void Clear();

public:
	bool m_need_free;
	const void* m_memory;	// memory
	int m_read_size;		// read offset
	int m_total_size;		// total size
    int m_last_read_size;   // last read size
	MESSAGE_ID m_id;		// ID
};

} // Protocol

#endif // _ALITTLE_MESSAGEREADFACTORY_H_