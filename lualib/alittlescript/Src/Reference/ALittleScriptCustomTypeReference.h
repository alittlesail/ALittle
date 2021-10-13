
#ifndef _ALITTLE_ALITTLESCRIPTCUSTOMTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCUSTOMTYPEREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptCustomTypeDotIdNameElement.h"

class ALittleScriptCustomTypeReference : public ALittleScriptCustomTypeCommonReference
{
public:
    ALittleScriptCustomTypeReference(const ABnfElementPtr& p_element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptCustomTypeReference(element); }

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCUSTOMTYPEREFERENCE_H_