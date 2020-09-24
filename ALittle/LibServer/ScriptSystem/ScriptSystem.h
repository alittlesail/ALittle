
#ifndef _ALITTLE_SCRIPTSYSTEM_H_
#define _ALITTLE_SCRIPTSYSTEM_H_

#include "Carp/carp_script.hpp"

namespace ALittle
{

class ScriptSystem : public CarpScript
{
public:
	void Setup();
	void Shutdown();
};

} // ALittle

#endif // _ALITTLE_SCRIPTSYSTEM_H_