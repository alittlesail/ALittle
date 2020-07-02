
#include "ALittleScriptFactoryClass.h" 
#include "ALittleScriptFileClass.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"

ABnfReference* ALittleScriptFactoryClass::CreateReference(ABnfElementPtr element)
{
	return nullptr;
}

ABnfFile* ALittleScriptFactoryClass::CreateFile(ABnfProject* project, const std::string& full_path, const char* text, size_t len)
{
	return new ALittleScriptFileClass(project, full_path, text, len, false);
}
