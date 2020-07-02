
#ifndef _ALITTLE_ALITTLESCRIPTFACTORYCLASS_H_
#define _ALITTLE_ALITTLESCRIPTFACTORYCLASS_H_

#include "../../alanguage/Index/ABnfFactory.h"

class ALittleScriptFactoryClass : public ABnfFactory
{
public:
    ABnfReference* CreateReference(ABnfElementPtr element) override;

    ABnfFile* CreateFile(ABnfProject* project, const std::string& full_path, const char* text, size_t len) override;
};

#endif // _ALITTLE_ALITTLESCRIPTFACTORYCLASS_H_
