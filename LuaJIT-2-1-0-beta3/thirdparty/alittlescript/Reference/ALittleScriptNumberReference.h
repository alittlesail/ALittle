
#ifndef _ALITTLE_ALITTLESCRIPTNUMBERREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTNUMBERREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptNumberElement.h"

class ALittleScriptNumberReference : public ALittleScriptReferenceTemplate<ALittleScriptNumberElement>
{
public:
    ALittleScriptNumberReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptNumberElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptNumberReference(element); }

    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::ALittleScriptDefault;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTNUMBERREFERENCE_H_