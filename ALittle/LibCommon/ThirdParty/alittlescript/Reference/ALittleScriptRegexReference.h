
#ifndef _ALITTLE_ALITTLESCRIPTREGEXREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTREGEXREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptRegexElement.h"

class ALittleScriptRegexReference : public ALittleScriptReferenceTemplate<ALittleScriptRegexElement>
{
public:
    ALittleScriptRegexReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptRegexElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptRegexReference(element); }
    bool CanGotoDefinition() override
    {
        auto element = m_element.lock();
        if (element == nullptr) return false;

        auto parent = element->GetParent();
        if (parent == nullptr) return false;
        return parent->GetReference()->CanGotoDefinition();
    }
};

#endif // _ALITTLE_ALITTLESCRIPTREGEXREFERENCE_H_