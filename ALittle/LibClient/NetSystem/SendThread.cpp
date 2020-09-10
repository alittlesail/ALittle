
#include "SendThread.h"

#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/Tool/MemoryPool.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

namespace ALittle
{

SendThread::SendThread(TCPsocket socket)
{
	// create sem
	m_sem = SDL_CreateSemaphore(0);
	// save socket
	m_socket = socket;
	// falg to run
	m_run = true;
	// create thread
	m_thread = SDL_CreateThread(SendThread::Run, NULL, (void*)this);
}

SendThread::~SendThread()
{
	// flag to stop
	m_run = false;

	if (m_thread)
	{
		// notify to continue
		if (m_sem) SDL_SemPost(m_sem);
		
		// wait for thread completed
		SDL_WaitThread(m_thread, 0);
		m_thread = 0;
	}

	// delete sem
	if (m_sem)
	{
		SDL_DestroySemaphore(m_sem);
		m_sem = 0;
	}

	// release 
	void* body_memory = 0;
	while (m_list.try_dequeue(body_memory))
		g_MemoryPoolGroup.Release(body_memory);
}

void SendThread::Send( const Message& message )
{
	// get message total size
	MESSAGE_SIZE size = message.GetTotalSize();
	// get message id
	MESSAGE_ID id = message.GetID();
    // get message rpc id
    MESSAGE_RPCID rpc_id = message.GetRpcID();

	// total size = message size + PROTOCOL_HEAD_SIZE
	unsigned int extend_size = size + PROTOCOL_HEAD_SIZE;

	// create memory
	void* memory = g_MemoryPoolGroup.Create(extend_size);
	char* body_memory = (char*)memory;
	// set body memeory
	memcpy(body_memory, &size, sizeof(MESSAGE_SIZE));
	body_memory += sizeof(MESSAGE_SIZE);
	memcpy(body_memory, &id, sizeof(MESSAGE_ID));
    body_memory += sizeof(MESSAGE_ID);
    memcpy(body_memory, &rpc_id, sizeof(MESSAGE_RPCID));
    body_memory += sizeof(MESSAGE_RPCID);

	// serialize
	message.Serialize(body_memory);

	// add to list
	m_list.enqueue(memory);
	SDL_SemPost(m_sem);
}

int SendThread::Run(void* data)
{
	ALITTLE_INFO("tcp send thread begin");
	// get self
	SendThread* self = (SendThread*)data;

	while (self->m_run)
	{
		SDL_SemWait(self->m_sem);

		void* memory = 0;
		while (self->m_list.try_dequeue(memory))
		{
			char* body_memory = (char*)memory;
			// get memory
			MESSAGE_SIZE message_size = 0;
			memcpy(&message_size, body_memory, sizeof(MESSAGE_SIZE));
			// get message size
			unsigned int extend_size = message_size + PROTOCOL_HEAD_SIZE;
			// send message
			if (NetHelper::TCPSocketSend(self->m_socket, body_memory, extend_size) < (int)extend_size)
			{
				ALITTLE_INFO(SDLNet_GetError());
				// close socket
				SDLNet_TCP_JustClose(self->m_socket);
			}
			// release memory
			g_MemoryPoolGroup.Release(memory);
		}
	}

	ALITTLE_INFO("tcp send thread end");

	return 0;
}

} // ALittle