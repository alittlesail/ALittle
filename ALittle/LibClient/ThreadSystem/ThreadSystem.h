
#ifndef _ALITTLE_THREADSYSTEM_H_
#define _ALITTLE_THREADSYSTEM_H_

#include <vector>

#include "Thread.h"
#include "Task.h"
#include "ALittle/LibClient/Tool/concurrentqueue.h"

namespace ALittle
{

class Task;
class ScriptSystem;

class ThreadSystem
{
public:
	static ThreadSystem& Instance();

	friend class Thread;

public:
	void Setup();
	void Shutdown();
	void RegisterToScript(ScriptSystem& script_system);

public:
	/**
	 * set thread count
	 * @param count: count of thread
	 * @return succeed or not
	 */
	bool SetThreadCount(unsigned int count);

	/**
	 * get thread count
	 * @return count of thread
	 */
	unsigned int GetThreadCount() const;
	
public:
	/**
	 * add task to list
	 * @param task: task object
	 * @return succeed or not
	 */
	bool AddTask(Task* task);

private:
	std::vector<Thread*> m_thread_list;		// thread list
	moodycamel::ConcurrentQueue<Task*> m_task_list;		// task list

private:
	ThreadSystem();
	~ThreadSystem();
};

} // ALittle

#define g_ThreadSystem ALittle::ThreadSystem::Instance()

#endif // _ALITTLE_THREADSYSTEM_H_
