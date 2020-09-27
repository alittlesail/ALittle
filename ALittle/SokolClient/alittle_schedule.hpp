#ifndef ALITTLE_SCHEDULE_INCLUDED
#define ALITTLE_SCHEDULE_INCLUDED (1)

#include "Carp/carp_log.hpp"
#include "Carp/carp_task_consumer.hpp"
#include "Carp/carp_schedule.hpp"

#include "alittle_script.hpp"
#include "alittle_audio.hpp"
#include "alittle_net.hpp"
#include "alittle_csv.hpp"
#include "alittle_surface.hpp"

#include "sokol/sokol_app.h"

class ALittleSchedule
{
public:
	void SetArgs(int argc, char* argv[])
	{
		for (int i = 0; i < argc; ++i)
			m_args.emplace_back(argv[i]);
	}
	
	void Setup()
	{
#ifdef _WIN32
		s_carp_dump.Setup("ALittleClient", []() { s_carp_log.Shutdown(); });
#endif

		// 初始化日志系统
		CARP_INFO("==>ScheduleSystem Setup Begin<==");

#ifndef __EMSCRIPTEN__
		CarpFile::CreateDeepFolder(CarpRWops::ExternalFilePath() + "Log");
		s_carp_log.Setup(CarpRWops::ExternalFilePath() + "Log/", "ALittleClient");
#endif
#ifdef _WIN32
		s_carp_console.Setup("ALittleClient", std::bind(&ALittleSchedule::PushConsoleEvent, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&ALittleSchedule::Exit, this), std::bind(&ALittleSchedule::PushConsoleHelp, this));
#endif

		// init net system
		s_carp_schedule.Run(true);
		// init task system
		s_carp_task_consumer.SetThreadCount(1);
		
		// g_RenderSystem.Setup();			// render system
		s_alittle_audio.Setup();			// audio system
		s_alittle_script.Setup();			// script system

		// register to script
		// RegisterToScript(g_ScriptSystem);
		// g_RenderSystem.RegisterToScript(g_ScriptSystem);
		s_alittle_audio.Bind(s_alittle_script.GetLuaState());
		ALittleNet::Bind(s_alittle_script.GetLuaState());
		ALittleCsv::Bind(s_alittle_script.GetLuaState());
		ALittleSurface::Bind(s_alittle_script.GetLuaState());

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
#ifdef _WIN32
		s_carp_console.Shutdown();
#endif

		s_carp_log.Shutdown();

		// set dump info
#ifdef _WIN32
		s_carp_dump.Shutdown();
#endif
#if (defined __ANDROID__) || (defined __IPHONEOS__)
		exit(0);
#endif
	}

	void Exit()
	{
		sapp_quit();
	}

private:
	void PushConsoleHelp()
	{
		CARP_INFO(u8"模块列表:Client");
	}

	void PushConsoleEvent(const std::string& module, const std::string& cmd)
	{
		s_carp_task_consumer.PushEvent([module, cmd]()
		{
			if (module == "Client")
			{
				s_alittle_script.Invoke("__ALITTLEAPI_HandleConsoleCmd", cmd.c_str());
			}
		});
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

