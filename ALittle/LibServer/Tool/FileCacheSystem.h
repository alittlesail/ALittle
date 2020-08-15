
#ifndef _ALITTLE_FILECACHESYSTEM_H_
#define _ALITTLE_FILECACHESYSTEM_H_

#include <vector>
#include <map>
#include <memory>
#include <string>

namespace ALittle
{

class FileCache
{
public:
	FileCache(int unit_size);
	~FileCache();

public:
	enum Status
	{
		FILECACHESTATUS_IDLE,           // 空闲
		FILECACHESTATUS_LOADING,        // 加载中
		FILECACHESTATUS_LOADED,         // 加载完成
	};

public:
	// 获取状态
	Status GetStatus() const;

    // 设置状态
	void SetStatus(Status status);

    // 获取大小
    int GetSize() const;

public:
    // 将数据写入缓存
    void Write(void* memory, int size);
    // 从缓存总读取数据
	int Read(int offset, void* buffer, int size);

    // 清理缓存
	void Clear();

private:
	Status m_status;					// 缓存状态
	int m_unit_size;					// 内存块大小

	int m_last_empty_size;				// 最后一个块的内存大小
	int m_total_size;					// 总大小
	std::vector<void*> m_memory_list;	// 内存块列表
};

typedef std::shared_ptr<FileCache> FileCachePtr;
class FileCacheSystem;

class FileCacheHelper
{
public:
	FileCacheHelper(FileCacheSystem* system);
	~FileCacheHelper();

public:
    // 打开文件
	bool Open(const std::string& file_path, bool use_cache);
	bool IsOpen();

    // 关闭文件
	void Close();
	
public:
    // 获取文件大小
	int GetFileSize();
    // 设置偏移
	void SetOffset(int offset);
    // 读取文件
	int Read(void* buffer, int size);

private:
	FileCachePtr m_file_cache;  // 文件缓存
	int m_offset;               // 偏移
	
private:
	FILE* m_native_file;        // 原始文件
	int m_native_size;          // 原始文件大小

private:
	FileCacheSystem* m_system;
};

class FileCacheSystem
{
public:
	FileCacheSystem();
	~FileCacheSystem();

public:
	void Setup();
	void Shutdown();

public:
    // 设置文件缓存上限
	void SetMaxSize(int max_size);

public:
    // 如果最后使用的时间小于time
    // 那么就清理掉
	void ClearByTime(int time);
	
    // 如果某些文件超过size的大小
    // 那么就清理掉
	void ClearBySize(int size);
	
    // 如果当前所有文件的大小总和超过max_size
    // 那么就清理到max_size为止
	void ClearByMaxSize(int max_size);
	
    // 根据文件路径来清理
	void ClearByPath(const char* file_path);
	
    // 清理全部
	void ClearAll();

public:
	bool Create(const std::string& file_path, FileCachePtr& file_cache, FILE** native_file, int& native_size);
	
private:
	struct FileCacheInfo
	{
		FileCachePtr file_cache;    // 缓存
		time_t create_time;         // 创建时间
		time_t update_time;         // 更新时间
		int native_size;            // 文件大小
	};

	typedef std::map<std::string, FileCacheInfo> FileCacheInfoMap;
	FileCacheInfoMap m_file_cache_map;

	int m_total_size;
	int m_max_size;
};

} // ALittle

#endif // _ALITTLE_FILECACHESYSTEM_H_
