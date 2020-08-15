
#ifndef _ALITTLE_SCRIPTSYSTEMEX_H_
#define _ALITTLE_SCRIPTSYSTEMEX_H_

#include "ALittle/LibCommon/ScriptSystem/ScriptSystem.h"
#include <map>

namespace ALittle
{

class ScriptSystemEx : public ScriptSystem
{
public:
	static ScriptSystemEx& Instance();

public:
	void Setup();
	void Shutdown();

public:
	/**
	 * import engine script
     */
	void StartScript(std::string module_name, const std::string& debug_info);
	const char* FileMD5(const char* file_path);
	const char* BaseFilePath();
	const char* ExternalFilePath();

#ifdef __EMSCRIPTEN__
	void Log(const char* content, short level) { ScriptSystem::Log(content, level); }
	bool Require(const char* file_path) { return ScriptSystem::Require(file_path); }
	void RunScriptForLua(const char* script, const char* file_path) { ScriptSystem::RunScriptForLua(file_path); }
#endif
	
protected:
	virtual void RegisterImpl() override;
	virtual bool LoadFile(const char* file_path, std::vector<char>& content) override;

private:
	ScriptSystemEx();
	~ScriptSystemEx();
};

} // ALittle

#define g_ScriptSystem	ALittle::ScriptSystemEx::Instance()

#endif // _ALITTLE_SCRIPTSYSTEMEX_H_
