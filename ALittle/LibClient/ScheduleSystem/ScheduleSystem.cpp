
#include "ScheduleSystem.h"
#include "EventDefine.h"
#include <asio.hpp>

#include "ALittle/LibClient/Tool/MemoryPool.h"

#include "ALittle/LibClient/ThreadSystem/ThreadSystem.h"
#include "ALittle/LibClient/RenderSystem/RenderSystem.h"
#include "ALittle/LibClient/RenderSystem/DisplaySystem.h"
#include "ALittle/LibClient/AudioSystem/AudioSystem.h"
#include "ALittle/LibClient/NetSystem/NetSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystem.h"
#include "ALittle/LibClient/Helper/InputHelper.h"

#include "ALittle/LibClient/Platform/Windows/WindowsSystem.h"

#include <SDL.h>
#include <SDL_version.h>
#include <SDL_syswm.h>
#include <functional>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#define CARP_CONSOLE_IMPL
#include "Carp/carp_console.hpp"
#define CARP_DUMP_IMPL
#include "Carp/carp_dump.hpp"

#include "Carp/carp_file.hpp"

#define CARP_LOG_IMPL
#include "Carp/carp_log.hpp"

#include "Carp/carp_rwops.hpp"
#define CARP_RWOPS_IMPL
#include "Carp/carp_rwops.h"

namespace ALittle
{

#define DEFAULT_FPS 60
#define TRANS_INTERVAL(fps) ((unsigned int)(1000.0f/fps))

ScheduleSystem::ScheduleSystem()
: m_interval(TRANS_INTERVAL(DEFAULT_FPS))
, m_last_time(0), m_current_time(0)
, m_restart(false)
, m_app_pause(false)
, m_app_pause_interval(10)
, m_has_updater(false)
{}

ScheduleSystem::~ScheduleSystem() {}

ScheduleSystem& ScheduleSystem::Instance()
{
	static ScheduleSystem instance;
	return instance;
}

void ScheduleSystem::Setup(int argc, char* argv[])
{
	// 初始化日志系统
	CARP_INFO("==>ScheduleSystem Setup Begin<==");

	// set up instance
	g_MemoryPoolGroup;				// memory pool
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

bool ScheduleSystem::SetFPS(int fps)
{
	if (fps <= 0) return false;
	m_interval = TRANS_INTERVAL(fps);
	return true;
}

bool ScheduleSystem::SetAppPauseInterval(int interval)
{
	if (interval <= 0) return false;
	m_app_pause_interval = interval;
	return true;
}

int ScheduleSystem::GetAppPauseInterval()
{
	return m_app_pause_interval;
}

void ScheduleSystem::EmscriptenMainLoop(void* arg)
{
	ScheduleSystem* self = (ScheduleSystem*)arg;
	bool run;
	self->MainLoop(run);
}

int ScheduleSystem::Run(int argc, char* argv[])
{
	// set dump info
#ifdef _WIN32
	s_carp_dump.Setup("ALittleClient", []() { s_carp_log.Shutdown(); });
#endif

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) == -1)
		CARP_ERROR(SDL_GetError());
	
	// enable drop file
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	// Android do not pause
	SDL_SetHint(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, "0");

#ifndef __EMSCRIPTEN__
	CarpFile::CreateDeepFolder(CarpRWops::ExternalFilePath() + "Log");
	s_carp_log.Setup(CarpRWops::ExternalFilePath() + "Log/", "ALittleClient");
#endif
#ifdef _WIN32
	s_carp_console.Setup("ALittleClient", std::bind(&ScheduleSystem::PushConsoleEvent, this, std::placeholders::_1, std::placeholders::_2)
						, std::bind(&ScheduleSystem::Exit, this), std::bind(&ScheduleSystem::PushConsoleHelp, this));
#endif

	// print current platform
	CARP_INFO("current platform is " << SDL_GetPlatform());

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

		g_DisplaySystem.RemoveAllChild();

		// handle last event
		while (SDL_PollEvent(&event))
			HandleEvent(event);

		g_ThreadSystem.Shutdown();

		// handle last event
		while (SDL_PollEvent(&event))
			HandleEvent(event);

