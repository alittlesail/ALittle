#ifndef ALITTLE_SCHEDULE_INCLUDED
#define ALITTLE_SCHEDULE_INCLUDED (1)

#include "Carp/carp_log.hpp"
#include "Carp/carp_task_consumer.hpp"
#include "Carp/carp_schedule.hpp"

#include "ALittle/LibClient/alittle_script.hpp"
#include "ALittle/LibClient/alittle_audio.hpp"
#include "ALittle/LibClient/alittle_net.hpp"
#include "ALittle/LibClient/alittle_csv.hpp"
#include "alittle_surface.hpp"
#include "alittle_system.hpp"

#include "alittle_displayobject.hpp"
#include "alittle_displayobjects.hpp"
#include "alittle_display.hpp"
#include "alittle_displayview.hpp"
#include "alittle_render.hpp"

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

#ifndef __EMSCRIPTEN__
		CarpFile::CreateDeepFolder(CarpRWops::ExternalFilePath() + "Log");
		s_carp_log.Setup(CarpRWops::ExternalFilePath() + "Log/", "ALittleClient");
#endif
		
		// 初始化日志系统
		CARP_INFO("==>ScheduleSystem Setup Begin<==");

#ifdef _WIN32
		s_carp_console.Setup("ALittleClient", std::bind(&ALittleSchedule::PushConsoleEvent, this, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&ALittleSchedule::Exit, this), std::bind(&ALittleSchedule::PushConsoleHelp, this));
#endif

		// init net system
		s_carp_schedule.Run(true);
		// init task system
		s_carp_task_consumer.SetThreadCount(1);
		
		s_alittle_render.Setup();			// render system
		s_alittle_audio.Setup();			// audio system
		s_alittle_script.Setup();			// script system

		// register to script
		s_alittle_render.Bind(s_alittle_script.GetLuaState());
		s_alittle_audio.Bind(s_alittle_script.GetLuaState());
		ALittleNet::Bind(s_alittle_script.GetLuaState());
		ALittleCsv::Bind(s_alittle_script.GetLuaState());
		ALittleSurface::Bind(s_alittle_script.GetLuaState());
		ALittleSystem::Bind(s_alittle_script.GetLuaState());

		s_alittle_display.Bind(s_alittle_script.GetLuaState());
		ALittleDisplayObject::Bind(s_alittle_script.GetLuaState());
		ALittleDisplayObjects::Bind(s_alittle_script.GetLuaState());
		ALittleDisplayView::Bind(s_alittle_script.GetLuaState());

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
		s_alittle_render.Render();
	}

	void Shutdown()
	{
		s_alittle_audio.Shutdown();
		s_alittle_display.Shutdown();
		s_alittle_render.Shutdown();
		
		s_alittle_script.Shutdown();
#ifdef _WIN32
		s_carp_console.Shutdown();
#endif

		s_carp_log.Shutdown();

		// set dump info
#ifdef _WIN32
		s_carp_dump.Shutdown();
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

