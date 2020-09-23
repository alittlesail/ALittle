#ifndef ALITTLE_SCHEDULE_INCLUDED
#define ALITTLE_SCHEDULE_INCLUDED (1)

#include "Carp/carp_log.hpp"

class ALittleSchedule
{
public:
	void Setup()
	{
		// 初始化日志系统
		CARP_INFO("==>ScheduleSystem Setup Begin<==");

		// set up instance
		g_ThreadSystem.Setup();			// thread system
		g_RenderSystem.Setup();			// render system
		g_AudioSystem.Setup();			// audio system
		NetSystem::Setup();				// net system
		g_ScriptSystem.Setup();			// script system

		// register to script
		RegisterToScript(g_ScriptSystem);
		g_ThreadSystem.RegisterToScript(g_ScriptSystem);
		g_RenderSystem.RegisterToScript(g_ScriptSystem);
		g_AudioSystem.RegisterToScript(g_ScriptSystem);
		NetSystem::RegisterToScript(g_ScriptSystem);

		// load engine
		CARP_INFO("==>ScheduleSystem Lua Init Begin<==");
		std::string main_path;
		if (argc >= 2) main_path = argv[1];
		std::string debug_info;
		if (argc >= 3) debug_info = argv[2];
		g_ScriptSystem.StartScript(main_path, debug_info);
		CARP_INFO("==>ScheduleSystem Lua Init Completed<==");
		m_has_updater = g_ScriptSystem.IsFunction("__ALITTLEAPI_Update");
		if (!m_has_updater) CARP_ERROR("can't find __ALITTLEAPI_Update in _G");
		CARP_INFO("==>ScheduleSystem Setup Completed<==");
	}

	void Update()
	{
		
	}

	void Shutdown()
	{
		
	}
};

#endif