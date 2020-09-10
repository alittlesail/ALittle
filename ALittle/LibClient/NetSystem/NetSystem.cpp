
#include "NetSystem.h"
#include "HttpClient.h"
#include "HttpFile.h"

#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"
#include "ALittle/LibCommon/Tool/MemoryPool.h"

namespace ALittle
{

NetSystem::NetSystem()
: m_netsystem_filter_push(0), m_netsystem_filter_handle(0)
, m_state(CONNECT_IDLE), m_port(0), m_socket(0), m_in_cancel(false)
, m_send_thread(0), m_receive_thread(0)
{
}

// remove event already in the queue
int NetSystem_EventFilter(void *userdata, SDL_Event * event)
{
	if (event->type != SDL_USEREVENT) return 1;

	if (event->user.code == NET_MESSAGE
		|| event->user.code == NET_DISCONNECT
		|| event->user.code == NET_CONNECT_SUCCEED
		|| event->user.code == NET_CONNECT_FAILED)
	{
		if (event->user.data1 == userdata)
		{
			g_MemoryPoolGroup.Release(event->user.data2);
			return 0;
		}
	}

	return 1;
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
		.addFunction("Load", &HttpClient::Load)
		.addFunction("Start", &HttpClient::Start)
		.addFunction("Stop", &HttpClient::Stop)
		.addFunction("GetStatus", &HttpClient::GetStatus)
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
		.addFunction("GetStatus", &HttpFile::GetStatus)
		.addFunction("GetContent", &HttpFile::GetContent)
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

void NetSystem::Execute()
{
	ALITTLE_INFO("connecting " << m_ip << ":" << m_port);
#ifdef __IPHONEOS__
	// start connect
	if (SDLNet_TCP_IPV6SocketConnect(m_socket, m_ip.c_str(), m_port)<0)
    {
        ++ m_netsystem_filter_push;
        g_ScheduleSystem.PushUserEvent(NET_CONNECT_FAILED, (void*)this, NULL);
        ALITTLE_ERROR("can't connect " << m_ip << ":" << m_port << ", " << SDLNet_GetError());
        return;
	}
#else
	IPaddress st_ip;
	// resolve ip
	if (SDLNet_ResolveHost(&st_ip, m_ip.c_str(), m_port) < 0)
	{
		++ m_netsystem_filter_push;
		g_ScheduleSystem.PushUserEvent(NET_CONNECT_FAILED, (void*)this, NULL);
		ALITTLE_ERROR("SDLNet_ResolveHost failed:" << SDLNet_GetError() << ", " << m_ip << ":" << m_port);
		return;
	}

	if (m_in_cancel)
	{
		++ m_netsystem_filter_push;
		g_ScheduleSystem.PushUserEvent(NET_CONNECT_FAILED, (void*)this, NULL);
		ALITTLE_ERROR("can't connect " << m_ip << ":" << m_port << ", " << " canceled");
		return;
	}

	// start connect
	if (SDLNet_TCP_SocketConnect(&st_ip, m_socket)<0)
	{
		++ m_netsystem_filter_push;
		g_ScheduleSystem.PushUserEvent(NET_CONNECT_FAILED, (void*)this, NULL);
		ALITTLE_ERROR("can't connect " << m_ip << ":" << m_port << ", " << SDLNet_GetError());
		return;
	}
#endif
	ALITTLE_INFO("connect " << m_ip << ":" << m_port << " succeed!");

	// connect succeed
	++ m_netsystem_filter_push;
	g_ScheduleSystem.PushUserEvent(NET_CONNECT_SUCCEED, (void*)this, NULL);
}

void NetSystem::Abandon()
{
	++ m_netsystem_filter_push;
	g_ScheduleSystem.PushUserEvent(NET_CONNECT_FAILED, (void*)this, NULL);
}

void NetSystem::HandleConnectEvent( unsigned int event_type, void* data1, void* data2 )
{
	NetSystem* self = (NetSystem*)data1;

	if (event_type == NET_CONNECT_SUCCEED)
	{
		if (self->m_in_cancel)
		{
			self->m_port = 0;
			self->m_ip = "";

			// release socket
			if (self->m_socket)
			{
				SDLNet_TCP_Close(self->m_socket);
				self->m_socket = 0;
			}
			self->m_state = CONNECT_IDLE;

			g_ScriptSystem.Invoke("__ALITTLEAPI_ConnectFailed", self->GetID());
			return;
		}

		// set conected
		self->m_state = CONNECT_ED;
		// create send thread
		self->m_send_thread = new SendThread(self->m_socket);
		// create receive thread
		self->m_receive_thread = new ReceiveThread(self, self->m_socket);
		// notify script system
		g_ScriptSystem.Invoke("__ALITTLEAPI_ConnectSucceed", self->GetID());
	}
	else if (event_type == NET_CONNECT_FAILED)
	{
		self->m_port = 0;
		self->m_ip = "";

		// release socket
		if (self->m_socket)
		{
			SDLNet_TCP_Close(self->m_socket);
			self->m_socket = 0;
		}
		self->m_state = CONNECT_IDLE;

		g_ScriptSystem.Invoke("__ALITTLEAPI_ConnectFailed", self);
	}
	else if (event_type == NET_DISCONNECT)
	{
		// flag to idle
		self->m_state = CONNECT_IDLE;
		// wait for receive thread completed
		// Due to the thread on the client side only deals with a socket, can wait
		if (self->m_receive_thread)
		{
			delete self->m_receive_thread;
			self->m_receive_thread = 0;
		}

		// wait for send thread completed
		// Due to the thread on the client side only deals with a socket, can wait
		if (self->m_send_thread)
		{
			delete self->m_send_thread;
			self->m_send_thread = 0;
		}

		if (self->m_socket)
		{
			self->m_port = 0;
			self->m_ip = "";

			// release socket
			SDLNet_TCP_Close(self->m_socket);
			self->m_socket = 0;
			g_ScriptSystem.Invoke("__ALITTLEAPI_Disconnect", self->GetID());
		}
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
	m_in_cancel = false;

	if (m_socket) SDLNet_TCP_Close(m_socket);
#ifdef __IPHONEOS__
	m_socket = SDLNet_TCP_IPV6SocketCreate(NetHelper::GetAIFamily(ip, port));
#else
	m_socket = SDLNet_TCP_SocketCreate();
#endif
	if (!m_socket) 
	{
		++ m_netsystem_filter_push;
		g_ScheduleSystem.PushUserEvent(NET_CONNECT_FAILED, (void*)this, NULL);
		ALITTLE_ERROR("Create socket faile:" << SDLNet_GetError());
		return;
	}
	// add to thread system
	g_ThreadSystem.AddTask(this, ThreadSystem::THREAD_TYPE_SLOW);
#endif
}

void NetSystem::Close()
{
	if (m_state == CONNECT_IDLE) return;

	if (m_state == CONNECT_ING)
	{
		m_in_cancel = true;
#ifdef __IPHONEOS__
		if (m_socket) SDLNet_TCP_JustClose(m_socket);
#else
		if (m_socket) SDLNet_TCP_JustShutdown(m_socket);
#endif
		return;
	}
	if (m_socket)
	{
		SDLNet_TCP_JustClose(m_socket);
	}
	ALITTLE_INFO(">>>>>>>>>>>>>>>>Net Close<<<<<<<<<<<<<<<");
	// wait for receive thread completed
	// Due to the thread on the client side only deals with a socket, can wait
	if (m_receive_thread)
	{
		delete m_receive_thread;
		m_receive_thread = 0;
	}

	// wait for send thread completed
	// Due to the thread on the client side only deals with a socket, can wait
	if (m_send_thread)
	{
		delete m_send_thread;
		m_send_thread = 0;
	}

	if (m_socket)
	{
		// free socket
		SDLNet_TCP_JustFree(m_socket);
		m_socket = 0;
	}

	// flag to idle
	m_state = CONNECT_IDLE;

	m_port = 0;
	m_ip = "";
}

void NetSystem::Send(const Message& message)
{
	if (!m_send_thread) return;

	m_send_thread->Send(message);
}

void NetSystem::SendFactory(const MessageWriteFactory* message)
{
	if (!m_send_thread) return;

	m_send_thread->Send(*message);
}

void NetSystem::HandleMessageEvent(unsigned int event_type, void* data1, void* data2)
{
	NetSystem* self = (NetSystem*)data1;
	if (data2 == 0) return;

	// save memory
	char* body_memory = (char*)data2;

	// get message size
	MESSAGE_SIZE len = 0;
	memcpy(&len, body_memory, sizeof(MESSAGE_SIZE));
	body_memory += sizeof(MESSAGE_SIZE);
	MESSAGE_ID head_id = 0;
	memcpy(&head_id, body_memory, sizeof(MESSAGE_ID));
	body_memory += sizeof(MESSAGE_ID);
    MESSAGE_RPCID head_rpc_id = 0;
    memcpy(&head_rpc_id, body_memory, sizeof(MESSAGE_RPCID));
    body_memory += sizeof(MESSAGE_RPCID);

	// execute callback
	if (head_id >= self->m_handle_list.size() || !self->m_handle_list[head_id])
	{
		// If is unknown packets, then handed over to read the data factory processing, and then to the script
		self->m_read_factory.SetID(head_id);
        self->m_read_factory.SetRpcID(head_rpc_id);
		self->m_read_factory.Deserialize(body_memory, len);
		g_ScriptSystem.Invoke("__ALITTLEAPI_Message", self->GetID(), head_id, head_rpc_id, &self->m_read_factory);
	}
	else
	{
		// If the registered callback function, then execute
		Message* msg = self->m_message_list[head_id];
        msg->SetRpcID(head_rpc_id);
		if (msg->Deserialize(body_memory, len) >= 0)
			self->m_handle_list[head_id](*msg);
		else
			ALITTLE_ERROR("message: " << head_id << " Deserialize failed!");
	}

	// release memory
	g_MemoryPoolGroup.Release(data2);
}

void NetSystem::RegisterHandle(Message* msg, MessageHandle func)
{
	unsigned int id = msg->GetID();
	// Expand the register list
	if (m_handle_list.size() <= id)
	{
		m_message_list.resize(id + 1);
		m_handle_list.resize(id + 1);
	}
	// set callback
	m_handle_list[id] = func;
	// set message object
	if (m_message_list[id])
		delete m_message_list[id];
	m_message_list[id] = msg;
}

} // ALittle
