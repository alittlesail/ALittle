#ifndef ALITTLE_SYSTEM_INCLUDED
#define ALITTLE_SYSTEM_INCLUDED (1)

extern "C" {
#include "lua.h"
}
#include "LuaBridge/LuaBridge.h"
#ifdef __ANDROID__
#include "sokol/sokol_app.h"
#endif

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

class ALittleSystem
{
public:
	static void Bind(lua_State* l_state)
	{
		luabridge::getGlobalNamespace(l_state)
			// .addFunction("__CPPAPI_GetDeviceID", SystemHelper::GetDeviceID)
			.addFunction("__CPPAPI_GetPlatform", GetPlatform)
			// .addFunction("__CPPAPI_InstallProgram", SystemHelper::InstallProgram)
			// .addFunction("__CPPAPI_StartProgram", SystemHelper::StartProgram)
			// .addFunction("__CPPAPI_BackProgram", SystemHelper::BackProgram)
			// .addFunction("__CPPAPI_GetScreenWidth", SystemHelper::GetScreenWidth)
			// .addFunction("__CPPAPI_GetScreenHeight", SystemHelper::GetScreenHeight)
			// .addFunction("__CPPAPI_GetStatusBarHeight", SystemHelper::GetStatusBarHeight)
			// .addFunction("__CPPAPI_GetTicks", SDL_GetTicks)
			// .addFunction("__CPPAPI_EnableScreenSaver", SDL_EnableScreenSaver)
			// .addFunction("__CPPAPI_DisableScreenSaver", SDL_DisableScreenSaver)
			// .addFunction("__CPPAPI_SystemSelectFile", SystemHelper::SystemSelectFile)
			// .addFunction("__CPPAPI_SystemSelectDirectory", SystemHelper::SystemSelectDirectory)
			// .addFunction("__CPPAPI_SystemSaveFile", SystemHelper::SystemSaveFile)
			// .addFunction("__CPPAPI_GetDisplayOrientation", SystemHelper::GetDisplayOrientation)
			// .addFunction("__CPPAPI_OpenUrlBySystemBrowser", SystemHelper::OpenUrlBySystemBrowser)
			// .addFunction("__CPPAPI_Alert", SystemHelper::Alert)
			;
	}

	static int GetPlatform(lua_State* l_state)
	{
#ifdef _WIN32
		lua_pushstring(l_state, "Windows");
#elif __ANDROID__
		lua_pushstring(l_state, "Andoird");
#elif __APPLE__
#ifdef TARGET_OS_IPHONE
		lua_pushstring(l_state, "iOS");
#else
		lua_pushstring(l_state, "Mac");
#endif
#elif __EMSCRIPTEN__
		lua_pushstring(l_state, "Emscripten");
#endif
		return 1;
	}
};

extern ALittleSystem s_alittle_system;

#endif


#ifdef ALITTLE_SYSTEM_IMPL
ALittleSystem s_alittle_system;
#endif

