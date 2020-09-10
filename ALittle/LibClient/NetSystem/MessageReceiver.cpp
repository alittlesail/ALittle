
#include "MessageReceiver.h"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"

#include "ALittle/LibCommon/Tool/MemoryPool.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

#include "NetSystem.h"

namespace ALittle
{

MessageReceiver::MessageReceiver(NetSystem* net_system, TCPsocket socket)
: m_net_system(net_system), m_socket(socket)
, m_receive_head(true), m_message_size(0), m_message_id(0), m_message_rpc_id(0)
, m_memory(0)
{
	// init address of message size and message id
	m_message_size = (MESSAGE_SIZE*)m_message_head;
    m_message_id = (MESSAGE_ID*)(m_message_head + sizeof(MESSAGE_SIZE));
    m_message_rpc_id = (MESSAGE_RPCID*)(m_message_head + sizeof(MESSAGE_SIZE) + sizeof(MESSAGE_ID));
	// init with 0
    memset(m_message_head, 0, sizeof(m_message_head));
}

MessageReceiver::~MessageReceiver()
{
	Clear();
}

void MessageReceiver::Clear()
{
	// release memory
	if (m_memory)
		g_MemoryPoolGroup.Release(m_memory);

	// reset message head
	*m_message_id = 0;
    *m_message_rpc_id = 0;
	*m_message_size = 0;
	// reset message body
	m_receive_head = true;
	m_memory = 0;
}

bool MessageReceiver::Run()
{
	// check message receive completed or not
	if (m_receive_head)
	{
		// flag with false, then receive body
		m_receive_head = false;

		// if receive failed, then reset status and retuen
		int max_len = sizeof(m_message_head);
		int recv_len = NetHelper::TCPSocketReceive(m_socket, m_message_head, max_len);
		if (recv_len < max_len)
		{
			Clear();
			if (strlen(SDLNet_GetError()) > 0) ALITTLE_ERROR(SDLNet_GetError());
			return false;
		}
		
		// malloc memory
		m_memory = g_MemoryPoolGroup.Create(static_cast<size_t>(*m_message_size) + static_cast<size_t>(PROTOCOL_HEAD_SIZE));
		char* body_memory = (char*)m_memory;
		// copy message id to memory
		memcpy(body_memory, m_message_size, sizeof(MESSAGE_SIZE));
		body_memory += sizeof(MESSAGE_SIZE);
        memcpy(body_memory, m_message_id, sizeof(MESSAGE_ID));
        body_memory += sizeof(MESSAGE_ID);
        memcpy(body_memory, m_message_rpc_id, sizeof(MESSAGE_RPCID));
        body_memory += sizeof(MESSAGE_RPCID);

		// if message size == 0 then read completed
		if (*m_message_size == 0)
			ReadComplete();
		
		return true;
	}

	// if receive failed, then reset status and return
	int max_len = (int)(*m_message_size);
	int recv_len = NetHelper::TCPSocketReceive(m_socket, (char*)m_memory + PROTOCOL_HEAD_SIZE, max_len);
	if (recv_len < max_len)
	{
		Clear();
		if (strlen(SDLNet_GetError()) > 0) ALITTLE_ERROR(SDLNet_GetError());
		return false;
	}

	ReadComplete();

	return true;
}

void MessageReceiver::ReadComplete()
{
	// push message
	++ m_net_system->m_netsystem_filter_push;
	g_ScheduleSystem.PushUserEvent(NET_MESSAGE, (void*)m_net_system, m_memory);

	// reset param
	*m_message_id = 0;
    *m_message_rpc_id = 0;
	*m_message_size = 0;
	m_receive_head = true;
	m_memory = 0;
}

} // ALittle