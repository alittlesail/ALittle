#ifndef ALITTLE_SCHEDULE_INCLUDED
#define ALITTLE_SCHEDULE_INCLUDED

#include "Carp/carp_log.hpp"
#include "Carp/carp_task_consumer.hpp"
#include "Carp/carp_schedule.hpp"
#include "Carp/carp_system.h"

#include "ALittle/ALittleClient/alittle_script.hpp"
#include "ALittle/ALittleClient/alittle_audio.hpp"
#include "ALittle/ALittleClient/alittle_net.hpp"
#include "ALittle/ALittleClient/alittle_csv.hpp"
#include "Carp/carp_surface.hpp"
#include "alittle_render.hpp"

#include "sokol/sokol_app.h"

class ALittleSchedule
{
public:
	void SetArgs(int argc, char* argv[])
	{
		for (int i = 0; i < argc; ++i)
			m_args.emplace_back(argv[i]);


		// set dump info
#ifdef _WIN32
		s_carp_dump.Setup("ALittleClient", []() { s_carp_log.Shutdown(); });
#endif

#ifndef __EMSCRIPTEN__
		CarpFile::CreateDeepFolder(CarpRWops::ExternalFilePath() + "Log");
		s_carp_log.Setup(CarpRWops::ExternalFilePath() + "Log/", "ALittleClient");
#endif
#ifdef _WIN32
		s_carp_console.Setup("ALittleClient", std::bind(ALittleSchedule::PushConsoleEvent, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&ALittleSchedule::Exit, this), ALittleSchedule::PushConsoleHelp);
#endif

		// print current platform
		CARP_INFO("current platform is " << Carp_GetPlatform());
	}
	
	void Setup()
	{
		// 初始化日志系统
		CARP_INFO("==>ScheduleSystem Setup Begin<==");

		// set up instance
		s_carp_task_consumer.SetThreadCount(1);
		s_alittle_render.Setup();			// render system
		s_alittle_display.Setup();
		s_alittle_audio.Setup();			// audio system
		s_alittle_script.Setup();			// script system
		s_carp_schedule.Run(true);

		// register to script
		Bind(s_alittle_script.GetLuaState());
		s_alittle_input.Bind(s_alittle_script.GetLuaState());
		s_alittle_display.Bind(s_alittle_script.GetLuaState());
		ALittleDisplayObject::Bind(s_alittle_script.GetLuaState());
		ALittleDisplayObjects::Bind(s_alittle_script.GetLuaState());
		ALittleDisplayView::Bind(s_alittle_script.GetLuaState());
		ALittleImage::Bind(s_alittle_script.GetLuaState());
		ALittleQuad::Bind(s_alittle_script.GetLuaState());
		ALittleSprite::Bind(s_alittle_script.GetLuaState());
		ALittleTriangle::Bind(s_alittle_script.GetLuaState());
		ALittleGrid9Image::Bind(s_alittle_script.GetLuaState());
		ALittleText::Bind(s_alittle_script.GetLuaState());
		ALittleTextArea::Bind(s_alittle_script.GetLuaState());
		ALittleTextInput::Bind(s_alittle_script.GetLuaState());
		ALittleTextEdit::Bind(s_alittle_script.GetLuaState());
		ALittleTextureBind::Bind(s_alittle_script.GetLuaState());
		/// ALittleSurface::Bind(s_alittle_script.GetLuaState());
		s_alittle_system.Bind(s_alittle_script.GetLuaState());
		s_alittle_render.Bind(s_alittle_script.GetLuaState());
		s_alittle_audio.Bind(s_alittle_script.GetLuaState());
		ALittleCsv::Bind(s_alittle_script.GetLuaState());
		ALittleNet::Bind(s_alittle_script.GetLuaState());

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

	void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			.beginClass<ALittleSchedule>("__CPPAPIScheduleSystem")
			.addFunction("Exit", &ALittleSchedule::Exit)
			.addFunction("ForceExit", &ALittleSchedule::ForceExit)
			.addFunction("Restart", &ALittleSchedule::Restart)
			.endClass();

		luabridge::setGlobal(l_state, this, "__CPPAPI_ScheduleSystem");
	}

	static void PushConsoleHelp()
	{
		CARP_INFO(u8"module list:Client");
	}

	static void PushConsoleEvent(const std::string& module, const std::string& cmd)
	{
		s_carp_task_consumer.PushEvent([module, cmd]()
		{
			if (module == "Client")
			{
				s_alittle_script.Invoke("__ALITTLEAPI_HandleConsoleCmd", cmd.c_str());
			}
		});
	}

	/**
	 * handle all event
	 * @param event: SDL event object
	 * @return continue or not
	 */
	bool HandleEvent(const sapp_event& event)
	{
		if (event.type == SDL_QUIT) return false;

		// handle windows event
		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				s_alittle_render.HandleViewResized((unsigned int)event.window.data1, (unsigned int)event.window.data2);
			else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED || event.window.event == SDL_WINDOWEVENT_HIDDEN)
				s_alittle_render.HandleMinViewSize();
			else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
				s_alittle_render.HandleMaxViewSize();
			else if (event.window.event == SDL_WINDOWEVENT_RESTORED || event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
				s_alittle_render.HandleRestoreViewSize();
			else if (event.window.event == SDL_WINDOWEVENT_ENTER)
				s_alittle_script.Invoke("__ALITTLEAPI_WindowEnter");
			else if (event.window.event == SDL_WINDOWEVENT_LEAVE)
				s_alittle_script.Invoke("__ALITTLEAPI_WindowLeave");

			return true;
		}

