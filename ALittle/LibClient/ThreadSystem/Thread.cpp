
#include "Thread.h"

#include "Task.h"
#include "ThreadSystem.h"

#include <iostream>
#include <time.h>

namespace ALittle
{

Thread::Thread(ThreadGroup* group)
{
	// set thread group
	m_group = group;
	// flag to run
	m_run = true;
	// default not to auto release
	m_auto_release = false;
	// create sem
	m_sem = SDL_CreateSemaphore(0);
	// create thread
	m_thread = SDL_CreateThread(Thread::Run, NULL, (void*)this);
}

Thread::~Thread()
{
	// flag to stop
	m_run = false;

	if (m_thread)
	{
		// notify to continue
		if (m_sem) SDL_SemPost(m_sem);

		// wait thread complete
		SDL_WaitThread(m_thread, 0);
		m_thread = 0;
	}

	if (m_sem)
	{
		// release sem
		SDL_DestroySemaphore(m_sem);
		m_sem = 0;
	}
}

int Thread::Run(void* data)
{
	// get self
	Thread* self = (Thread*)data;

	while(self->m_run)
	{
		// wait for tasks
		SDL_SemWait(self->m_sem);

		// define task pointer
		Task* task = 0;

		// execute all list
		while (self->m_group->m_task_list.try_dequeue(task))
			task->Execute();
	}

	// check auto realse or not
	if (self->m_auto_release)
	{
		delete self;
		self = 0;
	}

	return 0;
}

void Thread::InvokeTask()
{
	SDL_SemPost(m_sem);
}

void Thread::AutoRelease()
{
	// flag to stop and auto realse
	m_auto_release = true;
	m_run = false;

	// notify to continue
	SDL_SemPost(m_sem);

	// detach thread
	SDL_DetachThread(m_thread);
	m_thread = 0;
}

} // ALittle
