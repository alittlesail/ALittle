
#ifndef _ALITTLE_RECEIVETHREAD_H_
#define _ALITTLE_RECEIVETHREAD_H_

#include <list>

#include <SDL.h>

#include "ALittle/LibClient/Helper/NetHelper.h"

namespace ALittle
{

class NetSystem;

class ReceiveThread
{
public:
	ReceiveThread(NetSystem* net_system, TCPsocket socket);
	~ReceiveThread();

public:
	static int Run(void* data);

private:
	NetSystem* m_net_system;	// net system
	SDL_Thread* m_thread;		// thread
	TCPsocket m_socket;			// TCP socket
};

} // ALittle

#endif // _ALITTLE_RECEIVETHREAD_H_