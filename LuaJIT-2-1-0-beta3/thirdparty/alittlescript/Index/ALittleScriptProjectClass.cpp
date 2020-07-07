
#include "ALittleScriptProjectClass.h"

ALittleScriptProjectClass::ALittleScriptProjectClass(const std::string& full_path)
	: ABnfProject(full_path)
{
	m_language_set.insert("Lua");
	m_language_set.insert("JavaScript");
}

ALittleScriptProjectClass::~ALittleScriptProjectClass()
{
}

void ALittleScriptProjectClass::SetTargetLanguage(const std::string& language)
{
	m_target_language = language;
}

