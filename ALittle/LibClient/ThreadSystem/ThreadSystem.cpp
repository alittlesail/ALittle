
#include "ThreadSystem.h"
#include "Task.h"
#include "ALittle/LibCommon/ScriptSystem/ScriptSystem.h"

namespace ALittle
{

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
	SetThreadCount(1);
#endif
}

void ThreadSystem::Shutdown()
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

bool ThreadSystem::AddTask(Task* task)
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

bool ThreadSystem::SetThreadCount(unsigned int count)
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
			m_thread_list.push_back(new Thread());
			--append_count;
		}
		return true;
	}

	// if count < current count, then remove
	int remove_count = (int)m_thread_list.size() - (int)count;
	while (remove_count)
	{
		m_thread_list.back()->AutoRelease();
		m_thread_list.pop_back();
		--remove_count;
	}

	return true;
#endif
}

unsigned int ThreadSystem::GetThreadCount() const
{
	return static_cast<unsigned int>(m_thread_list.size());
}

} // ALittle
