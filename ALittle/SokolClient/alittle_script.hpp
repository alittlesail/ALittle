#ifndef ALITTLE_SCRIPT_INCLUDED
#define ALITTLE_SCRIPT_INCLUDED (1)

#include <string>

extern "C" {
#include "lualib/ajson/lua_ajson.h"
#include "lualib/cjson/lua_cjson.h"
#include "lualib/sqlite3/lsqlite3.h"
}

#include "LuaBridge/LuaBridge.h"

#include "Carp/carp_script.hpp"
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

class ALittleScript : public CarpScript
{
public:
	void Setup()
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
	}
	
	void Shutdown()
	{
		Invoke("__ALITTLEAPI_ShutdownMainModule");
		Release();
	}

public:
	/**
	 * import engine script
	 */
	void StartScript(std::string module_name, const std::string& debug_info)
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
};

extern ALittleScript& ALittleScriptInstance();
#define s_alittle_script ALittleScriptInstance()

#endif


#ifdef ALITTLE_SCRIPT_IMPL
ALittleScript& ALittleScriptInstance() { static ALittleScript instance; return instance; };
#endif

