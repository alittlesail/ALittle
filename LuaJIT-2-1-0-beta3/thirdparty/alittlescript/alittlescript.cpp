
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "alittlescript.h"
}

#include "Index/ALittleScriptFactoryClass.h"
#include "Index/ALittleScriptFileClass.h"
#include "Index/ALittleScriptProjectClass.h"

void* create_alittlescript_factory()
{
	return new ALittleScriptFactoryClass();
}

void delete_alittlescript_factory(void* factory)
{
	delete ((ALittleScriptFactoryClass*)factory);
}

void* create_alittlescript_file(void* project, const char* full_path, void* abnf, const char* text, size_t len)
{
	return new ALittleScriptFileClass((ABnfProject*)project, full_path, (ABnf*)abnf, text, len);
}

void delete_alittlescript_file(void* file)
{
	delete ((ALittleScriptFileClass*)file);
}

void* create_alittlescript_project(const char* full_path)
{
	return new ALittleScriptProjectClass(full_path);
}

void delete_alittlescript_project(void* file)
{
	delete ((ALittleScriptProjectClass*)file);
}
