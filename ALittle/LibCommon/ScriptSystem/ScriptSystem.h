
#ifndef _ALITTLE_SCRIPTSYSTEM_H_
#define _ALITTLE_SCRIPTSYSTEM_H_

#ifdef __EMSCRIPTEN__
#include "lua.hpp"
#else
#include "LuaJIT-2.1.0-beta3/src/lua.hpp"
#endif
#include "LuaBridge/Source/LuaBridge/LuaBridge.h"
#include <string>
#include <set>
#include "ALittle/LibCommon/Helper/LogHelper.h"

namespace ALittle
{

class ScriptSystem
{
public:
	void Init(const std::string& module_title);
	void Release();

public:
	// 运行脚本文件
	void RunScript(const char* script, size_t len, const char* file_path);
	void RunScriptForLua(const char* script, const char* file_path) { RunScript(script, strlen(script), file_path); }

private:
	static void CallStack(lua_State* L, int n, std::string& stack_info);
	static int OnError(lua_State* L);
	static void PrintError(lua_State* L, const char* name, const char* message);

	// 边界条件
	inline int InvokePush(int count)
	{
		return count;
	}

	// 必须使用尾递归的写法，否则调用会产生非常大的代价
	template<typename T1, typename ...T2>
	inline int InvokePush(int count, T1 arg, T2 ...args)
	{
		luabridge::push(m_L, arg);
		return InvokePush(count + 1, args...);
	}

public:
	template<typename ...T>
	void Invoke(const char* name, T ...args)
	{
		if (m_L == nullptr) return;

		lua_pushcclosure(m_L, OnError, 0);
		int errfunc = lua_gettop(m_L);

		lua_getglobal(m_L, name);
		if (lua_isfunction(m_L, -1))
		{
			int count = InvokePush(0, args...);
			lua_pcall(m_L, count, 0, errfunc);
		}
		else
		{
			std::string content;
			content.append("attempt to call global '");
			content.append(name);
			content.append("' (not a function)");
			ALITTLE_SCRIPT_ERROR(content);
		}

		lua_remove(m_L, errfunc);
	}

	bool IsFunction(const char* name)
	{
		if (m_L == nullptr) return false;
		lua_getglobal(m_L, name);
		bool result = lua_isfunction(m_L, -1) != 0;
		lua_remove(m_L, -1);
		return result;
	}

	void InvokeMain(const char* name, const std::string& module_path, int argc, char* argv[])
	{
		if (m_L == nullptr) return;

		lua_pushcclosure(m_L, OnError, 0);
		int errfunc = lua_gettop(m_L);

		lua_getglobal(m_L, name);
		if (lua_isfunction(m_L, -1))
		{
			luabridge::push(m_L, module_path.c_str());
			for (int i = 1; i < argc; ++i)
				luabridge::push(m_L, static_cast<const char*>(argv[i]));
			lua_pcall(m_L, argc, 0, errfunc);
		}
		else
		{
			std::string content;
			content.append("attempt to call global '");
			content.append(name);
			content.append("' (not a function)");
			ALITTLE_SCRIPT_ERROR(content);
		}

		lua_remove(m_L, errfunc);
	}

public:
	lua_State* GetLuaState() { return m_L; }

protected:	
	lua_State* m_L;					// lua state

public:
	ScriptSystem();
	virtual ~ScriptSystem();

public:
	bool Require(const char* file_path);

protected:
	void Log(const char* content, short level);
	int JSHash(const char* value);
	
private:
	virtual void RegisterImpl();
	virtual bool LoadFile(const char* file_path, std::vector<char>& content);

protected:
	std::string m_string;

protected:
	std::string m_module_title;
	std::set<std::string> m_script_set;
};

} // ALittle

#endif // _ALITTLE_SCRIPTSYSTEM_H_
