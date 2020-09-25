
#include "HttpClient.h"
#include "NetSystem.h"
#include "Carp/carp_schedule.hpp"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystem.h"

#include "Carp/carp_log.hpp"

namespace ALittle
{

CarpSafeIDCreator<int> HttpClient::s_id_creator;

HttpClient::HttpClient()
{
	m_id = s_id_creator.CreateID();
}

HttpClient::~HttpClient()
{
	s_id_creator.ReleaseID(m_id);
	if (m_client) m_client->Stop();
}

void HttpClient::SetURL(const char* url, const char* content)
{
	if (m_client)
	{
		CARP_ERROR("socket already exist!");
		return;
	}

	if (url) m_url = url;
	if (content) m_content = content;

	m_client = CarpHttpClientTextPtr(new CarpHttpClientText());
}

const char* HttpClient::GetResponse() const
{
	return m_response.c_str();
}

void HttpClient::GetContent(const char*& content, int& size)
{
	size = static_cast<int>(m_response.size());
	if (size <= 0)
	{
		content = 0;
		size = 0;
		return;
	}
	content = m_response.c_str();
}

const char* HttpClient::GetURL() const
{
	return m_url.c_str();
}

int HttpClient::GetID() const
{
	return m_id;
}

void HttpClient::Start()
{
	if (m_client)
	{
		m_client->SendRequest(m_url, m_content.empty(), "application/json", m_content.c_str(), m_content.size()
			, [this](bool result, const std::string& body, const std::string& head, const std::string& error)
			{
				if (result)
				{
					m_response = body;
					g_ScheduleSystem.PushUserEvent(NET_HTTP_SUCCEED, (void*)this);
				}
				else
				{
					m_failed_reason = error;
					g_ScheduleSystem.PushUserEvent(NET_HTTP_FAILED, (void*)this);
				}
			}
			, nullptr, &CarpScheduleInstance().GetIOService(), "", 0, "");
	}
}

void HttpClient::Stop()
{
	if (m_client) m_client->Stop();
}

void HttpClient::HandleEvent(unsigned int event_type, void* data1, void* data2)
{
	HttpClient* client = (HttpClient*)data1;
	client->m_client = CarpHttpClientTextPtr();

	if (event_type == NET_HTTP_SUCCEED)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpClientSucceed", client->GetID());
	else if (event_type == NET_HTTP_FAILED)
		g_ScriptSystem.Invoke("__ALITTLEAPI_HttpClientFailed", client->GetID(), client->m_failed_reason.c_str());
}

} // ALittle
