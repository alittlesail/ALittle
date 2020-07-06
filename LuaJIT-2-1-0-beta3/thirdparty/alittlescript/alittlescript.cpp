
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "alittlescript.h"
}

#include "Index/ALittleScriptFileClass.h"
#include "Index/ALittleScriptProjectClass.h"

void* create_alittlescript_project(const char* full_path, const char* abnf_buffer)
{
	auto* project = new ALittleScriptProjectClass(full_path);
	project->Start(abnf_buffer);
	return project;
}

void delete_alittlescript_project(void* file)
{
	delete ((ALittleScriptProjectClass*)file);
}

void alittlescriptproject_settargetlanguage(void* project, const char* target_language)
{
	auto* project_c = (ALittleScriptProjectClass*)project;
	project_c->Add(std::bind(&ALittleScriptProjectClass::SetTargetLanguage, project_c, target_language));
}

void* create_alittlescript_file(void* project, const char* full_path, const char* text, size_t len)
{
	return new ALittleScriptFileClass((ABnfProject*)project, full_path, text, len, true);
}

void delete_alittlescript_file(void* file)
{
	delete ((ALittleScriptFileClass*)file);
}
