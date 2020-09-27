#ifndef ALITTLE_SYSTEM_INCLUDED
#define ALITTLE_SYSTEM_INCLUDED (1)

extern "C" {
#include "lua.h"
}
#include "LuaBridge/LuaBridge.h"

#include "Carp/carp_system.hpp"

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
		lua_pushstring(l_state, CarpSystem::GetPlatform().c_str());
		return 1;
	}
};

#endif

