
#ifndef _ALITTLE_ALITTLESCRIPTCUSTOMTYPEDOTIDREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCUSTOMTYPEDOTIDREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptCustomTypeDotIdNameElement.h"

class ALittleScriptCustomTypeDotIdReference : public ALittleScriptCustomTypeCommonReference
{
public:
    ALittleScriptCustomTypeDotIdReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptCustomTypeDotIdReference(element); }
};

#endif // _ALITTLE_ALITTLESCRIPTCUSTOMTYPEDOTIDREFERENCE_H_