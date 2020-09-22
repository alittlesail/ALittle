
#include "NetSystem.h"
#include "HttpClient.h"
#include "HttpFile.h"

#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"

#define CARP_SCHEDULE_IMPL
#include "Carp/carp_schedule.hpp"

CarpSchedule& CarpScheduleInstance()
{
	static CarpSchedule instance;
	return instance;
}

namespace ALittle
{

// remove event already in the queue
int NetSystem_EventFilter(void* userdata, SDL_Event* event)
{
	if (event->type != SDL_USEREVENT) return 1;

	if (event->user.code == NET_MESSAGE
		|| event->user.code == NET_DISCONNECT
		|| event->user.code == NET_CONNECT_SUCCEED
		|| event->user.code == NET_CONNECT_FAILED)
	{
		if (event->user.data1 == userdata)
		{
			free(event->user.data2);
			return 0;
		}
	}

	return 1;
}

NetSystem::NetSystem()
: m_netsystem_filter_push(0), m_netsystem_filter_handle(0)
, m_state(CONNECT_IDLE), m_port(0)
{
}

NetSystem::~NetSystem()
{
	Close();

	if (m_netsystem_filter_push != m_netsystem_filter_handle)
		SDL_FilterEvents(NetSystem_EventFilter, this);
}

void NetSystem::Setup()
{
	g_ScheduleSystem.RegisterHandle(HTTP_DOWNLOADING_EVENT, HttpFile::HandleEvent);
	g_ScheduleSystem.RegisterHandle(HTTP_DOWNLOAD_SUCCEED_EVENT, HttpFile::HandleEvent);
	g_ScheduleSystem.RegisterHandle(HTTP_DOWNLOAD_FAILED_EVENT, HttpFile::HandleEvent);
	g_ScheduleSystem.RegisterHandle(HTTP_UPLOADING_EVENT, HttpFile::HandleEvent);
	g_ScheduleSystem.RegisterHandle(HTTP_UPLOAD_SUCCEED_EVENT, HttpFile::HandleEvent);
	g_ScheduleSystem.RegisterHandle(HTTP_UPLOAD_FAILED_EVENT, HttpFile::HandleEvent);

	g_ScheduleSystem.RegisterHandle(NET_HTTP_SUCCEED, HttpClient::HandleEvent);
	g_ScheduleSystem.RegisterHandle(NET_HTTP_FAILED, HttpClient::HandleEvent);

	g_ScheduleSystem.RegisterHandle(NET_MESSAGE, NetSystem::HandleMessageEvent);
	g_ScheduleSystem.RegisterHandle(NET_DISCONNECT, NetSystem::HandleConnectEvent);
	g_ScheduleSystem.RegisterHandle(NET_CONNECT_SUCCEED, NetSystem::HandleConnectEvent);
	g_ScheduleSystem.RegisterHandle(NET_CONNECT_FAILED, NetSystem::HandleConnectEvent);

	CarpScheduleInstance().Start(nullptr);
}

void NetSystem::Shutdown()
{
}

void NetSystem::RegisterToScript(ScriptSystem& script_system)
{
	lua_State* L = script_system.GetLuaState();

	luabridge::getGlobalNamespace(L)
		.beginClass<NetSystem>("__CPPAPIMsgInterface")
		.addConstructor<void(*)()>()
		.addFunction("GetID", &NetSystem::GetID)
		.addFunction("Connect", &NetSystem::Connect)
		.addFunction("Close", &NetSystem::Close)
		.addFunction("IsConnected", &NetSystem::IsConnected)
		.addFunction("SendFactory", &NetSystem::SendFactory)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<HttpClient>("__CPPAPIHttpInterface")
		.addConstructor<void(*)()>()
		.addFunction("GetID", &HttpClient::GetID)
		.addFunction("SetURL", &HttpClient::SetURL)
		.addFunction("Start", &HttpClient::Start)
		.addFunction("Stop", &HttpClient::Stop)
		.addFunction("GetResponse", &HttpClient::GetResponse)
		.addFunction("GetURL", &HttpClient::GetURL)
		.endClass();

	luabridge::getGlobalNamespace(L)
		.beginClass<HttpFile>("__CPPAPIHttpFileInterface")
		.addConstructor<void(*)()>()
		.addFunction("SetURL", &HttpFile::SetURL)
		.addFunction("GetID", &HttpFile::GetID)
		.addFunction("Start", &HttpFile::Start)
		.addFunction("Stop", &HttpFile::Stop)
		.addFunction("GetPath", &HttpFile::GetPath)
		.addFunction("GetTotalSize", &HttpFile::GetTotalSize)
		.addFunction("GetCurSize", &HttpFile::GetCurSize)
		.endClass();
}

int NetSystem::GetID() const
{
#ifdef __IPHONEOS__
	static int s_id = 0;
	++s_id;
	return s_id;
#else
	int id = 0;
	const NetSystem* data = this;
	memcpy(&id, &data, sizeof(int));
	return id;
#endif
}

void NetSystem::HandleConnectEvent( unsigned int event_type, void* data1, void* data2 )
{
	NetSystem* self = (NetSystem*)data1;

	if (event_type == NET_CONNECT_SUCCEED)
	{
		++self->m_netsystem_filter_handle;
		// set conected
		self->m_state = CONNECT_ED;
		// notify script system
		g_ScriptSystem.Invoke("__ALITTLEAPI_ConnectSucceed", self->GetID());
	}
	else if (event_type == NET_CONNECT_FAILED)
	{
		++self->m_netsystem_filter_handle;
		self->m_state = CONNECT_IDLE;
		self->m_port = 0;
		self->m_ip = "";
		self->m_client = CarpConnectClientPtr();

		g_ScriptSystem.Invoke("__ALITTLEAPI_ConnectFailed", self);
	}
	else if (event_type == NET_DISCONNECT)
	{
		++self->m_netsystem_filter_handle;
		// flag to idle
		self->m_state = CONNECT_IDLE;
		self->m_port = 0;
		self->m_ip = "";
		self->m_client = CarpConnectClientPtr();

		g_ScriptSystem.Invoke("__ALITTLEAPI_Disconnect", self->GetID());
	}
}

void NetSystem::Connect(const char* ip, unsigned int port)
{
	// if current is connected then close first
	if (m_state == CONNECT_ED) Close();

	// if connecting then return
	if (m_state == CONNECT_ING)
	{
		ALITTLE_WARN("net system already connecting:" << m_ip << ":" << m_port);
		return;
	}

	if (ip) m_ip = ip;
	m_port = port;

#ifdef __EMSCRIPTEN__
	g_ScriptSystem.Invoke("__ALITTLEAPI_ConnectFailed", this);
#else
	// flag to connecting
	m_state = CONNECT_ING;

	m_client = CarpConnectClientPtr(new CarpConnectClient());
	m_client->Connect(m_ip, m_port, &CarpScheduleInstance().GetIOService()
		, std::bind(&NetSystem::HandleConnectFailed, this)
		, std::bind(&NetSystem::HandleConnectSucceed, this)
		, std::bind(&NetSystem::HandleDisconnected, this)
		, std::bind(&NetSystem::HandleMessage, this, std::placeholders::_1, std::placeholders::_2));
#endif
}

void NetSystem::Close()
{
	if (m_state == CONNECT_IDLE) return;
	m_client->Close();
	
	// flag to idle
	m_state = CONNECT_IDLE;

	m_port = 0;
	m_ip = "";
}

void NetSystem::Send(const CarpMessage& message)
{
	if (!m_client) return;

	int size = 0;
	void* memory = message.CreateMemoryForSend(&size);
	m_client->SendPocket(memory, size);
}

void NetSystem::SendFactory(const CarpMessageWriteFactory* message)
{
	if (!m_client) return;

	int size = 0;
	void* memory = message->CreateMemoryForSend(&size);
	m_client->SendPocket(memory, size);
}

void NetSystem::HandleMessageEvent(unsigned int event_type, void* data1, void* data2)
{
	NetSystem* self = (NetSystem*)data1;
	if (data2 == 0) return;
	++self->m_netsystem_filter_handle;

	// save memory
	char* memory = (char*)data2;

	// get message size
	CARP_MESSAGE_SIZE len = 0;
	memcpy(&len, memory, sizeof(CARP_MESSAGE_SIZE));
	memory += sizeof(CARP_MESSAGE_SIZE);
	CARP_MESSAGE_ID head_id = 0;
	memcpy(&head_id, memory, sizeof(CARP_MESSAGE_ID));
	memory += sizeof(CARP_MESSAGE_ID);
	CARP_MESSAGE_RPCID head_rpc_id = 0;
    memcpy(&head_rpc_id, memory, sizeof(CARP_MESSAGE_RPCID));
	memory += sizeof(CARP_MESSAGE_RPCID);

	// If is unknown packets, then handed over to read the data factory processing, and then to the script
	self->m_read_factory.SetID(head_id);
    self->m_read_factory.SetRpcID(head_rpc_id);
	self->m_read_factory.Deserialize(memory, len);
	g_ScriptSystem.Invoke("__ALITTLEAPI_Message", self->GetID(), head_id, head_rpc_id, &self->m_read_factory);

	// release memory
	free(data2);
}

void NetSystem::HandleConnectFailed()
{
	++m_netsystem_filter_push;
	g_ScheduleSystem.PushUserEvent(NET_CONNECT_FAILED, (void*)this, NULL);
}

void NetSystem::HandleConnectSucceed()
{
	++m_netsystem_filter_push;
	g_ScheduleSystem.PushUserEvent(NET_CONNECT_SUCCEED, (void*)this, NULL);
}

void NetSystem::HandleDisconnected()
{
	++m_netsystem_filter_push;
	g_ScheduleSystem.PushUserEvent(NET_DISCONNECT, (void*)this, NULL);
}

void NetSystem::HandleMessage(void* message, int size)
{
	++m_netsystem_filter_push;
	g_ScheduleSystem.PushUserEvent(NET_MESSAGE, (void*)this, message);
}

} // ALittle
