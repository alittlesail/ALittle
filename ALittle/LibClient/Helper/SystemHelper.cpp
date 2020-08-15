
#include "SystemHelper.h"

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"
#include "ALittle/LibClient/ScriptSystem/ScriptSystemEx.h"
#include "ALittle/LibClient/Tool/MemoryPool.h"

#include "ALittle/LibClient/RenderSystem/RenderSystem.h"

#include "ALittle/LibClient/Platform/Android/AndroidSystem.h"
#include "ALittle/LibClient/Platform/iOS/iOSSystem.h"
#include "ALittle/LibClient/Platform/Windows/WindowsSystem.h"
#include <SDL.h>

namespace ALittle
{

std::string SystemHelper::s_temp_string;

void SystemHelper::Alert(const char* message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", message, NULL);
}

void SystemHelper::InstallProgram(const char* file_path)
{
#ifdef __ANDROID__
	Android_InstallAPK(file_path);
#elif __IPHONEOS__
#elif _WIN32
	Windows_InstallExe(file_path);
#endif
}

void SystemHelper::StartProgram(const char* package_name)
{
#ifdef __ANDROID__
	Android_StartAPP(package_name);
#elif __IPHONEOS__
	iOS_StartAPP(package_name);
#elif _WIN32
	Windows_StartApp(package_name);
#endif
}

void SystemHelper::BackProgram()
{
#ifdef __ANDROID__
	Android_MoveTaskToBack();
#elif __IPHONEOS__

#elif _WIN32
	Windows_MoveTaskToBack();
#endif
}

const char* SystemHelper::GetDeviceID()
{
#ifdef __ANDROID__
	return Android_GetDeviceID();
#elif __IPHONEOS__
	return iOS_GetDeviceID();
#elif _WIN32
	return Windows_GetDeviceID();
#else
	s_temp_string = "";
	return s_temp_string.c_str();
#endif
}

int SystemHelper::GetScreenWidth()
{
#ifdef _WIN32  
	return Windows_GetScreenWidth();  
#elif __ANDROID__
	return Android_GetScreenWidth();
#elif __IPHONEOS__
	return iOS_GetScreenWidth();
#else
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) return 0;
	return dm.w;
#endif
}

int SystemHelper::GetScreenHeight()
{
#ifdef _WIN32
	return Windows_GetScreenHeight();
#elif __ANDROID__
	return Android_GetScreenHeight();
#elif __IPHONEOS__
	return iOS_GetScreenHeight();
#else
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) return 0;
	return dm.h;
#endif
}

int SystemHelper::GetStatusBarHeight()
{
#ifdef __ANDROID__
	return Android_GetStatusBarHeight() / g_RenderSystem.GetScaleY();
#elif __IPHONEOS__
	return iOS_GetStatusBarHeight() / g_RenderSystem.GetScaleY();
#else
	return 0;
#endif
}

void SystemHelper::SystemSelectFile(const char* init_dir)
{
#ifdef _WIN32
	Windows_SystemSelectFile(init_dir);
#elif __ANDROID__
	Android_SystemSelectFile(init_dir);
#elif __IPHONEOS__
	iOS_SystemSelectFile(init_dir);
#else
	g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSelectFile");
#endif
}

void SystemHelper::SystemSelectDirectory(const char* init_dir)
{
#ifdef _WIN32
	Windows_SystemSelectDirectory(init_dir);
#elif __ANDROID__
	Android_SystemSelectDirectory(init_dir);
#elif __IPHONEOS__
	iOS_SystemSelectDirectory(init_dir);
#else
	g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSelectDirectory");
#endif
}

void SystemHelper::SystemSaveFile(const char* file_name, const char* init_dir)
{
#ifdef _WIN32
	Windows_SystemSaveFile(file_name, init_dir);
#elif __ANDROID__
	Android_SystemSaveFile(file_name, init_dir);
#elif __IPHONEOS__
	iOS_SystemSaveFile(file_name, init_dir);
#else
	g_ScriptSystem.Invoke("__ALITTLEAPI_SystemSaveFile");
#endif
}

void SystemHelper::OpenUrlBySystemBrowser(const char* url)
{
#ifdef _WIN32
	Windows_OpenUrlBySystemBrowser(url);
#elif __ANDROID__
	Android_OpenUrlBySystemBrowser(url);
#elif __IPHONEOS__
	iOS_OpenUrlBySystemBrowser(url);
#endif
}

int SystemHelper::GetDisplayOrientation()
{
	return static_cast<int>(SDL_GetDisplayOrientation(0));
}

} // ALittle
