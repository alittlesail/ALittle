
#include "CsvFile.h"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystem.h"

#include "Carp/carp_rwops.hpp"
#include "Carp/carp_task_consumer.hpp"

namespace ALittle
{

void CsvFileLoader::Start()
{
    s_carp_task_consumer.AddTask(this);
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

bool CsvFile::Load(const char* file_path, bool only_from_asset)
{
	Close();

	m_file_path = "";
	if (file_path == nullptr) return false;
	m_file_path = file_path;

    CARP_RWops* file = CARP_RWFromFile(file_path, "rb", false);
    if (file == nullptr) return false;
    
    bool result = m_csv.ReadFromCustomFile(file_path, (CarpCsv::read_file)CARP_RWread, file, 0);
    CARP_RWclose(file);
    return result;
}

void CsvFile::Close()
{
    m_csv.Close();
}

const char* CsvFile::ReadCell(int row, int col)
{
    const char* cell = m_csv.ReadCell(row, col);
    if (cell) return cell;
    return m_empty_string.c_str();
}

int CsvFile::GetColCount() const
{
    return (int)m_csv.GetColCount();
}

int CsvFile::GetRowCount() const
{
    return (int)m_csv.GetRowCount();
}

} // ALittle
