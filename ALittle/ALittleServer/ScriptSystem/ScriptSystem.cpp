
#include "ScriptSystem.h"

#include "Carp/carp_bit_bind.hpp"
#include "Carp/carp_message_bind.hpp"
#include "Carp/carp_crypto_bind.hpp"
#include "Carp/carp_log_bind.hpp"
#include "Carp/carp_csv_bind.hpp"
#include "Carp/carp_timer_bind.hpp"
#include "Carp/carp_file_bind.hpp"
#include "Carp/carp_string_bind.hpp"
#include "Carp/carp_task_consumer_bind.hpp"
#include "Carp/carp_lua_worker.hpp"
#include "Carp/carp_process_bind.hpp"

extern "C" {
#include "lualib/ajson/lua_ajson.h"
#include "lualib/cjson/lua_cjson.h"
#include "lualib/tinyxml2/tinyxml2lib.h"
#include "lualib/sqlite3/lsqlite3.h"
}

namespace ALittle
{
	
void ScriptSystem::Setup()
{
	Init();

	luaopen_cjson(m_L); lua_settop(m_L, 0);
	luaopen_ajson(m_L); lua_settop(m_L, 0);
	luaopen_tinyxml2(m_L); lua_settop(m_L, 0);
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
	CarpSurfaceBind::Bind(m_L);
	CarpLuaWorker::Bind(m_L);
	CarpProcessBind::Bind(m_L);
}

void ScriptSystem::Shutdown()
{
	Release();
}
	
} // ALittle
