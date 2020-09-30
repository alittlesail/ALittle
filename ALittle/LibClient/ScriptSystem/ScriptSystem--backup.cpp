
#include "ScriptSystem.h"

#include "ALittle/LibClient/Helper/TextureHelper.h"
#include "ALittle/LibClient/Helper/NetHelper.h"
#include "ALittle/LibClient/Helper/SystemHelper.h"
#include "ALittle/LibClient/Helper/InputHelper.h"

#include "ALittle/LibClient/Tool/CsvFile.h"
#include "ALittle/LibClient/ScheduleSystem/EventDefine.h"
#include "ALittle/LibClient/ScheduleSystem/ScheduleSystem.h"

extern "C" {
#include "lualib/ajson/lua_ajson.h"
#include "lualib/cjson/lua_cjson.h"
#include "lualib/sqlite3/lsqlite3.h"
}

#include <vector>
#include "SDL.h"
#include "LuaBridge/LuaBridge.h"

#include "Carp/carp_message_bind.hpp"
#include "Carp/carp_crypto_bind.hpp"
#include "Carp/carp_log_bind.hpp"
#include "Carp/carp_csv_bind.hpp"
#include "Carp/carp_timer_bind.hpp"
#include "Carp/carp_file_bind.hpp"
#include "Carp/carp_string_bind.hpp"
#include "Carp/carp_bit_bind.hpp"
#include "Carp/carp_rwops_bind.hpp"
#include "Carp/carp_task_consumer_bind.hpp"

