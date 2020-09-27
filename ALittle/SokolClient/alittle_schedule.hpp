#ifndef ALITTLE_SCHEDULE_INCLUDED
#define ALITTLE_SCHEDULE_INCLUDED (1)

#include "Carp/carp_log.hpp"
#include "Carp/carp_task_consumer.hpp"

#include "alittle_script.hpp"
#include "alittle_audio.hpp"

class ALittleSchedule
{
public:
	void SetArgs(int argc, char* argv[])
	{
		for (int i = 0; i < argc; ++i)
			m_args.push_back(argv[i]);
	}
	
	void Setup()
	{
		// 初始化日志系统
		CARP_INFO("==>ScheduleSystem Setup Begin<==");
		
		// set up instance
		s_carp_task_consumer.SetThreadCount(1);
		// g_RenderSystem.Setup();			// render system
		s_alittle_audio.Setup();			// audio system
		// NetSystem::Setup();				// net system
		s_alittle_script.Setup();			// script system

		// register to script
		// RegisterToScript(g_ScriptSystem);
		// g_RenderSystem.RegisterToScript(g_ScriptSystem);
		s_alittle_audio.Bind(s_alittle_script.GetLuaState());
		// NetSystem::RegisterToScript(g_ScriptSystem);

		// load engine
		CARP_INFO("==>ScheduleSystem Lua Init Begin<==");
		std::string main_path;
		if (m_args.size() >= 2) main_path = m_args[1];
		std::string debug_info;
		if (m_args.size() >= 3) debug_info = m_args[2];
		s_alittle_script.StartScript(main_path, debug_info);
		CARP_INFO("==>ScheduleSystem Lua Init Completed<==");
		m_has_updater = s_alittle_script.IsFunction("__ALITTLEAPI_Update");
		if (!m_has_updater) CARP_ERROR("can't find __ALITTLEAPI_Update in _G");
		CARP_INFO("==>ScheduleSystem Setup Completed<==");
	}

	void Update()
	{
		s_carp_task_consumer.HandleEvent();
	}

	void Shutdown()
	{
		
	}

private:
	std::vector<std::string> m_args;
	bool m_has_updater = false;
};

extern ALittleSchedule s_alittle_schedule;

#endif


#ifdef ALITTLE_SCHEDULE_IMPL
ALittleSchedule s_alittle_schedule;
#endif

