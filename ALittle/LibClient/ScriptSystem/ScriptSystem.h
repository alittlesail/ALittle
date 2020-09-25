
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
	
private:
	ScriptSystem();
	~ScriptSystem();
};

} // ALittle

#define g_ScriptSystem	ALittle::ScriptSystem::Instance()

#endif // _ALITTLE_SCRIPTSYSTEMEX_H_
