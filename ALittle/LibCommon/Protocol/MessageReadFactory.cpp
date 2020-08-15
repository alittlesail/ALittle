
#include "MessageReadFactory.h"
#include "ALittle/LibCommon/Helper/FileHelper.h"
#include <memory.h>
#include <stdlib.h>

namespace ALittle
{

MessageReadFactory::MessageReadFactory()
: m_read_size(0), m_memory(nullptr), m_total_size(0), m_id(0), m_last_read_size(0), m_need_free(false)
{ }

MessageReadFactory::~MessageReadFactory()
{
	Clear();
}

void MessageReadFactory::Clear()
{
	if (m_memory && m_need_free)
		free((void*)m_memory);
	m_need_free = false;
	m_memory = 0;
}

int MessageReadFactory::Deserialize(const void* data, int len)
{
	Clear();
	m_memory = data;
	m_read_size = 0;
	m_total_size = len;
    m_last_read_size = 0;
	return 0;
}

bool MessageReadFactory::ReadFromStdFile(const char* file_path)
{
	std::vector<char> data;
	if (!FileHelper::LoadStdFile(file_path, data))
		return false;

	Clear();

	m_need_free = true;
	m_total_size = 0;
	if (data.size() > 0)
	{
		m_total_size = (int)data.size();
		m_memory = malloc(data.size());
		memcpy((void*)m_memory, data.data(), data.size());
	}

	m_read_size = 0;
	m_last_read_size = 0;
	return true;
}

const char* MessageReadFactory::ReadString()
{
	if (m_read_size >= m_total_size || m_read_size < 0)
    {
        m_last_read_size = -1;
		ALITTLE_ERROR("id: "<< m_id << "already read completed:" << m_total_size << ", " << m_read_size);
		return "";
	}
	int len = 0; // include '\0'
	memcpy(&len, CONST_DATA_OFSSET(m_memory, m_read_size), sizeof(len));
	if (len <= 0)
    {
        m_last_read_size = -1;
		ALITTLE_ERROR("id: "<< m_id << "string len: " << len << " is error:" << m_total_size << ", " << m_read_size);
		return "";
	}
	const char* value = static_cast<const char*>(m_memory) + m_read_size + sizeof(int);
	m_read_size += len + static_cast<int>(sizeof(int));
    m_last_read_size = len + static_cast<int>(sizeof(int));
	return value;
}

} // Protocol
