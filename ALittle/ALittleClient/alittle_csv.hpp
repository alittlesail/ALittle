#ifndef ALITTLE_CSV_INCLUDED
#define ALITTLE_CSV_INCLUDED

#include "Carp/carp_csv.hpp"
#include "Carp/carp_task_consumer.hpp"
#include "Carp/carp_rwops.hpp"
#include "alittle_script.hpp"

extern int s_alittle_csv_id_creator;

class ALittleCsvFile : public CarpCsv
{
public:
	size_t GetColCount() const override { return CarpCsv::GetColCount(); }
	size_t GetRowCount() const override { return CarpCsv::GetRowCount(); }
	
	// 这个函数的下标从1开始
	const char* ReadCell(size_t row, size_t col) override { return CarpCsv::ReadCell(row, col); }
	const char* GetPath() const override { return CarpCsv::GetPath(); }
	void Close() override { CarpCsv::Close(); }
	// file_path 是文件路径
	// only_from_asset 是否只从asset里面读取
	bool Load(const char* file_path, bool only_assets)
	{
		Close();
		if (file_path == nullptr) return false;
		SDL_RWops* file = CarpRWops::OpenFile(file_path, "rb", false);
		if (file == nullptr) return false;
		const bool result = ReadFromCustomFile(file_path, (CarpCsv::READ_FILE)SDL_RWread, file, 0);
		SDL_RWclose(file);
		return result;
	}
};

class ALittleCsvFileWrap
{
public:
	~ALittleCsvFileWrap() { delete m_file; }

public:
	void SetCsvFile(ALittleCsvFile* file) { m_file = file; }
	const char* GetPath() const { if (m_file == nullptr) return nullptr; return m_file->GetPath(); }
	const char* ReadCell(int lua_row, int lua_col) const { if (m_file == nullptr) return nullptr; return m_file->ReadCell(lua_row, lua_col); }
	int GetColCount() const { if (m_file == nullptr) return 0; return static_cast<int>(m_file->GetColCount()); }
	int GetRowCount() const { if (m_file == nullptr) return 0; return static_cast<int>(m_file->GetRowCount()); }
	void Close() { if (m_file) delete m_file; m_file = nullptr; }

private:
	ALittleCsvFile* m_file = nullptr;
};

class ALittleCsvFileLoader : public CarpTask
{
public:
	ALittleCsvFileLoader()
	{
		++s_alittle_csv_id_creator;
		m_id = s_alittle_csv_id_creator;
	}
	
public:
	void SetPath(const char* file_path, bool only_assets)
	{
		if (file_path != nullptr) m_file_path = file_path;
		m_only_assets = only_assets;
	}
	const char* GetPath() const { return m_file_path.c_str(); }

public:
	void Start() {  s_carp_task_consumer.AddTask(this); }
	int GetID() const { return m_id; }

public:
	void Execute() override
	{
		auto* file = new ALittleCsvFile();
		if (file->Load(m_file_path.c_str(), m_only_assets))
		{
			s_carp_task_consumer.PushEvent([this, file]() { s_alittle_script.Invoke("__ALITTLEAPI_CsvFileLoadSucceed", this, file); });
		}
		else
		{
			delete file;
			s_carp_task_consumer.PushEvent([this, file]() { s_alittle_script.Invoke("__ALITTLEAPI_CsvFileLoadFailed", this); });
		}
	}
	void Abandon() override
	{
		s_carp_task_consumer.PushEvent([this]() { s_alittle_script.Invoke("__ALITTLEAPI_CsvFileLoadFailed", this); });
	}

private:
	std::string m_file_path;
	bool m_only_assets = false;
	int m_id = 0;
};

class ALittleCsv
{
public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleCsvFileLoader>("__CPPAPICsvFileLoader")
			.addConstructor<void(*)()>()
			.addFunction("Start", &ALittleCsvFileLoader::Start)
			.addFunction("SetPath", &ALittleCsvFileLoader::SetPath)
			.addFunction("GetPath", &ALittleCsvFileLoader::GetPath)
			.addFunction("GetID", &ALittleCsvFileLoader::GetID)
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleCsvFile>("__CPPAPICsvFile")
			.addConstructor<void(*)()>()
			.addFunction("Close", &ALittleCsvFile::Close)
			.addFunction("Load", &ALittleCsvFile::Load)
			.addFunction("GetPath", &ALittleCsvFile::GetPath)
			.addFunction("ReadCell", &ALittleCsvFile::ReadCell)
			.addFunction("GetRowCount", &ALittleCsvFile::GetRowCount)
			.addFunction("GetColCount", &ALittleCsvFile::GetColCount)
			.endClass();

		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleCsvFileWrap>("__CPPAPICsvFileWrap")
			.addConstructor<void(*)()>()
			.addFunction("Close", &ALittleCsvFileWrap::Close)
			.addFunction("SetCsvFile", &ALittleCsvFileWrap::SetCsvFile)
			.addFunction("GetPath", &ALittleCsvFileWrap::GetPath)
			.addFunction("ReadCell", &ALittleCsvFileWrap::ReadCell)
			.addFunction("GetRowCount", &ALittleCsvFileWrap::GetRowCount)
			.addFunction("GetColCount", &ALittleCsvFileWrap::GetColCount)
			.endClass();
	}
};

#endif

#ifdef ALITTLE_CSV_IMPL
#ifndef ALITTLE_CSV_IMPL_INCLUDE
#define ALITTLE_CSV_IMPL_INCLUDE
int s_alittle_csv_id_creator = 0;
#endif
#endif