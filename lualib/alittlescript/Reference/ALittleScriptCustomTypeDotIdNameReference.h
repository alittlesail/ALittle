
#ifndef _ALITTLE_ALITTLESCRIPTCUSTOMTYPEDOTIDNAMEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCUSTOMTYPEDOTIDNAMEREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptCustomTypeDotIdNameElement.h"

class ALittleScriptCustomTypeDotIdNameReference : public ALittleScriptCustomTypeCommonReference
{
public:
    ALittleScriptCustomTypeDotIdNameReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptCustomTypeDotIdNameReference(element); }

    int QueryClassificationTag(bool& blur) override;
};

#endif // _ALITTLE_ALITTLESCRIPTCUSTOMTYPEDOTIDNAMEREFERENCE_H_