
#ifndef _ALITTLE_ABNFFACTORYCLASS_H_
#define _ALITTLE_ABNFFACTORYCLASS_H_

#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfFactory.h"

class ABnfFactoryClass : public ABnfFactory
{
public:
    ABnfReference* CreateReference(ABnfElementPtr element) override;

    std::string GetDotExt() override { return ".abnf"; }

};

#endif // _ALITTLE_ABNFFACTORYCLASS_H_
