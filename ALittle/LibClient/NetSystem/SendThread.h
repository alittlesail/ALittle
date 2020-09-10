
#ifndef _ALITTLE_SENDTHREAD_H_
#define _ALITTLE_SENDTHREAD_H_

#include <SDL.h>
#include "ALittle/LibClient/Helper/NetHelper.h"
#include "ALittle/LibClient/Tool/concurrentqueue.h"

#include "ALittle/LibCommon/Protocol/Message.h"

namespace ALittle
{

class SendThread
{
public:
	SendThread(TCPsocket socket);
	~SendThread();

public:
	/**
	 * thread runner
	 */
	static int Run(void* data);

public:
	/**
	 * send message
	 * @param message object
	 */
	void Send(const Message& message);

private:
	TCPsocket m_socket;		// TCP socket
	bool m_run;				// run or not
	SDL_Thread* m_thread;	// thread
	
private:
	SDL_sem* m_sem;					// lock
	moodycamel::ConcurrentQueue<void*> m_list;	// list
};

} // ALittle

#endif // _ALITTLE_SENDTHREAD_H_