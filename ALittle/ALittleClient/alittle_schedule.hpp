#ifndef ALITTLE_SCHEDULE_INCLUDED
#define ALITTLE_SCHEDULE_INCLUDED

#include <string>

#include "alittle_csv.hpp"
#include "alittle_net.hpp"
#include "alittle_audio.hpp"
#include "alittle_display.hpp"
#include "alittle_displayview.hpp"
#include "alittle_grid9image.hpp"
#include "alittle_image.hpp"
#include "alittle_render.hpp"
#include "alittle_input.hpp"
#include "alittle_quad.hpp"
#include "alittle_sprite.hpp"
#include "alittle_system.hpp"
#include "alittle_text.hpp"
#include "alittle_textarea.hpp"
#include "alittle_textedit.hpp"
#include "alittle_textinput.hpp"
#include "alittle_triangle.hpp"
#include "alittle_verteximage.hpp"
#include "Carp/carp_console.hpp"
#include "Carp/carp_dump.hpp"
#include "Carp/carp_log.hpp"
#include "Carp/carp_task_consumer.hpp"
#include "Carp/carp_lua_debug.hpp"
#include "Carp/carp_lua_profiler.hpp"
#include "Carp/carp_lua_decompile.hpp"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

extern CarpLuaDebugServer s_alittle_lua_debug_server;
extern CarpLuaProfiler s_alittle_lua_profiler;
class Application;

#define DEFAULT_FPS 60
#define TRANS_INTERVAL(fps) ((unsigned int)(1000.0f/fps))

class ALittleSchedule
{
private:
	void Setup(int argc, char* argv[])
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
		ALittleVertexImage::Bind(s_alittle_script.GetLuaState());
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
		s_alittle_lua_debug_server.Bind(s_alittle_script.GetLuaState());
		CarpLuaDebugClient::Bind(s_alittle_script.GetLuaState());
		s_alittle_lua_profiler.Bind(s_alittle_script.GetLuaState());
		CarpLuaDecompile::Bind(s_alittle_script.GetLuaState());
		