		// close all system
		InputHelper::Shutdown();
		g_ScriptSystem.Shutdown();

		// handle last event
		while (SDL_PollEvent(&event))
			HandleEvent(event);

		g_AudioSystem.Shutdown();

		g_RenderSystem.Shutdown();
		NetSystem::Shutdown();

		CARP_INFO("===============ScheduleSystem Shutdown Completed============");
	}
	while(m_restart);

	// release SDL
	SDL_Quit();

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

void ScheduleSystem::Render()
{	
	// get current time
	m_current_time = SDL_GetTicks();

#ifdef _WIN32
	Windows_UpdateNetwork(m_current_time);
#endif

	// check fps
	if (m_current_time < m_last_time + m_interval) return;

	// update script logic
	if (m_has_updater)
		g_ScriptSystem.Invoke("__ALITTLEAPI_Update", m_current_time - m_last_time);

	// render for interval
	g_RenderSystem.Render();

	// save last time
	m_last_time = m_current_time;
}

void ScheduleSystem::MainLoop(bool& run)
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

bool ScheduleSystem::HandleEvent(const SDL_Event& event)
{
	if (event.type == SDL_QUIT) return false;

	// handle user event
	if (event.type == SDL_USEREVENT)
	{
		ScheduleHandleMap::iterator it = m_handle_map.find(event.user.code);
		if (it != m_handle_map.end()) it->second(event.user.code, event.user.data1, event.user.data2);
				
		return true;
	}
	
	// handle windows event
	if (event.type == SDL_WINDOWEVENT)
	{
		if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			g_RenderSystem.HandleViewResized((unsigned int)event.window.data1, (unsigned int)event.window.data2);
		else if (event.window.event == SDL_WINDOWEVENT_MINIMIZED || event.window.event == SDL_WINDOWEVENT_HIDDEN)
			g_RenderSystem.HandleMinViewSize();
		else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
			g_RenderSystem.HandleMaxViewSize();
		else if (event.window.event == SDL_WINDOWEVENT_RESTORED || event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			g_RenderSystem.HandleRestoreViewSize();
		else if (event.window.event == SDL_WINDOWEVENT_ENTER)
			g_ScriptSystem.Invoke("__ALITTLEAPI_WindowEnter");
		else if (event.window.event == SDL_WINDOWEVENT_LEAVE)
			g_ScriptSystem.Invoke("__ALITTLEAPI_WindowLeave");

		return true;
	}

	// handle drop file event
	if (event.type == SDL_DROPFILE)
	{
		g_ScriptSystem.Invoke("__ALITTLEAPI_DropFile", (const char*)event.drop.file);
		SDL_free(event.drop.file);
		return true;
	}
#if !(defined __ANDROID__) && !(defined __IPHONEOS__) // because IOS/Android open SDL_WINDOW_ALLOW_HIGHDPI,mouse and finger both send message. and mouse's pos is wrong. so not handle mouse
	// handle mouse event
	else if (event.type == SDL_MOUSEMOTION)
	{
		g_ScriptSystem.Invoke("__ALITTLEAPI_MouseMoved", event.motion.x, event.motion.y);
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		switch(event.button.button)
		{
		case 1: g_ScriptSystem.Invoke("__ALITTLEAPI_LButtonDown", event.button.x, event.button.y, event.button.clicks); break;
		case 2: g_ScriptSystem.Invoke("__ALITTLEAPI_MButtonDown", event.button.x, event.button.y, event.button.clicks); break;
		case 3: g_ScriptSystem.Invoke("__ALITTLEAPI_RButtonDown", event.button.x, event.button.y, event.button.clicks); break;
		}	
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		switch(event.button.button)
		{
		case 1: g_ScriptSystem.Invoke("__ALITTLEAPI_LButtonUp", event.button.x, event.button.y); break;
		case 2: g_ScriptSystem.Invoke("__ALITTLEAPI_MButtonUp", event.button.x, event.button.y); break;
		case 3: g_ScriptSystem.Invoke("__ALITTLEAPI_RButtonUp", event.button.x, event.button.y); break;
		}	
	}
	else if (event.type == SDL_MOUSEWHEEL)
		g_ScriptSystem.Invoke("__ALITTLEAPI_MouseWheel", event.wheel.x, event.wheel.y);
#endif // !__IPHONEOS__/__ANDROID__

	// handle keyboard event
	else if (event.type == SDL_KEYDOWN)
		g_ScriptSystem.Invoke("__ALITTLEAPI_KeyDown"
			, static_cast<int>(event.key.keysym.mod)
			, static_cast<int>(event.key.keysym.sym)
			, static_cast<int>(event.key.keysym.scancode));
	else if (event.type == SDL_KEYUP)
		g_ScriptSystem.Invoke("__ALITTLEAPI_KeyUp"
			, static_cast<int>(event.key.keysym.mod)
			, static_cast<int>(event.key.keysym.sym)
			, static_cast<int>(event.key.keysym.scancode));
	else if (event.type == SDL_TEXTINPUT)
		g_ScriptSystem.Invoke("__ALITTLEAPI_TextInput", event.text.text);
	else if (event.type == SDL_TEXTEDITING)
		g_ScriptSystem.Invoke("__ALITTLEAPI_TextEditing", event.edit.text, event.edit.start);
	
	// handle touch event
	else if (event.type == SDL_FINGERDOWN)
		g_ScriptSystem.Invoke("__ALITTLEAPI_FingerDown"
			, g_RenderSystem.CalcFingerX(event.tfinger.x)
			, g_RenderSystem.CalcFingerY(event.tfinger.y)
			, static_cast<int>(event.tfinger.fingerId)
			, static_cast<int>(event.tfinger.touchId));
	else if (event.type == SDL_FINGERUP)
		g_ScriptSystem.Invoke("__ALITTLEAPI_FingerUp"
			, g_RenderSystem.CalcFingerX(event.tfinger.x)
			, g_RenderSystem.CalcFingerY(event.tfinger.y)
			, static_cast<int>(event.tfinger.fingerId)
			, static_cast<int>(event.tfinger.touchId));
	else if (event.type == SDL_FINGERMOTION)
		g_ScriptSystem.Invoke("__ALITTLEAPI_FingerMoved"
			, g_RenderSystem.CalcFingerX(event.tfinger.x)
			, g_RenderSystem.CalcFingerY(event.tfinger.y)
			, static_cast<int>(event.tfinger.fingerId)
			, static_cast<int>(event.tfinger.touchId));


	else if (event.type == SDL_APP_WILLENTERBACKGROUND)
		g_ScriptSystem.Invoke("__ALITTLEAPI_WillEnterBackground");
	else if (event.type == SDL_APP_WILLENTERFOREGROUND)
		g_ScriptSystem.Invoke("__ALITTLEAPI_WillEnterForeground");
	// handle app go to background
	else if (event.type == SDL_APP_DIDENTERBACKGROUND)
	{
		m_app_pause = true;
		g_ScriptSystem.Invoke("__ALITTLEAPI_DidEnterBackground");
	}
	else if (event.type == SDL_APP_DIDENTERFOREGROUND)
	{
		m_app_pause = false;
		g_ScriptSystem.Invoke("__ALITTLEAPI_DidEnterForeground");
		// just release SDL_WaitEvent
		PushUserEvent(EMPTY_EVENT);
	}

	// handle device reset
	else if (event.type == SDL_RENDER_DEVICE_RESET)
		g_RenderSystem.HandleDeviceReset();
	else if (event.type == SDL_APP_LOWMEMORY)
		g_ScriptSystem.Invoke("__ALITTLEAPI_LowMemory");

	return true;
}

void ScheduleSystem::HandleExternalInvokeLua(unsigned int event_type, void* data1, void* data2)
{
	char* method = (char*)data1;
	char* content = (char*)data2;
	g_ScriptSystem.Invoke(method, content);
	g_MemoryPoolGroup.Release(method);
	g_MemoryPoolGroup.Release(content);
}

void ScheduleSystem::HandleConsoleInvokeLua(unsigned int event_type, void* data1, void* data2)
{
	std::string module = (char*)data1;
	std::string cmd = (char*)data2;

	if (module == "Client")
	{
		g_ScriptSystem.Invoke("__ALITTLEAPI_HandleConsoleCmd", cmd.c_str());
	}

	g_MemoryPoolGroup.Release(data1);
	g_MemoryPoolGroup.Release(data2);
}

void ScheduleSystem::Exit()
{
	SDL_Event event;
	event.type = SDL_QUIT;
	SDL_PushEvent(&event);
}

void ScheduleSystem::Restart()
{
	m_restart = true;
	Exit();
}

void ScheduleSystem::ForceExit()
{
	exit(0);
}

void ScheduleSystem::PushUserEvent(unsigned int event_type, void* data1, void* data2)
{
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = event_type;
	event.user.data1 = data1;
	event.user.data2 = data2;
	SDL_PushEvent(&event);
}

void ScheduleSystem::PushExternalEvent(const char* method, int method_len, const char* param, int param_len)
{
	// calc method and param len
	if (method_len <= 0) method_len = static_cast<int>(strlen(method));
	if (param_len <= 0) param_len = static_cast<int>(strlen(param));

	// create memory
	char* method_mem = (char*)g_MemoryPoolGroup.Create(method_len + 1);
	char* param_mem = (char*)g_MemoryPoolGroup.Create(param_len + 1);

	// copy info
	memcpy(method_mem, method, method_len); method_mem[method_len] = 0;
	memcpy(param_mem, param, param_len); param_mem[param_len] = 0;

	// push event
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = EXTERNAL_INVOKE_LUA;
	event.user.data1 = (void*)method_mem;
	event.user.data2 = (void*)param_mem;
	SDL_PushEvent(&event);
}

void ScheduleSystem::PushConsoleEvent(const std::string& module, const std::string& cmd)
{
	// create memory
	char* module_mem = (char*)g_MemoryPoolGroup.Create(module.size() + 1);
	char* cmd_mem = (char*)g_MemoryPoolGroup.Create(cmd.size() + 1);

	// copy info
	memcpy(module_mem, module.c_str(), module.size()); module_mem[module.size()] = 0;
	memcpy(cmd_mem, cmd.c_str(), cmd.size()); cmd_mem[cmd.size()] = 0;

	// push event
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = CONSOLE_INVOKE_LUA;
	event.user.data1 = (void*)module_mem;
	event.user.data2 = (void*)cmd_mem;
	SDL_PushEvent(&event);
}

void ScheduleSystem::PushConsoleHelp()
{
	CARP_INFO(u8"模块列表:Client");
}

//===============================================================

void ScheduleSystem::RegisterToScript(ScriptSystem& script_system)
{
	lua_State* L = script_system.GetLuaState();

	luabridge::getGlobalNamespace(L)
		.beginClass<ScheduleSystem>("__CPPAPIScheduleSystem")
		.addFunction("Exit", &ScheduleSystem::Exit)
		.addFunction("ForceExit", &ScheduleSystem::ForceExit)
		.addFunction("Restart", &ScheduleSystem::Restart)
		.addFunction("SetFPS", &ScheduleSystem::SetFPS)
		.addFunction("SetAppPauseInterval", &ScheduleSystem::SetAppPauseInterval)
		.addFunction("GetAppPauseInterval", &ScheduleSystem::GetAppPauseInterval)
		.addFunction("GetCurrentMS", &ScheduleSystem::GetCurrentMS)
		.endClass();

	luabridge::setGlobal(L, this, "__CPPAPI_ScheduleSystem");

	g_ScheduleSystem.RegisterHandle(EXTERNAL_INVOKE_LUA, ScheduleSystem::HandleExternalInvokeLua);
	g_ScheduleSystem.RegisterHandle(CONSOLE_INVOKE_LUA, ScheduleSystem::HandleConsoleInvokeLua);
}

void ScheduleSystem::RegisterHandle(unsigned int event_type, ScheduleHandle func)
{
	m_handle_map[event_type] = func;
}

void ScheduleSystem::UnregisterHandle(unsigned int event_type)
{
	m_handle_map.erase(event_type);
}

} // ALittle
