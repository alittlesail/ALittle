
#include "FileCacheSystem.h"
#include "Carp/carp_log.hpp"

#include <list>
#include <memory>

#include <time.h>

namespace ALittle
{

FileCache::FileCache(int unit_size)
	: m_status(FILECACHESTATUS_IDLE), m_last_empty_size(0), m_total_size(0)
{
	if (unit_size <= 0)
		m_unit_size = 1024 - 4;
	else
		m_unit_size = unit_size;
}

FileCache::~FileCache()
{
	Clear();
}

void FileCache::Clear()
{
    // 释放内存
	for (unsigned int i = 0; i < m_memory_list.size(); ++i)
		free(m_memory_list[i]);
	m_memory_list.clear();

    // 数据重置
	m_last_empty_size = 0;
	m_total_size = 0;
	m_status = FILECACHESTATUS_IDLE;
}

void FileCache::Write(void* memory, int size)
{
	if (m_status == FILECACHESTATUS_LOADED) return;

	// 把当前数据大小添加到总大小
	m_total_size += size;

	char* memory_tmp = static_cast<char*>(memory);
	while (size > 0)
	{
		// 如果最后一个块还未填满，那么就填充
		if (m_last_empty_size > 0 && !m_memory_list.empty())
		{
			char* last_memory = static_cast<char*>(m_memory_list.back());
			if (m_last_empty_size >= size)
			{
				memcpy(last_memory + m_unit_size - m_last_empty_size, memory_tmp, size);
				m_last_empty_size -= size;
				memory_tmp += size;
				size = 0;
			}
			else
			{
				memcpy(last_memory + m_unit_size - m_last_empty_size, memory_tmp, m_last_empty_size);
				size -= m_last_empty_size;
				memory_tmp += m_last_empty_size;
				m_last_empty_size = 0;
			}
		}
		// 创建一个新的内存块，并填充数据
		else
		{
			void* new_memory = malloc(m_unit_size);
			m_memory_list.push_back(new_memory);
			if (m_unit_size >= size)
			{
				memcpy(new_memory, memory_tmp, size);
				m_last_empty_size = m_unit_size - size;
				memory_tmp += size;
				size = 0;
			}
			else
			{
				memcpy(new_memory, memory_tmp, m_unit_size);
				size -= m_unit_size;
				memory_tmp += m_unit_size;
				m_last_empty_size = 0;
			}
		}
	}
}

int FileCache::Read(int offset, void* buffer, int size)
{
    // 计算偏移
	int index = offset / m_unit_size;
	int unit_offset = offset % m_unit_size;

	char* new_memory = static_cast<char*>(buffer);
	int last_buffer_size = size;

	int total_size = 0;
	while (true)
	{
		// 检查是否超出范围
		if (index >= static_cast<int>(m_memory_list.size()))
			break;

		// 如果缓冲区已经没有足够位置，那么就跳出
		if (last_buffer_size <= 0)
			break;

		// 获取内存位置
		char* file_memory = static_cast<char*>(m_memory_list[index]) + unit_offset;
		// 计算当前数据块剩余的数据大小
		int unit_last_size = m_unit_size - unit_offset;
		// 如果当前是最后一个数据块，根据实际大小来查看数据大小
		if (m_last_empty_size > 0 && index + 1 == static_cast<int>(m_memory_list.size()))
			unit_last_size = (m_unit_size - m_last_empty_size) - unit_offset;
        // 根据大小来填充缓冲区
		if (unit_last_size > last_buffer_size)
		{
			memcpy(new_memory, file_memory, last_buffer_size);
			unit_offset += last_buffer_size;
			new_memory += last_buffer_size;
			total_size += last_buffer_size;
			last_buffer_size = 0;
		}
		else
		{
			memcpy(new_memory, file_memory, unit_last_size);
			unit_offset = 0;
			++ index;
			new_memory += unit_last_size;
			total_size += unit_last_size;
			last_buffer_size -= unit_last_size;
		}
	}

    // 返回填充的数据量
	return total_size;
}

FileCache::Status FileCache::GetStatus() const
{
	return m_status;
}

void FileCache::SetStatus(Status status)
{
	m_status = status;
}

int FileCache::GetSize() const
{
	return m_total_size;
}

FileCacheHelper::FileCacheHelper(FileCacheSystem* system)
    : m_offset(0), m_native_file(0), m_native_size(0), m_system(system)
{

}

FileCacheHelper::~FileCacheHelper()
{
	Close();
}

bool FileCacheHelper::Open(const std::string& file_path, bool use_cache)
{
	Close();

	if (use_cache) 
		return m_system->Create(file_path, m_file_cache, &m_native_file, m_native_size);

	// open native file
#ifdef _WIN32
	fopen_s(&m_native_file, file_path.c_str(), "rb");
#else
	m_native_file = fopen(file_path.c_str(), "rb");
#endif
	if (m_native_file == 0) return false;

	fseek(m_native_file, 0, SEEK_END);
	m_native_size = (int)ftell(m_native_file);
	fseek(m_native_file, 0, SEEK_SET);

	return true;
}

int FileCacheHelper::GetFileSize()
{
	if (m_native_file) return m_native_size;

	if (!m_file_cache) return 0;
	return m_file_cache->GetSize();
}

void FileCacheHelper::SetOffset(int offset)
{
	if (m_native_file)
	{
		fseek(m_native_file, offset, SEEK_SET);
		m_offset = offset;

		// 如果设置了偏移，那么就放弃缓存
		if (m_file_cache)
		{
			m_file_cache->Clear();
			m_file_cache = FileCachePtr();
		}
	}
	else if (m_file_cache)
	{
		m_offset = offset;
	}
}

int FileCacheHelper::Read(void* buffer, int size)
{
	int read_size = 0;

	if (m_native_file)
	{
		read_size = (int)fread(buffer, 1, size, m_native_file);
		m_offset += read_size;

		if (m_file_cache)
		{
			m_file_cache->Write(buffer, read_size);
			if (m_offset >= m_native_size)
				m_file_cache->SetStatus(FileCache::FILECACHESTATUS_LOADED);
		}
	}
	else if (m_file_cache)
	{
		read_size = m_file_cache->Read(m_offset, buffer, size);
		m_offset += read_size;
	}

	return read_size;
}

void FileCacheHelper::Close()
{
	if (m_file_cache && m_file_cache->GetStatus() != FileCache::FILECACHESTATUS_LOADED)
		m_file_cache->Clear();

	m_file_cache = FileCachePtr();
	m_offset = 0;

	if (m_native_file)
		fclose(m_native_file);

	m_native_file = 0;
	m_native_size = 0;
}

bool FileCacheHelper::IsOpen()
{
	if (m_native_file || m_file_cache) return true;
	return false;
}

FileCacheSystem::FileCacheSystem()
	: m_total_size(0), m_max_size(1024*1024*100) // default 100MB
{

}

FileCacheSystem::~FileCacheSystem()
{

}

void FileCacheSystem::Setup()
{

}

void FileCacheSystem::Shutdown()
{
	ClearAll();
}

bool FileCacheSystem::Create(const std::string& file_path, FileCachePtr& file_cache, FILE** native_file, int& native_size)
{
	// init result
	file_cache = FileCachePtr();
	*native_file = 0;
	native_size = 0;

	// find file cache
	FileCacheInfoMap::iterator it = m_file_cache_map.find(file_path);
	if (it != m_file_cache_map.end())
	{
		if (it->second.file_cache->GetStatus() == FileCache::FILECACHESTATUS_IDLE)
		{
			// open native file
#ifdef _WIN32
			fopen_s(native_file, file_path.c_str(), "rb");
#else
			*native_file = fopen(file_path.c_str(), "rb");
#endif
			if (*native_file == 0)
			{
				m_total_size -= it->second.native_size;
				m_file_cache_map.erase(it);
				return false;
			}

			fseek(*native_file, 0, SEEK_END);
			native_size = (int)ftell(*native_file);
			fseek(*native_file, 0, SEEK_SET);

			it->second.file_cache->SetStatus(FileCache::FILECACHESTATUS_LOADING);
			file_cache = it->second.file_cache;
			it->second.update_time = CarpTimeHelper::GetCurTime();
		}
		else if (it->second.file_cache->GetStatus() == FileCache::FILECACHESTATUS_LOADING)
		{
			// open native file
#ifdef _WIN32
			fopen_s(native_file, file_path.c_str(), "rb");
#else
			*native_file = fopen(file_path.c_str(), "rb");
#endif
			if (*native_file == 0) return false;

			fseek(*native_file, 0, SEEK_END);
			native_size = (int)ftell(*native_file);
			fseek(*native_file, 0, SEEK_SET);
		}
		else
		{
			it->second.update_time = CarpTimeHelper::GetCurTime();
			file_cache = it->second.file_cache;
		}
	}
	else
	{
		// create info and set status
		FileCacheInfo info;
		info.create_time = CarpTimeHelper::GetCurTime();
		info.update_time = info.create_time;
		info.file_cache = FileCachePtr(new FileCache(-1)); // use default unit size
		info.file_cache->SetStatus(FileCache::FILECACHESTATUS_LOADING);

		// open native file
#ifdef _WIN32
		fopen_s(native_file, file_path.c_str(), "rb");
#else
		*native_file = fopen(file_path.c_str(), "rb");
#endif
		if (*native_file == 0) return false;

		fseek(*native_file, 0, SEEK_END);
		native_size = (int)ftell(*native_file);
		fseek(*native_file, 0, SEEK_SET);

		info.native_size = native_size;

		// save in system
		file_cache = info.file_cache;
		m_file_cache_map[file_path] = info;

		m_total_size += native_size;

		ClearByMaxSize(m_max_size);
	}

	return true;
}

void FileCacheSystem::ClearByTime(int time)
{
	FileCacheInfoMap::iterator it, end = m_file_cache_map.end();
	for (it = m_file_cache_map.begin(); it != end;)
	{
		if (it->second.update_time < time)
		{
			m_total_size -= it->second.native_size;
			it = m_file_cache_map.erase(it);
		}
		else
			++it;
	}
}

void FileCacheSystem::ClearBySize(int size)
{
	FileCacheInfoMap::iterator it, end = m_file_cache_map.end();
	for (it = m_file_cache_map.begin(); it != end;)
	{
		if (it->second.file_cache->GetSize() > size)
		{
			m_total_size -= it->second.native_size;
			it = m_file_cache_map.erase(it);
		}
		else
			++it;
	}
}

void FileCacheSystem::ClearByMaxSize(int max_size)
{
	if (m_total_size <= max_size) return;

	FileCacheInfoMap::iterator it, end = m_file_cache_map.end();
	for (it = m_file_cache_map.begin(); it != end;)
	{
		if (m_total_size <= max_size) return;

		m_total_size -= it->second.native_size;
		it = m_file_cache_map.erase(it);
	}
}

void FileCacheSystem::ClearByPath(const char* file_path)
{
	FileCacheInfoMap::iterator it = m_file_cache_map.find(file_path);
	if (it == m_file_cache_map.end()) return;

	m_total_size -= it->second.native_size;
	m_file_cache_map.erase(it);
}

void FileCacheSystem::ClearAll()
{
	m_file_cache_map.clear();
	m_total_size = 0;
}

void FileCacheSystem::SetMaxSize(int max_size)
{
	m_max_size = max_size;
	ClearByMaxSize(m_max_size);
}

} // ALittle