		// load engine
		CARP_INFO("==>ScheduleSystem Lua Init Begin<==");
		std::string main_path;
		if (argc >= 2) main_path = argv[1];
		std::string debug_info;
		if (argc >= 3) debug_info = argv[2];
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
			.addFunction("SetFPS", &ALittleSchedule::SetFPS)
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

private:
	/**
	 * handle all event
	 * @param event: SDL event object
	 * @return continue or not
	 */
	bool HandleEvent(const SDL_Event& event)
	{
		// SDL_USEREVENT used for exit
		if (event.type == SDL_USEREVENT) return false;
		
		if (event.type == SDL_QUIT)
		{
			s_alittle_script.Invoke("__ALITTLEAPI_Quit");
			return true;
		}

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
			SDL_Event event = {0};
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
	 * FPS
	 */
	bool SetFPS(int fps)
	{
		if (fps <= 0) return false;
		m_interval = TRANS_INTERVAL(fps);
		return true;
	}
	/**
	 * Set APP Pause Interval in ms
	 */
	bool SetAppPauseInterval(int interval)
	{
		if (interval <= 0) return false;
		m_app_pause_interval = interval;
		return true;
	}
	/**
	 * Get APP Pause Interval in ms
	 */
	int GetAppPauseInterval() const
	{
		return m_app_pause_interval;
	}

public:
	static void EmscriptenMainLoop(void* arg)
	{
		auto* self = static_cast<ALittleSchedule*>(arg);
		bool run;
		self->MainLoop(run);
	}

private:
	/**
	 * render action
	 */
	void Render()
	{
		// get current time
		m_current_time = SDL_GetTicks();
		s_carp_task_consumer.HandleEvent();
#ifdef __EMSCRIPTEN__
		s_carp_schedule.PollOne();
#endif

		// check fps
		if (m_current_time < m_last_time + m_interval) return;

		// update script logic
		if (m_has_updater)
			s_alittle_script.Invoke("__ALITTLEAPI_Update", m_current_time - m_last_time);

		// render for interval
		s_alittle_render.Render();

		// save last time
		m_last_time = m_current_time;
	}

	void MainLoop(bool& run)
	{
		SDL_Event event;
		// execute render
		Render();
		// handle all event
		bool has_event = false;
		while (SDL_PollEvent(&event))
		{
			has_event = true;
			run = HandleEvent(event);
			if (run == false) break;
		}
		// if has event then sleep 1ms
		if (has_event == false)
			SDL_Delay(m_app_pause ? m_app_pause_interval : 1);
	}

public:
	int Run(int argc, char* argv[])
	{
		// set dump info
#ifdef _WIN32
		s_carp_dump.Setup("ALittleClient", []() { s_carp_log.Shutdown(); });
#endif

#ifndef __EMSCRIPTEN__
		CarpFile::CreateDeepFolder(CarpRWops::ExternalFilePath() + "Log");
		s_carp_log.Setup(CarpRWops::ExternalFilePath() + "Log/", "ALittleClient");
#endif
		// init SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) == -1)
			CARP_ERROR(SDL_GetError());

		// enable drop file
		SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
		// Android do not pause
		SDL_SetHint(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, "0");

#ifdef _WIN32
		s_carp_console.Setup("ALittleClient", std::bind(ALittleSchedule::PushConsoleEvent, std::placeholders::_1, std::placeholders::_2)
			, std::bind(&ALittleSchedule::Exit, this), ALittleSchedule::PushConsoleHelp);
#endif

		// print current platform
		CARP_INFO("current platform is " << s_alittle_system.GetPlatform());

		do
		{
			// flag restart to false
			m_restart = false;
			bool run = true;

			// setup app
			Setup(argc, argv);
			// store current time
			m_current_time = SDL_GetTicks();
			m_last_time = m_current_time;

#ifdef __EMSCRIPTEN__
			const int simulate_infinite_loop = 1; // call the function repeatedly
			const int fps = -1; // call the function as fast as the browser wants to render (typically 60fps)
			emscripten_set_main_loop_arg(EmscriptenMainLoop, this, fps, simulate_infinite_loop);
#else
			while (run) MainLoop(run);
#endif		

			CARP_INFO("===============ScheduleSystem Shutdown Begin============");

			SDL_Event event;

			s_alittle_display.RemoveAllChild();

			// handle last event
			while (SDL_PollEvent(&event))
				HandleEvent(event);

			s_carp_task_consumer.Shutdown();

			// handle last event
			while (SDL_PollEvent(&event))
				HandleEvent(event);
			
			// close all system
			s_alittle_lua_debug_server.Stop();
			s_alittle_lua_profiler.Stop();
			s_alittle_script.Shutdown();

			// handle last event
			while (SDL_PollEvent(&event))
				HandleEvent(event);

			s_carp_task_consumer.Shutdown();

			s_alittle_audio.Shutdown();

			s_alittle_display.Shutdown();
			s_alittle_render.Shutdown();

			s_alittle_font.Shutdown();
			CARP_INFO("===============ScheduleSystem Shutdown Completed============");
		} while (m_restart);

		// release SDL
		SDL_Quit();

		s_carp_schedule.Exit();
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
		return 0;
	}

	/**
	 * exit
	 */
	void Exit() const
	{
		SDL_Event event;
		event.type = SDL_USEREVENT;
		SDL_PushEvent(&event);
	}

	/**
	 * force exit
	 */
	void ForceExit() const
	{
		exit(0);
	}

	/**
	 * restart
	 */
	void Restart()
	{
		m_restart = true;
		Exit();
	}

public:
	int GetLastMS() const { return m_last_time; }
	int GetCurrentMS() const { return m_current_time; }
	int GetLogicInterval() const { return m_interval; }
	int GetRealInterval() const { return m_current_time - m_last_time; }

private:
	int m_interval = TRANS_INTERVAL(DEFAULT_FPS);			// render loop interval
	int m_last_time = 0;		// store last render time
	int m_current_time = 0;		// store current
	int m_has_updater = false;

private:
	bool m_restart = false;			// restart or not
	bool m_app_pause = false;		// pause
	int	 m_app_pause_interval = 10;
};

extern ALittleSchedule s_alittle_schedule;

#endif

#ifdef ALITTLE_SCHEDULE_IMPL
#ifndef ALITTLE_SCHEDULE_IMPL_INCLUDE
#define ALITTLE_SCHEDULE_IMPL_INCLUDE
ALittleSchedule s_alittle_schedule;
#endif
#endif