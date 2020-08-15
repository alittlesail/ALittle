
#include "ScriptSystem.h"

extern "C" {
#include "ALittle/LibCommon/ThirdParty/json/lua_cjson.h"
#include "ALittle/LibCommon/ThirdParty/json/lua_ajson.h"
#include "ALittle/LibCommon/ThirdParty/lfs/lfs.h"
#include "ALittle/LibCommon/ThirdParty/base64/base64lib.h"
#include "ALittle/LibCommon/ThirdParty/csv/csvlib.h"
#include "ALittle/LibCommon/ThirdParty/md5/md5.h"
#include "ALittle/LibCommon/ThirdParty/utf8/utf8lib.h"
#include "ALittle/LibCommon/ThirdParty/timer/timerlib.h"
#include "ALittle/LibCommon/ThirdParty/sqlite3/lsqlite3.h"
}

#include "ALittle/LibCommon/Helper/LogHelper.h"
#include "ALittle/LibCommon/Helper/FileHelper.h"
#include "ALittle/LibCommon/Helper/CryptHelper.h"
#include "ALittle/LibCommon/Tool/LogSystem.h"
#include "ALittle/LibCommon/Protocol/MessageReadFactory.h"
#include "ALittle/LibCommon/Protocol/MessageWriteFactory.h"

