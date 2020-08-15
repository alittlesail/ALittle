
#include "ThreadSystem.h"
#include "Task.h"
#include "ALittle/LibCommon/ScriptSystem/ScriptSystem.h"

namespace ALittle
{

ThreadGroup::ThreadGroup()
{

}

ThreadGroup::~ThreadGroup()
{
	Clear();
}

void ThreadGroup::Clear()
{
	// release all thread
	for (unsigned int i = 0; i < m_thread_list.size(); ++i)
		delete m_thread_list[i];

	// clear list
	m_thread_list.clear();

	Task* task;
	while (m_task_list.try_dequeue(task))
		task->Execute();
}

bool ThreadGroup::SetThreadCount(unsigned int count)
{
#ifdef __EMSCRIPTEN__
	return false;
#else
	// count must >= 1
	if (count < 1 || count == m_thread_list.size()) return false;

	// if count > current count, then create
	if (count > m_thread_list.size())
	{
		int append_count = (int)count - (int)m_thread_list.size();
		while (append_count > 0)
		{
			m_thread_list.push_back(new Thread(this));
			-- append_count;
		}
		return true;
	}

	// if count < current count, then remove
	int remove_count = (int)m_thread_list.size() - (int)count;
	while(remove_count)
	{
		m_thread_list.back()->AutoRelease();
		m_thread_list.pop_back();
		-- remove_count;
	}

	return true;
#endif
}

unsigned int ThreadGroup::GetThreadCount()
{
	return static_cast<unsigned int>(m_thread_list.size());
}

bool ThreadGroup::AddTask(Task* task)
{
	// check task ptr
	if (!task) return false;

	// if thread count is 0 then execute task
	if (m_thread_list.size() == 0)
	{
		task->Execute();
		return true;
	}

	// add to task list
	m_task_list.enqueue(task);

	// add to list
	for (unsigned int i = 0; i < m_thread_list.size(); ++i)
		m_thread_list[i]->InvokeTask();

	return true;
}

ThreadSystem::ThreadSystem() { }
ThreadSystem::~ThreadSystem() { }

ThreadSystem& ThreadSystem::Instance()
{
	static ThreadSystem instance;
	return instance;
}

void ThreadSystem::Setup()
{
#ifndef __EMSCRIPTEN__
	SetThreadCount(1, THREAD_TYPE_FAST);
	SetThreadCount(1, THREAD_TYPE_MIDDLE);
	SetThreadCount(1, THREAD_TYPE_SLOW);
#endif
}

void ThreadSystem::Shutdown()
{
	m_fast_group.Clear();
	m_middle_group.Clear();
	m_slow_group.Clear();
}

void ThreadSystem::RegisterToScript(ScriptSystem& script_system)
{
	lua_State* L = script_system.GetLuaState();

	luabridge::getGlobalNamespace(L)
		.beginClass<ThreadSystem>("__CPPAPIThreadSystem")
		.addFunction("SetThreadCount", &ThreadSystem::SetThreadCount)
		.addFunction("GetThreadCount", &ThreadSystem::GetThreadCount)
		.endClass();

	luabridge::setGlobal(L, this, "__CPPAPI_ThreadSystem");
}

bool ThreadSystem::AddTask(Task* task, int thread_type)
{
	return GetThreadList(thread_type).AddTask(task);
}

bool ThreadSystem::SetThreadCount(unsigned int count, int thread_type)
{
	if (thread_type == THREAD_TYPE_FAST)
		return m_fast_group.SetThreadCount(count);
	if (thread_type == THREAD_TYPE_MIDDLE)
		return m_middle_group.SetThreadCount(count);
	return m_slow_group.SetThreadCount(count);
}

unsigned int ThreadSystem::GetThreadCount(int thread_type)
{
	return GetThreadList(thread_type).GetThreadCount();
}

} // ALittle
