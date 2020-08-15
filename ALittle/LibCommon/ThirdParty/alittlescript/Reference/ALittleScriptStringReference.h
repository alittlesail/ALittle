
#ifndef _ALITTLE_ALITTLESCRIPTSTRINGREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTSTRINGREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptReturnExprElement.h"

class ALittleScriptStringReference : public ALittleScriptReferenceTemplate<ALittleScriptStringElement>
{
public:
    ALittleScriptStringReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptStringElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptStringReference(element); }
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::DEFAULT;
    }

    bool CanGotoDefinition() override
    {
        return false;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTSTRINGREFERENCE_H_