namespace ALittle
{

void ScriptSystem::Init(const std::string& module_title)
{
	m_module_title = module_title;

	// create state
	m_L = ::luaL_newstate();
	if (!m_L)
	{
		ALITTLE_SCRIPT_ERROR("lua_open failed!");
		return;
	}

	// open all library
	luaL_openlibs(m_L); lua_settop(m_L, 0);
	luaopen_json(m_L); lua_settop(m_L, 0);
	luaopen_ajson(m_L); lua_settop(m_L, 0);
	luaopen_lfs(m_L); lua_settop(m_L, 0);
	luaopen_base64(m_L); lua_settop(m_L, 0);
	luaopen_csv(m_L); lua_settop(m_L, 0);
	luaopen_md5(m_L); lua_settop(m_L, 0);
	luaopen_utf8(m_L); lua_settop(m_L, 0);
	luaopen_timer(m_L); lua_settop(m_L, 0);
	luaopen_sqlite3(m_L); lua_settop(m_L, 0);

	luabridge::getGlobalNamespace(m_L)
		.beginClass<MessageReadFactory>("__CPPAPIMessageReadFactory")
		.addConstructor<void(*)()>()
		.addFunction("ReadFromStdFile", &MessageReadFactory::ReadFromStdFile)
		.addFunction("ReadBool", &MessageReadFactory::ReadBool)
		.addFunction("ReadInt", &MessageReadFactory::ReadInt)
		.addFunction("ReadI64", &MessageReadFactory::ReadLongLong)
		.addFunction("ReadString", &MessageReadFactory::ReadString)
		.addFunction("ReadDouble", &MessageReadFactory::ReadDouble)
		.addFunction("GetReadSize", &MessageReadFactory::GetReadSize)
		.addFunction("GetDataSize", &MessageReadFactory::GetDataSize)
		.endClass();

	luabridge::getGlobalNamespace(m_L)
		.beginClass<MessageWriteFactory>("__CPPAPIMessageWriteFactory")
		.addConstructor<void(*)()>()
		.addFunction("WriteToStdFile", &MessageWriteFactory::WriteToStdFile)
		.addFunction("SetID", &MessageWriteFactory::SetID)
		.addFunction("SetRpcID", &MessageWriteFactory::SetRpcID)
		.addFunction("ResetOffset", &MessageWriteFactory::ResetOffset)
		.addFunction("WriteBool", &MessageWriteFactory::WriteBool)
		.addFunction("WriteInt", &MessageWriteFactory::WriteInt)
		.addFunction("WriteI64", &MessageWriteFactory::WriteLongLong)
		.addFunction("WriteString", &MessageWriteFactory::WriteString)
		.addFunction("WriteDouble", &MessageWriteFactory::WriteDouble)
		.addFunction("SetInt", &MessageWriteFactory::SetInt)
		.addFunction("GetOffset", &MessageWriteFactory::GetOffset)
		.endClass();

	RegisterImpl();
}

void ScriptSystem::Release()
{
	// close lua state
	if (m_L)
	{
		lua_close(m_L);
		m_L = nullptr;
	}
}

ScriptSystem::ScriptSystem() : m_L(nullptr)
{
}

ScriptSystem::~ScriptSystem()
{
	Release();
}

void ScriptSystem::Log(const char* content, short level)
{
	std::string real;
	real.append("[").append(m_module_title).append("] ");
	real.append(content);
	if (level == LogHelper::LL_ERROR)
	{
		real.append("\n");
		CallStack(m_L, 0, real);
	}
	
	g_LogSystem.Log(real.c_str(), level);
}

void ScriptSystem::CallStack(lua_State* L, int n, std::string& stack_info)
{
	if (n >= 100) return;
	lua_Debug ar;
	if (lua_getstack(L, n, &ar) != 1) return;

	lua_getinfo(L, "nSlu", &ar);

	char text[32] = { 0 };
#ifdef _WIN32
	sprintf_s(text, "%d", ar.currentline);
#else
	sprintf(text, "%d", ar.currentline);
#endif

	if (ar.name)
		stack_info.append(ar.name).append("() : line ").append(text).append(" [").append(ar.source).append("]\n");
	else
		stack_info.append("unknown : line ").append(text).append(" [").append(ar.source).append("]\n");

	CallStack(L, n + 1, stack_info);
}

int ScriptSystem::OnError(lua_State* L)
{
	std::string content;
	const char* error = lua_tostring(L, -1);
	if (error != nullptr) content = error;
	lua_pop(L, 1);

	content.append("\n");
	CallStack(L, 0, content);
	ALITTLE_SCRIPT_ERROR(content);

	return 0;
}

void ScriptSystem::PrintError(lua_State* L, const char* name, const char* message)
{
	std::string content = name;
	content.append("\n");
	content.append(message);
	lua_pop(L, 1);
	content.append("\n");
	CallStack(L, 0, content);
	ALITTLE_SCRIPT_ERROR(content);
}

void ScriptSystem::RunScript(const char* script, size_t len, const char* file_path)
{
	lua_pushcclosure(m_L, OnError, 0);
	int errfunc = lua_gettop(m_L);
	std::string show_path;
	if (file_path != nullptr) show_path = file_path;
	if (show_path.size() > 48) show_path = show_path.substr(show_path.size() - 48);
	if (luaL_loadbuffer(m_L, script, len, show_path.c_str()) == 0)
	{
		lua_pushstring(m_L, file_path);
		lua_pcall(m_L, 1, 1, errfunc);
	}
	else
		PrintError(m_L, file_path, lua_tostring(m_L, -1));
	lua_remove(m_L, errfunc);
	lua_pop(m_L, 1);
}

bool ScriptSystem::Require(const char* file_path)
{
	std::string lua_path = file_path;
	lua_path += ".lua";

	if (m_script_set.count(lua_path) > 0) return true;
	m_script_set.insert(lua_path);

	std::vector<char> content;
	if (!LoadFile(lua_path.c_str(), content))
	{
		ALITTLE_ERROR("can't find lua file:" << lua_path);
		return false;
	}

	std::string start_text = "-- ALittle Generate Lua";
	if (content.size() < start_text.size() || start_text != std::string(content.data(), start_text.size()))
		CryptHelper::XXTeaDecodeMemory(content.data(), static_cast<int>(content.size()), 0);
	RunScript(content.data(), content.size(), lua_path.c_str());
	return true;
}

void ScriptSystem::RegisterImpl()
{
	// register script system
	luabridge::getGlobalNamespace(m_L)
		.beginClass<ScriptSystem>("__CPPAPIScriptSystem")
		.addFunction("Log", &ScriptSystem::Log)
		.addFunction("Require", &ScriptSystem::Require)
		.addFunction("RunScript", &ScriptSystem::RunScriptForLua)
		.addFunction("JSHash", &ScriptSystem::JSHash)
		.endClass();

	luabridge::setGlobal(m_L, this, "__CPPAPI_ScriptSystem");

	std::string require = "core_require = function(path) return __CPPAPI_ScriptSystem:Require(path) end";
	RunScript(require.c_str(), require.size(), "ALittleBuild");
}

bool ScriptSystem::LoadFile(const char* file_path, std::vector<char>& content)
{
	return FileHelper::LoadStdFile(file_path, content);
}

int ScriptSystem::JSHash(const char* value)
{
	return CryptHelper::JSHash(value);
}

} // ALittle
