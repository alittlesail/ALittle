
#ifndef _ALITTLE_ALITTLESCRIPTCUSTOMTYPENAMEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCUSTOMTYPENAMEREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptCustomTypeDotIdNameElement.h"

class ALittleScriptCustomTypeNameReference : public ALittleScriptCustomTypeCommonReference
{
public:
    ALittleScriptCustomTypeNameReference(ABnfElementPtr element) : ALittleScriptCustomTypeCommonReference(std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(element->GetParent()), element)
    {
    }

    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::ALittleScriptCustomName;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTCUSTOMTYPENAMEREFERENCE_H_