namespace ALittle
{

ScriptSystem& ScriptSystem::Instance()
{
	static ScriptSystem instance;
	return instance;
}

void ScriptSystem::Setup()
{
	Init();
	luaopen_cjson(m_L); lua_settop(m_L, 0);
	luaopen_ajson(m_L); lua_settop(m_L, 0);
	luaopen_sqlite3(m_L); lua_settop(m_L, 0);

	CarpMessageBind::Bind(m_L);
	CarpCryptoBind::Bind(m_L);
	CarpLogBind::Bind(m_L);
	CarpCsvBind::Bind(m_L);
	CarpTimerBind::Bind(m_L);
	CarpFileBind::Bind(m_L);
	CarpStringBind::Bind(m_L);
	CarpBitBind::Bind(m_L);
	CarpRWopsBind::Bind(m_L);
	CarpTaskConsumerBind::Bind(m_L);

	luabridge::getGlobalNamespace(m_L)
		.beginClass<SDL_Surface>("__CPPAPISurface")
		.endClass();

	luabridge::getGlobalNamespace(m_L)
		.addFunction("__CPPAPI_CreateSurface", TextureHelper::CreateSurface)
		.addFunction("__CPPAPI_FreeSurface", SDL_FreeSurface)
		.addFunction("__CPPAPI_BlitSurface", TextureHelper::BlitSurface)
		.addFunction("__CPPAPI_LoadSurface", TextureHelper::LoadSurface)
		.addFunction("__CPPAPI_SaveSurface", TextureHelper::SaveSurface)
		.addFunction("__CPPAPI_GetSurfaceWidth", TextureHelper::GetSurfaceWidth)
		.addFunction("__CPPAPI_GetSurfaceHeight", TextureHelper::GetSurfaceHeight)
		.addFunction("__CPPAPI_CutBlitSurface", TextureHelper::CutBlitSurface)
		.addFunction("__CPPAPI_GetSurfaceGrid9", TextureHelper::GetSurfaceGrid9)
		.addFunction("__CPPAPI_GetSurfacePixel", TextureHelper::GetSurfacePixel)
		.addFunction("__CPPAPI_SetSurfacePixel", TextureHelper::SetSurfacePixel)
		.addFunction("__CPPAPI_GetPixelAlpha", TextureHelper::GetPixelAlpha)
		.addFunction("__CPPAPI_SetPixelAlpha", TextureHelper::SetPixelAlpha)
		.addFunction("__CPPAPI_GetPixelRed", TextureHelper::GetPixelRed)
		.addFunction("__CPPAPI_SetPixelRed", TextureHelper::SetPixelRed)
		.addFunction("__CPPAPI_GetPixelGreen", TextureHelper::GetPixelGreen)
		.addFunction("__CPPAPI_SetPixelGreen", TextureHelper::SetPixelGreen)
		.addFunction("__CPPAPI_GetPixelBlue", TextureHelper::GetPixelBlue)
		.addFunction("__CPPAPI_SetPixelBlue", TextureHelper::SetPixelBlue)
		//////////////////////////////////////////////////////////////////////////
		.addFunction("__CPPAPI_StartNetworkListener", NetHelper::StartNetworkListener)
		.addFunction("__CPPAPI_GetNetworkType", NetHelper::GetNetworkType)
		//////////////////////////////////////////////////////////////////////////
		.addFunction("__CPPAPI_GetDeviceID", SystemHelper::GetDeviceID)
		.addFunction("__CPPAPI_GetPlatform", SDL_GetPlatform)
		.addFunction("__CPPAPI_InstallProgram", SystemHelper::InstallProgram)
		.addFunction("__CPPAPI_StartProgram", SystemHelper::StartProgram)
		.addFunction("__CPPAPI_BackProgram", SystemHelper::BackProgram)
		.addFunction("__CPPAPI_GetScreenWidth", SystemHelper::GetScreenWidth)
		.addFunction("__CPPAPI_GetScreenHeight", SystemHelper::GetScreenHeight)
		.addFunction("__CPPAPI_GetStatusBarHeight", SystemHelper::GetStatusBarHeight)
		.addFunction("__CPPAPI_GetTicks", SDL_GetTicks)
		.addFunction("__CPPAPI_EnableScreenSaver", SDL_EnableScreenSaver)
		.addFunction("__CPPAPI_DisableScreenSaver", SDL_DisableScreenSaver)
		.addFunction("__CPPAPI_SystemSelectFile", SystemHelper::SystemSelectFile)
		.addFunction("__CPPAPI_SystemSelectDirectory", SystemHelper::SystemSelectDirectory)
		.addFunction("__CPPAPI_SystemSaveFile", SystemHelper::SystemSaveFile)
		.addFunction("__CPPAPI_GetDisplayOrientation", SystemHelper::GetDisplayOrientation)
		.addFunction("__CPPAPI_OpenUrlBySystemBrowser", SystemHelper::OpenUrlBySystemBrowser)
		.addFunction("__CPPAPI_Alert", SystemHelper::Alert)
		//////////////////////////////////////////////////////////////////////////
		;

	luabridge::getGlobalNamespace(m_L)
		.beginClass<CsvFileLoader>("__CPPAPICsvFileLoader")
		.addConstructor<void(*)()>()
		.addFunction("Start", &CsvFileLoader::Start)
		.addFunction("SetPath", &CsvFileLoader::SetPath)
		.addFunction("GetPath", &CsvFileLoader::GetPath)
		.addFunction("GetID", &CsvFileLoader::GetID)
		.endClass();

	luabridge::getGlobalNamespace(m_L)
		.beginClass<CsvFile>("__CPPAPICsvFile")
		.addConstructor<void(*)()>()
		.addFunction("Close", &CsvFile::Close)
		.addFunction("Load", &CsvFile::Load)
		.addFunction("GetPath", &CsvFile::GetPath)
		.addFunction("ReadCell", &CsvFile::ReadCell)
		.addFunction("GetRowCount", &CsvFile::GetRowCount)
		.addFunction("GetColCount", &CsvFile::GetColCount)
		.endClass();

	luabridge::getGlobalNamespace(m_L)
		.beginClass<CsvFileWrap>("__CPPAPICsvFileWrap")
		.addConstructor<void(*)()>()
		.addFunction("Close", &CsvFileWrap::Close)
		.addFunction("SetCsvFile", &CsvFileWrap::SetCsvFile)
		.addFunction("GetPath", &CsvFileWrap::GetPath)
		.addFunction("ReadCell", &CsvFileWrap::ReadCell)
		.addFunction("GetRowCount", &CsvFileWrap::GetRowCount)
		.addFunction("GetColCount", &CsvFileWrap::GetColCount)
		.endClass();

	g_ScheduleSystem.RegisterHandle(CSV_LOAD_SUCCEED, CsvFileLoader::HandleEvent);
	g_ScheduleSystem.RegisterHandle(CSV_LOAD_FAILED, CsvFileLoader::HandleEvent);

	//////////////////////////////////////////////////////////////////////////
	luabridge::getGlobalNamespace(m_L)
		.addFunction("__CPPAPI_GetClipboardText", InputHelper::GetClipboardText)
		.addFunction("__CPPAPI_SetClipboardText", InputHelper::SetClipboardText)
		.addFunction("__CPPAPI_HasClipboardText", InputHelper::HasClipboardText)
		.addFunction("__CPPAPI_GetClipboardImage", InputHelper::GetClipboardImage)
		.addFunction("__CPPAPI_HasClipboardImage", InputHelper::HasClipboardImage)
		.addFunction("__CPPAPI_SetClipboardImage", InputHelper::SetClipboardImage)
		.addFunction("__CPPAPI_GetIMESelectList", InputHelper::GetIMESelectList)
		.addFunction("__CPPAPI_SetIMSPos", InputHelper::SetIMSPos)
		.addFunction("__CPPAPI_OpenIME", SDL_StartTextInput)
		.addFunction("__CPPAPI_CloseIME", SDL_StopTextInput)
		.addFunction("__CPPAPI_SetIMSRect", InputHelper::SetIMSRect)
		.addFunction("__CPPAPI_GetCursorX", InputHelper::GetCursorX)
		.addFunction("__CPPAPI_GetCursorY", InputHelper::GetCursorY)
		.addFunction("__CPPAPI_SetEditCursor", InputHelper::SetEditCursor)
		.addFunction("__CPPAPI_SetNormalCursor", InputHelper::SetNormalCursor)
		.addFunction("__CPPAPI_SetHandCursor", InputHelper::SetHandCursor)
		.addFunction("__CPPAPI_SetHDragCursor", InputHelper::SetHDragCursor)
		.addFunction("__CPPAPI_SetVDragCursor", InputHelper::SetVDragCursor)
		.addFunction("__CPPAPI_SetHVDragCursor", InputHelper::SetHVDragCursor)
		.addFunction("__CPPAPI_SetHV2DragCursor", InputHelper::SetHV2DragCursor)
		.addFunction("__CPPAPI_SetCrossDragCursor", InputHelper::SetCrossDragCursor)
		;
}

void ScriptSystem::Shutdown()
{
	Invoke("__ALITTLEAPI_ShutdownMainModule");
	Release();
}

ScriptSystem::ScriptSystem()
{
}

ScriptSystem::~ScriptSystem()
{
	Shutdown();
}

void ScriptSystem::StartScript(std::string module_name, const std::string& debug_info)
{
	std::string base_path;
	if (module_name.empty())
	{
		module_name = "ALittleIDE";
		std::vector<char> enter_content;
		if (CarpRWops::LoadFile("Module/Enter.ali", false, enter_content))
			module_name.assign(enter_content.data(), enter_content.size());
	}
	base_path = "Module/" + module_name + "/";
	
	// 检查模块内是否有引起代码，否则加载Core
	std::vector<char> enter_content;
	if (CarpRWops::LoadFile(base_path + "Core/ALittle.lua", false, enter_content))
	{
		Require((base_path + "Core/ALittle").c_str());
		Invoke("RequireCore", (base_path + "Core/").c_str());
	}
	else
	{
		Require("Module/ALittleIDE/Other/GameLibrary/Core/Script/ALittle");
		Invoke("RequireCore", "Module/ALittleIDE/Other/GameLibrary/Core/Script/");
	}

	if (CarpRWops::LoadFile(base_path + "Std/ALittle.lua", false, enter_content))
	{
		Require((base_path + "Std/ALittle").c_str());
		Invoke("RequireStd", (base_path + "Std/").c_str());
	}
	else
	{
		Require("Module/ALittleIDE/Other/GameLibrary/Std/Script/ALittle");
		Invoke("RequireStd", "Module/ALittleIDE/Other/GameLibrary/Std/Script/");
	}

	if (CarpRWops::LoadFile(base_path + "CEngine/ALittle.lua", false, enter_content))
	{
		Require((base_path + "CEngine/ALittle").c_str());
		Invoke("RequireCEngine", (base_path + "CEngine/").c_str());
	}
	else
	{
		Require("Module/ALittleIDE/Other/GameLibrary/CEngine/Script/ALittle");
		Invoke("RequireCEngine", "Module/ALittleIDE/Other/GameLibrary/CEngine/Script/");
	}

	// 启动
	Invoke("__ALITTLEAPI_SetupMainModule", base_path.c_str(), module_name.c_str(), debug_info.c_str());
}


} // ALittle
