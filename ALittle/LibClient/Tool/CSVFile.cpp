
#include "CsvFile.h"
#include "LocalFile.h"

extern "C" {
#include "ALittle/LibCommon/ThirdParty/csv/csv.h"
}

#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"

namespace ALittle
{

void CsvFileLoader::Start()
{
    g_ThreadSystem.AddTask(this);
}

int CsvFileLoader::GetID() const
{
#ifdef __IPHONEOS__
    static int s_id = 0;
    ++s_id;
    return s_id;
#else
    int id = 0;
    const CsvFileLoader* data = this;
    memcpy(&id, &data, sizeof(int));
    return id;
#endif
}

void CsvFileLoader::HandleEvent(unsigned int event_type, void* data1, void* data2)
{
    CsvFileLoader* loader = (CsvFileLoader*)data1;
    CsvFile* file = (CsvFile*)data2;
    if (event_type == CSV_LOAD_FAILED)
    {
        g_ScriptSystem.Invoke("__ALITTLEAPI_CsvFileLoadFailed", loader, file);
        return;
    }
    g_ScriptSystem.Invoke("__ALITTLEAPI_CsvFileLoadSucceed", loader, file);
}

void CsvFileLoader::SetPath(const char* file_path, bool only_from_asset)
{
    if (file_path != nullptr) m_file_path_param = file_path;
    m_only_from_asset_param = only_from_asset;
}

void CsvFileLoader::Execute()
{
    CsvFile* file = new CsvFile();
    if (file->Load(m_file_path_param.c_str(), m_only_from_asset_param))
    {
        g_ScheduleSystem.PushUserEvent(CSV_LOAD_SUCCEED, this, file);
    }
    else
    {
        delete file;
        g_ScheduleSystem.PushUserEvent(CSV_LOAD_FAILED, this);
    }
}

void CsvFileLoader::Abandon()
{
    g_ScheduleSystem.PushUserEvent(CSV_LOAD_FAILED, this);
}

size_t csv_sdl_fread(void* buffer, size_t element_size, size_t count, void* file)
{
    return ((LocalFile*)file)->Read((char*)buffer, (int)(element_size * count), false);
}

bool CsvFile::Load(const char* file_path, bool only_from_asset)
{
	Close();

	m_file_path = "";
	if (file_path == nullptr) return false;
	m_file_path = file_path;

    LocalFile file;
    file.SetPath(file_path);
    if (!file.Open(only_from_asset)) return false;

    m_csv = csv_create();
    return csv_load(m_csv, file_path, csv_sdl_fread, &file, 0) != 0;
}

void CsvFile::Close()
{
    if (m_csv)
    {
        csv_destroy(m_csv);
        m_csv = 0;
    }   
}

const char* CsvFile::ReadCell(int row, int col)
{
    if (m_csv == 0) return m_empty_string.c_str();
    return csv_readcell(m_csv, row - 1, col - 1);
}

int CsvFile::GetColCount() const
{
    if (m_csv == 0) return 0;
    return csv_colcount(m_csv);
}

int CsvFile::GetRowCount() const
{
    if (m_csv == 0) return 0;
    return csv_rowcount(m_csv);
}

} // ALittle
