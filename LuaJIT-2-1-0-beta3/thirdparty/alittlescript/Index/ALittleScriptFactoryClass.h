
#ifndef _ALITTLE_ALITTLESCRIPTFACTORYCLASS_H_
#define _ALITTLE_ALITTLESCRIPTFACTORYCLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfFactory.h"

class ALittleScriptFactoryClass : public ABnfFactory
{
public:
    ABnfReference* CreateReference(ABnfElementPtr element) override;

    std::string GetDotExt() override { return ".alittle"; }

};

#endif // _ALITTLE_ALITTLESCRIPTFACTORYCLASS_H_
