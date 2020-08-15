
#include "ReceiveThread.h"

#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/Tool/MemoryPool.h"
#include "ALittle/LibCommon/Helper/LogHelper.h"

#include "MessageReceiver.h"

namespace ALittle
{

ReceiveThread::ReceiveThread(NetSystem* net_system, TCPsocket socket)
: m_net_system(net_system), m_socket(socket)
{
	// create thread
	m_thread = SDL_CreateThread(ReceiveThread::Run, NULL, (void*)this);
}

ReceiveThread::~ReceiveThread()
{
	// wait for thread completed
	SDL_WaitThread(m_thread, 0);
}

int ReceiveThread::Run(void* data)
{
	ALITTLE_INFO("tcp receive thread begin");
	// get self
	ReceiveThread* self = (ReceiveThread*)data;

	// receiver
	MessageReceiver receiver(self->m_net_system, self->m_socket);
	
	// receive message 
	while(receiver.Run());

	// send socket disconnect
	g_ScheduleSystem.PushUserEvent(NET_DISCONNECT, (void*)self->m_net_system);

	ALITTLE_INFO("tcp receive thread end");
	return 0;
}

} // Sail