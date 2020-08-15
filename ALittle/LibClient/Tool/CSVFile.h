
#ifndef _ALITTLE_CSVFILE_H_
#define _ALITTLE_CSVFILE_H_

#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>

#include <SDL.h>
#include "ALittle/LibClient/ThreadSystem/Task.h"

struct _csv;

namespace ALittle
{

class CsvFileLoader : public Task
{
public:
	static void HandleEvent(unsigned int event_type, void* data1, void* data2);

public:
	void SetPath(const char* file_path, bool only_from_asset);
	const char* GetPath() const { return m_file_path_param.c_str(); }

public:
	void Start();
	int GetID() const;

public:
	void Execute();
	void Abandon();

private:
	std::string m_file_path_param;
	bool m_only_from_asset_param;
	std::string m_empty_string;
};

class CsvFile
{
public:
	CsvFile() : m_csv(0) {}
	~CsvFile() { Close(); }

public:
	// file_path 是文件路径
	// only_from_asset 是否只从asset里面读取
	bool Load(const char* file_path, bool only_from_asset);

	// 关闭
	void Close();

public:
	const char* GetPath() const { return m_file_path.c_str(); }
	const char* ReadCell(int row, int col);
	int GetColCount() const;
	int GetRowCount() const;

private:
	std::string m_file_path;
	_csv* m_csv;
	std::string m_empty_string;
};

class CsvFileWrap
{
public:
	CsvFileWrap() : m_file(0) {}
	~CsvFileWrap() { if (m_file) delete m_file; }

public:
	void SetCsvFile(CsvFile* file) { m_file = file; }
	const char* GetPath() const { if (m_file == nullptr) return nullptr; return m_file->GetPath(); }
	const char* ReadCell(int lua_row, int lua_col) { if (m_file == nullptr) return nullptr; return m_file->ReadCell(lua_row, lua_col); }
	int GetColCount() const { if (m_file == nullptr) return 0; return m_file->GetColCount(); }
	int GetRowCount() const { if (m_file == nullptr) return 0; return m_file->GetRowCount(); }
	void Close() { if (m_file) delete m_file; m_file = nullptr; }

private:
	CsvFile* m_file;
};

} // ALittle

#endif // _ALITTLE_CSVFILE_H_
