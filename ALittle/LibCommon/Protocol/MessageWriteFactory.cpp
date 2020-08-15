
#include "MessageWriteFactory.h"
#include "ALittle/LibCommon/Helper/FileHelper.h"
#include <memory.h>
#include <stdlib.h>

namespace ALittle
{
	
MessageWriteFactory::MessageWriteFactory()
: m_id(0), m_size(0)
{ }

MessageWriteFactory::~MessageWriteFactory()
{
}

int MessageWriteFactory::GetTotalSize() const
{
    return m_size;
}

int MessageWriteFactory::Serialize(void* data) const
{
	memcpy(data, m_memory.data(), m_size);
	return m_size;
}

bool MessageWriteFactory::WriteToStdFile(const char* file_path)
{
	return FileHelper::WriteToStdFile(file_path, m_memory);
}

void MessageWriteFactory::SetInt(int offset, int value)
{
    Message_Serialize(value, m_memory.data() + offset);
}

int MessageWriteFactory::WriteString(const char* value)
{
	int len = static_cast<int>(strlen(value));
	int total_size = len + sizeof(int) + 1;
	ResizeMemory(total_size);

	void* memory = m_memory.data() + m_size;

	int str_len = len + 1; // include '\0'
	memcpy(memory, &str_len, sizeof(str_len));
	char* data_string = static_cast<char*>(memory) + sizeof(int);
	for (int i = 0; i < len; ++i)
		data_string[i] = value[i];
	data_string[len] = 0;

	m_size += total_size;

    return total_size;
}

} // Protocol
