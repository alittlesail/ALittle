
#include "LocalFile.h"
#include "ALittle/LibClient/Helper/FileHelperEx.h"

#include "ALittle/LibCommon/Helper/FileHelper.h"
#include "ALittle/LibCommon/Helper/CryptHelper.h"

namespace ALittle
{

LocalFile::LocalFile()
	: m_memory(0)
	, m_read_rwops(0)
    , m_size(0)
    , m_cur_offset(0)
{ }

LocalFile::~LocalFile()
{
	Clear();
}

void LocalFile::ClearMemory()
{
	if (m_memory)
	{
		free(m_memory);
		m_memory = 0;
	}

	if (m_read_rwops)
	{
		SDL_RWclose(m_read_rwops);
		m_read_rwops = 0;
	}

	m_cur_offset = 0;
}

void LocalFile::Clear()
{
	m_path = "";
	m_size = 0;

	ClearMemory();
}

void LocalFile::Save(const char* file_path)
{
	if (!m_memory) return;

	FileHelperEx::SaveFile(file_path, m_memory, m_size);
}

const char* LocalFile::GetContent() const
{
	return m_memory;
}

const char* LocalFile::GetPath() const
{
	return m_path.c_str();
}

int LocalFile::GetSize() const
{
	return m_size;
}

void LocalFile::SetPath(const char* path)
{
	Clear();

	if (path == 0) return;
	m_path = path;
}

bool LocalFile::Load()
{
	ClearMemory();

	// open file from local directory first
	SDL_RWops* src_file = FileHelperEx::OpenFile(m_path, false, "rb");
	// check exist or not
	if (!src_file) return false;

	// get file size
	m_size = (unsigned int)SDL_RWsize(src_file);

	// malloc memory
	m_memory = (char*)malloc(m_size + 1);
	// write to memory
	SDL_RWread(src_file, (char*)m_memory, m_size, 1);
	// adjust to string
	m_memory[m_size] = 0;
	// close file
	SDL_RWclose(src_file);

	return true;
}

bool LocalFile::LoadBySDL()
{
	ClearMemory();

	// only load from asset
	SDL_RWops* src_file = FileHelperEx::OpenFile(m_path, true, "rb");
	// check file exist or not
	if (!src_file) return false;

	// get file size
	m_size = (unsigned int)SDL_RWsize(src_file);

	// malloc memory
	m_memory = (char*)malloc(m_size + 1);
	// write to memory
	SDL_RWread(src_file, (char*)m_memory, m_size, 1);
	// adjust to string
	m_memory[m_size] = 0;
	// close file
	SDL_RWclose(src_file);

	return true;
}

void LocalFile::Decrypt(const char* key)
{
	if (!m_memory) return;

	CryptHelper::XXTeaDecodeMemory(m_memory, m_size, key);
}

void LocalFile::Encrypt(const char* key)
{
	if (!m_memory) return;

	CryptHelper::XXTeaEncodeMemory(m_memory, m_size, key);
}

bool LocalFile::Open(bool only_from_asset)
{
	ClearMemory();

	// open file from local directory first
	m_read_rwops = FileHelperEx::OpenFile(m_path, only_from_asset, "rb");
	
	// check exist or not
	if (!m_read_rwops) return 0;

	// get file size
	m_size = (unsigned int)SDL_RWsize(m_read_rwops);

	return m_read_rwops;
}

int LocalFile::Read(char* buffer, int buffer_size, bool auto_close_file)
{
	int read_size = buffer_size;
	int remain_size = m_size - m_cur_offset;
	if (read_size > remain_size) read_size = remain_size;
	m_cur_offset += read_size;

	if (m_read_rwops)
	{
		if (auto_close_file && read_size == 0)
		{
			SDL_RWclose(m_read_rwops);
			m_read_rwops = 0;
			return 0;
		}

		size_t real_size = SDL_RWread(m_read_rwops, buffer, 1, read_size);
		if (auto_close_file && real_size == 0)
		{
			SDL_RWclose(m_read_rwops);
			m_read_rwops = 0;
			m_cur_offset = m_size;
			return 0;
		}

		return static_cast<int>(real_size);
	}

	return 0;
}

void LocalFile::Seek(int offset)
{
	if (m_read_rwops)
	{
		if (offset < 0) offset = 0;
		else if (offset >= m_size) offset = m_size;
		SDL_RWseek(m_read_rwops, offset, RW_SEEK_SET);
		m_cur_offset = offset;
	}
}

char LocalFile::ReadChar(int offset) const
{
	if (offset + (int)sizeof(char) > m_size) return 0;
	return *(m_memory + offset);
}

unsigned int LocalFile::ReadUInt(int offset) const
{
	if (offset + (int)sizeof(unsigned int) > m_size) return 0;
	return *((unsigned int*)(m_memory + offset));
}

int LocalFile::ReadInt(int offset) const
{
	if (offset + (int)sizeof(int) > m_size) return 0;
	return *((int*)(m_memory + offset));
}

float LocalFile::ReadFloat(int offset) const
{
	if (offset + (int)sizeof(float) > m_size) return 0;
	return *((float*)(m_memory + offset));
}

double LocalFile::ReadDouble(int offset) const
{
	if (offset + (int)sizeof(double) > m_size) return 0;
	return *((double*)(m_memory + offset));
}

} // ALittle
