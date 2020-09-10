
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

class ThreadGroup
{
public:
	ThreadGroup();
	~ThreadGroup();

public:
	/**
	 * clear all thread
	 */
	void Clear();
	
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
	unsigned int GetThreadCount();
	
public:
	/**
	 * add task to list
	 * @param task: task object
	 * @param thread_type: 0 false, 1 middle, 2 slow
	 * @return succeed or not
	 */
	bool AddTask(Task* task);

public:
	std::vector<Thread*> m_thread_list;		// thread list
	moodycamel::ConcurrentQueue<Task*> m_task_list;		// task list
};

class ThreadSystem
{
public:
	static ThreadSystem& Instance();

public:
	void Setup();
	void Shutdown();
	void RegisterToScript(ScriptSystem& script_system);

public:
	enum ThreadType
	{
		THREAD_TYPE_FAST = 0,
		THREAD_TYPE_MIDDLE = 1,
		THREAD_TYPE_SLOW = 2
	};

public:
	/**
	 * set thread count
	 * @param count: count of thread
	 * @param thread_type: 0 false, 1 middle, 2 slow
	 * @return succeed or not
	 */
	bool SetThreadCount(unsigned int count, int thread_type);

	/**
	 * get thread count
	 * @param thread_type: 0 false, 1 middle, 2 slow
	 * @return count of thread
	 */
	unsigned int GetThreadCount(int thread_type);
	
public:
	/**
	 * add task to list
	 * @param task: task object
	 * @param thread_type: 0 false, 1 middle, 2 slow
	 * @return succeed or not
	 */
	bool AddTask(Task* task, int thread_type);

private:
	ThreadGroup& GetThreadList(int thread_type)
	{
		if (thread_type == THREAD_TYPE_FAST) return m_fast_group;
		if (thread_type == THREAD_TYPE_MIDDLE) return m_middle_group;
		return m_slow_group;
	}
	
private:
	ThreadGroup m_fast_group;
	ThreadGroup m_middle_group;
	ThreadGroup m_slow_group;

private:
	ThreadSystem();
	~ThreadSystem();
};

} // ALittle

#define g_ThreadSystem ALittle::ThreadSystem::Instance()

#endif // _ALITTLE_THREADSYSTEM_H_
