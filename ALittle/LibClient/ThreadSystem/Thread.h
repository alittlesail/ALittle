
#ifndef _ALITTLE_THREAD_H_
#define _ALITTLE_THREAD_H_

#include <list>

#include <SDL.h>
#include <SDL_thread.h>

namespace ALittle
{

class ThreadGroup;

class Thread
{
public:
	Thread(ThreadGroup* group);
	~Thread();

public:
	static int Run(void* data);

public:
	/*
	 * add task to execute
	 */
	void InvokeTask();

public:
	/**
	 * it can auto release self after execute
	 */
	void AutoRelease();

private:
	SDL_sem* m_sem;							// lock

private:
	bool m_run;				// flag to run
	bool m_auto_release;	// auto release or not
	SDL_Thread* m_thread;	// thread

private:
	ThreadGroup* m_group;
};

} // ALittle

#endif // _ALITTLE_THREAD_H_
