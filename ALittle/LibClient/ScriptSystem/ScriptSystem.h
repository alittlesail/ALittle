
#ifndef _ALITTLE_SCRIPTSYSTEMEX_H_
#define _ALITTLE_SCRIPTSYSTEMEX_H_

#include "Carp/carp_script.hpp"
#include <map>

namespace ALittle
{

class ScriptSystem : public CarpScript
{
public:
	static ScriptSystem& Instance();

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
	bool Require(const char* file_path) { return ScriptSystem::Require(file_path); }
	void RunScriptForLua(const char* script, const char* file_path) { ScriptSystem::RunScriptForLua(file_path); }
#endif
	
protected:
	virtual bool LoadFile(const char* file_path, std::vector<char>& content) override;

private:
	ScriptSystem();
	~ScriptSystem();

private:
	std::string m_string;
};

} // ALittle

#define g_ScriptSystem	ALittle::ScriptSystem::Instance()

#endif // _ALITTLE_SCRIPTSYSTEMEX_H_
