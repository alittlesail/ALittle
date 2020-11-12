
#include "ALittleScriptFactoryClass.h" 
#include "ALittleScriptFileClass.h"
#include "../../alanguage/Model/ABnfElement.h"

ABnfReference* ALittleScriptFactoryClass::CreateReference(const ABnfElementPtr& element)
{
	return nullptr;
}

ABnfFile* ALittleScriptFactoryClass::CreateFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len)
{
	return new ALittleScriptFileClass(project, module_path, full_path, text, len, false);
}
