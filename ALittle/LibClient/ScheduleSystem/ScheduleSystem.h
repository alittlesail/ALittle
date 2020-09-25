
#ifndef _ALITTLE_SCHEDULESYSTEM_H_
#define _ALITTLE_SCHEDULESYSTEM_H_

#include <string>
#include <list>
#include <map>

union SDL_Event;

namespace ALittle
{

class Application;
class ScriptSystemEx;

class ScheduleSystem
{
public:
	static ScheduleSystem& Instance();

private:
	void Setup(int argc, char* argv[]);
	void RegisterToScript(ScriptSystemEx& script_system);

public:
	/**
	 * push user event
	 * @param event_type: event type
	 * @param data1: data1
	 * @param data2: data2
	 */
	void PushUserEvent(unsigned int event_type, void* data1 = 0, void* data2 = 0);
	
	/**
	 * push external event
	 * @param event_type: event type
	 * @param method
	 * @param method length
	 * @param param
	 * @param param length
	 */
	void PushExternalEvent(const char* method, int method_len, const char* param, int param_len);

	/**
	 * push console event
	 * @param module
	 * @param cmd
	 */
	void PushConsoleEvent(const std::string& module, const std::string& cmd);
	void PushConsoleHelp();

private:
	/**
	 * handle all event
	 * @param event: SDL event object
	 * @return continue or not
	 */
	bool HandleEvent(const SDL_Event& event);

	// 处理外部lua调用
	static void HandleExternalInvokeLua(unsigned int event_type, void* data1, void* data2);
	// 控制台lua调用
	static void HandleConsoleInvokeLua(unsigned int event_type, void* data1, void* data2);

public:
	/**
	 * FPS
	 */
	bool SetFPS(int fps);
	/**
	 * Set APP Pause Interval in ms
	 */
	bool SetAppPauseInterval(int interval);
	/**
	 * Get APP Pause Interval in ms
	 */
	int GetAppPauseInterval();

public:
	static void EmscriptenMainLoop(void* arg);

private:
	/**
	 * render action
	 */
	void Render();

	void MainLoop(bool& run);

public:
	int Run(int argc, char* argv[]);
	
	/**
	 * exit
	 */
	void Exit();
	
	/**
	 * force exit
	 */
	void ForceExit();
	
	/**
	 * restart
	 */
	void Restart();

public:
	typedef void (*ScheduleHandle)(unsigned int event_type, void* data1, void* data2);
	void RegisterHandle(unsigned int event_type, ScheduleHandle func);
	void UnregisterHandle(unsigned int event_type);

private:
	typedef std::map<unsigned int, ScheduleHandle> ScheduleHandleMap;
	ScheduleHandleMap m_handle_map;

public:
	int GetLastMS() { return m_last_time; }
	int GetCurrentMS() { return m_current_time; }
	int GetLogicInterval() { return m_interval; }
	int GetRealInterval() { return m_current_time - m_last_time; }

private:
	int m_interval;			// render loop interval
	int m_last_time;		// store last render time
	int m_current_time;		// store current
	int m_has_updater;
	
private:
	bool m_restart;			// restart or not
	bool m_app_pause;		// pause
	int	 m_app_pause_interval;

private:
	ScheduleSystem();
	~ScheduleSystem();
};

} // ALittle

#define g_ScheduleSystem ALittle::ScheduleSystem::Instance()

#endif // _ALITTLE_SCHEDULESYSTEM_H_
