
#ifndef _ALITTLE_ABNFFACTORYCLASS_H_
#define _ALITTLE_ABNFFACTORYCLASS_H_

#include "../../alanguage/Index/ABnfFactory.h"

class ABnfFactoryClass : public ABnfFactory
{
public:
    ABnfReference* CreateReference(ABnfElementPtr element) override;

    ABnfFile* CreateFile(ABnfProject* project, const std::string& module_path, const std::string& full_path, const char* text, size_t len) override;
};

#endif // _ALITTLE_ABNFFACTORYCLASS_H_