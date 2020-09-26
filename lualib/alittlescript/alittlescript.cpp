
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include "alittlescript.h"
}

#include "Index/ALittleScriptFileClass.h"
#include "Index/ALittleScriptProjectClass.h"

void* create_alittlescript_project(const char* abnf_buffer)
{
	auto* project = new ALittleScriptProjectClass();
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
	project_c->SetTargetLanguageUI(target_language);
	project_c->Add(std::bind(&ALittleScriptProjectClass::SetTargetLanguage, project_c, std::string(target_language)));
}

const char* alittlescriptproject_gettargetlanguage(void* project)
{
	auto* project_c = (ALittleScriptProjectClass*)project;
	return project_c->GetTargetLanguageUI().c_str();
}

void alittlescriptproject_generate(void* project, int query_id, const char* full_path)
{
	auto* project_c = (ALittleScriptProjectClass*)project;
	project_c->Add(std::bind(&ALittleScriptProjectClass::Generate, project_c, query_id, std::string(full_path)));
}

void* create_alittlescript_file(void* project, const char* module_path, const char* full_path, const char* text, size_t len)
{
	return new ALittleScriptFileClass((ABnfProject*)project, module_path, full_path, text, len, true);
}

void delete_alittlescript_file(void* file)
{
	delete ((ALittleScriptFileClass*)file);
}
