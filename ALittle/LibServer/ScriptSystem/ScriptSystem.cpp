
#include "ScriptSystem.h"

#include "Carp/carp_bit_bind.hpp"
#include "Carp/carp_message_bind.hpp"
#include "Carp/carp_crypto_bind.hpp"
#include "Carp/carp_log_bind.hpp"
#include "Carp/carp_csv_bind.hpp"
#include "Carp/carp_timer_bind.hpp"
#include "Carp/carp_file_bind.hpp"
#include "Carp/carp_string_bind.hpp"

namespace ALittle
{
	
void ScriptSystem::Setup()
{
	Init();
	CarpMessageBind::Bind(m_L);
	CarpCryptoBind::Bind(m_L);
	CarpLogBind::Bind(m_L);
	CarpCsvBind::Bind(m_L);
	CarpTimerBind::Bind(m_L);
	CarpFileBind::Bind(m_L);
	CarpStringBind::Bind(m_L);
	CarpBitBind::Bind(m_L);

	// register script system
	luabridge::getGlobalNamespace(m_L)
		.beginNamespace("carp")
		.beginClass<ScriptSystem>("ScriptSystem")
		.addFunction("Require", &ScriptSystem::Require)
		.addFunction("RunScript", &ScriptSystem::RunScriptForLua)
		.endClass()
		.endNamespace();

	luabridge::setGlobal(m_L, this, "__CPPAPI_ScriptSystem");

	std::string require = "core_require = function(path) return __CPPAPI_ScriptSystem:Require(path) end";
	RunScript(require.c_str(), require.size(), "ALittleBuild");
}

void ScriptSystem::Shutdown()
{
	Release();
}
	
} // ALittle
