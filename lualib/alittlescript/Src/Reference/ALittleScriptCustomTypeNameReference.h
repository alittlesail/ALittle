
#ifndef _ALITTLE_ALITTLESCRIPTCUSTOMTYPENAMEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCUSTOMTYPENAMEREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptCustomTypeDotIdNameElement.h"

class ALittleScriptCustomTypeNameReference : public ALittleScriptCustomTypeCommonReference
{
public:
    ALittleScriptCustomTypeNameReference(const ABnfElementPtr& element) : ALittleScriptCustomTypeCommonReference(std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(element->GetParent()), element) { }
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptCustomTypeNameReference(element); }

    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::CUSTOM_NAME;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTCUSTOMTYPENAMEREFERENCE_H_