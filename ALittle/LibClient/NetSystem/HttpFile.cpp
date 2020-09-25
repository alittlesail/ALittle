
#include "HttpFile.h"
#include "NetSystem.h"
#include "Carp/carp_schedule.hpp"
#include "Carp/carp_log.hpp"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystem.h"
#include "Carp/carp_file.hpp"

namespace ALittle
{

CarpSafeIDCreator<int> HttpFile::s_id_creator;

HttpFile::HttpFile()
: m_total_size(0)
, m_cur_size(0)
, m_start_size(0)
, m_download(false)
{
	m_id = s_id_creator.CreateID();
}

HttpFile::~HttpFile()
{
	s_id_creator.ReleaseID(m_id);
	if (m_upload_client) m_upload_client->Stop();
	if (m_download_client) m_download_client->Stop();
}

const char* HttpFile::GetPath()
{
	return m_file_path.c_str();
}

void HttpFile::SetURL(const char* url, const char* file_path, bool download, int start_size, bool array_buffer)
{
	if (m_upload_client || m_download_client)
	{
		CARP_ERROR("socket already exist!");
		return;
	}

	m_url = url;
	m_file_path = file_path;
	m_download = download;
	m_start_size = start_size;

	if (download)
		m_download_client = CarpHttpClientTextPtr(new CarpHttpClientText());
	else
		m_upload_client = CarpHttpClientPostPtr(new CarpHttpClientPost());
}

int HttpFile::GetID() const
{
	return m_id;
}

unsigned int HttpFile::GetTotalSize() const
{
	return m_total_size;
}

unsigned int HttpFile::GetCurSize() const
{
	return m_cur_size;
}

void HttpFile::Start()
{
	if (m_download_client)
	{
		m_download_client->SendRequest(m_url, true, "", nullptr, 0
			, [this](bool result, const std::string& head, const std::string& body, const std::string& error)
			{
				if (result)
					g_ScheduleSystem.PushUserEvent(HTTP_DOWNLOAD_SUCCEED_EVENT, (void*)this);
				else
				{
					m_failed_reason = error;
					g_ScheduleSystem.PushUserEvent(HTTP_DOWNLOAD_FAILED_EVENT, (void*)this);
				}
			}
			, [this](int total_size, int cur_size)
			{
				m_total_size = total_size;
				m_cur_size = cur_size;
				g_ScheduleSystem.PushUserEvent(HTTP_UPLOADING_EVENT, (void*)this);
			}, &CarpScheduleInstance().GetIOService(), m_file_path, m_start_size, "");
	}
	else if (m_upload_client)
	{
		m_upload_client->SendRequest(m_url
			, std::map<std::string, std::string>()
			, CarpFile::GetFileNameByPath(m_file_path), m_file_path, m_start_size
			, [this](bool result, const std::string& head, const std::string& body, const std::string& error)
			{
				if (result)
					g_ScheduleSystem.PushUserEvent(HTTP_UPLOAD_SUCCEED_EVENT, (void*)this);
				else
				{
					m_failed_reason = error;
					g_ScheduleSystem.PushUserEvent(HTTP_UPLOAD_FAILED_EVENT, (void*)this);
				}
			}
			, [this](int total_size, int cur_size)
			{
				m_total_size = total_size;
				m_cur_size = cur_size;
				g_ScheduleSystem.PushUserEvent(HTTP_UPLOADING_EVENT, (void*)this);
			}, &CarpScheduleInstance().GetIOService(), "");
	}
}

void HttpFile::Stop()
{
	if (m_upload_client) m_upload_client->Stop();
	if (m_download_client) m_download_client->Stop();
}

void HttpFile::HandleEvent( unsigned int event_type, void* data1, void* data2 )
{
	HttpFile* file = (HttpFile*)data1;
	if (file == 0) return;
	if (event_type != HTTP_DOWNLOADING_EVENT && event_type != HTTP_UPLOADING_EVENT)
	{
		file->m_upload_client = CarpHttpClientPostPtr();
		file->m_download_client = CarpHttpClientTextPtr();
	}

    if (event_type == HTTP_DOWNLOADING_EVENT || event_type == HTTP_UPLOADING_EVENT)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpFileProcess", file->GetID(), file->GetCurSize(), file->GetTotalSize());
    else if (event_type == HTTP_DOWNLOAD_SUCCEED_EVENT || event_type == HTTP_UPLOAD_SUCCEED_EVENT)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpFileSucceed", file->GetID());
    else if (event_type == HTTP_DOWNLOAD_FAILED_EVENT || event_type == HTTP_UPLOAD_FAILED_EVENT)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpFileFailed", file->GetID(), file->m_failed_reason.c_str());
}

} // ALittle
