
#include "ALittleScriptProjectClass.h"

ALittleScriptProjectClass::ALittleScriptProjectClass(const std::string& full_path)
	: ABnfProject(full_path)
{
}

ALittleScriptProjectClass::~ALittleScriptProjectClass()
{
}

void ALittleScriptProjectClass::SetTargetLanguage(const std::string& language)
{
	m_target_language = language;
}