		// handle drop file event
		if (event.type == SDL_DROPFILE)
		{
			s_alittle_script.Invoke("__ALITTLEAPI_DropFile", (const char*)event.drop.file);
			SDL_free(event.drop.file);
			return true;
		}
#if !(defined __ANDROID__) && !(defined __IPHONEOS__) // because IOS/Android open SDL_WINDOW_ALLOW_HIGHDPI,mouse and finger both send message. and mouse's pos is wrong. so not handle mouse
		// handle mouse event
		else if (event.type == SDL_MOUSEMOTION)
		{
			s_alittle_script.Invoke("__ALITTLEAPI_MouseMoved", event.motion.x, event.motion.y);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (event.button.button)
			{
			case 1: s_alittle_script.Invoke("__ALITTLEAPI_LButtonDown", event.button.x, event.button.y, event.button.clicks); break;
			case 2: s_alittle_script.Invoke("__ALITTLEAPI_MButtonDown", event.button.x, event.button.y, event.button.clicks); break;
			case 3: s_alittle_script.Invoke("__ALITTLEAPI_RButtonDown", event.button.x, event.button.y, event.button.clicks); break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			switch (event.button.button)
			{
			case 1: s_alittle_script.Invoke("__ALITTLEAPI_LButtonUp", event.button.x, event.button.y); break;
			case 2: s_alittle_script.Invoke("__ALITTLEAPI_MButtonUp", event.button.x, event.button.y); break;
			case 3: s_alittle_script.Invoke("__ALITTLEAPI_RButtonUp", event.button.x, event.button.y); break;
			}
		}
		else if (event.type == SDL_MOUSEWHEEL)
			s_alittle_script.Invoke("__ALITTLEAPI_MouseWheel", event.wheel.x, event.wheel.y);
#endif // !__IPHONEOS__/__ANDROID__

		// handle keyboard event
		else if (event.type == SDL_KEYDOWN)
			s_alittle_script.Invoke("__ALITTLEAPI_KeyDown"
				, static_cast<int>(event.key.keysym.mod)
				, static_cast<int>(event.key.keysym.sym)
				, static_cast<int>(event.key.keysym.scancode));
		else if (event.type == SDL_KEYUP)
			s_alittle_script.Invoke("__ALITTLEAPI_KeyUp"
				, static_cast<int>(event.key.keysym.mod)
				, static_cast<int>(event.key.keysym.sym)
				, static_cast<int>(event.key.keysym.scancode));
		else if (event.type == SDL_TEXTINPUT)
			s_alittle_script.Invoke("__ALITTLEAPI_TextInput", event.text.text);
		else if (event.type == SDL_TEXTEDITING)
			s_alittle_script.Invoke("__ALITTLEAPI_TextEditing", event.edit.text, event.edit.start);

		// handle touch event
		else if (event.type == SDL_FINGERDOWN)
			s_alittle_script.Invoke("__ALITTLEAPI_FingerDown"
				, s_alittle_render.CalcFingerX(event.tfinger.x)
				, s_alittle_render.CalcFingerY(event.tfinger.y)
				, static_cast<int>(event.tfinger.fingerId)
				, static_cast<int>(event.tfinger.touchId));
		else if (event.type == SDL_FINGERUP)
			s_alittle_script.Invoke("__ALITTLEAPI_FingerUp"
				, s_alittle_render.CalcFingerX(event.tfinger.x)
				, s_alittle_render.CalcFingerY(event.tfinger.y)
				, static_cast<int>(event.tfinger.fingerId)
				, static_cast<int>(event.tfinger.touchId));
		else if (event.type == SDL_FINGERMOTION)
			s_alittle_script.Invoke("__ALITTLEAPI_FingerMoved"
				, s_alittle_render.CalcFingerX(event.tfinger.x)
				, s_alittle_render.CalcFingerY(event.tfinger.y)
				, static_cast<int>(event.tfinger.fingerId)
				, static_cast<int>(event.tfinger.touchId));


		else if (event.type == SDL_APP_WILLENTERBACKGROUND)
			s_alittle_script.Invoke("__ALITTLEAPI_WillEnterBackground");
		else if (event.type == SDL_APP_WILLENTERFOREGROUND)
			s_alittle_script.Invoke("__ALITTLEAPI_WillEnterForeground");
		// handle app go to background
		else if (event.type == SDL_APP_DIDENTERBACKGROUND)
		{
			m_app_pause = true;
			s_alittle_script.Invoke("__ALITTLEAPI_DidEnterBackground");
		}
		else if (event.type == SDL_APP_DIDENTERFOREGROUND)
		{
			m_app_pause = false;
			s_alittle_script.Invoke("__ALITTLEAPI_DidEnterForeground");
			// just release SDL_WaitEvent
			SDL_Event event = { 0 };
			event.type = SDL_USEREVENT;
			SDL_PushEvent(&event);
		}

		// handle device reset
		else if (event.type == SDL_RENDER_DEVICE_RESET)
			s_alittle_render.HandleDeviceReset();
		else if (event.type == SDL_APP_LOWMEMORY)
			s_alittle_script.Invoke("__ALITTLEAPI_LowMemory");

		return true;
	}

public:
	/**
	 * render action
	 */
	void Render()
	{
		s_carp_task_consumer.HandleEvent();

		// update script logic
		if (m_has_updater)
		{
			time_t cur_time = CarpTime::GetCurMSTime();
			if (m_last_time > 0)
				s_alittle_script.Invoke("__ALITTLEAPI_Update", cur_time - m_last_time);
			m_last_time = cur_time;
		}

		// render for interval
		s_alittle_render.Render();
	}

	void ForceExit()
	{
		exit(0);
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
	std::vector<std::string> m_args;
	bool m_has_updater = false;

	time_t m_last_time = 0;
};

extern ALittleSchedule s_alittle_schedule;

#endif


#ifdef ALITTLE_SCHEDULE_IMPL
ALittleSchedule s_alittle_schedule;
#endif

