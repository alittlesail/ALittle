
#ifndef _ALITTLE_ALITTLESCRIPTREGEXREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTREGEXREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptRegexElement.h"

class ALittleScriptRegexReference : public ALittleScriptReferenceTemplate<ALittleScriptRegexElement>
{
public:
    ALittleScriptRegexReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptRegexElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptRegexReference(element); }
    bool CanGotoDefinition() override
    {
        const auto element = m_element.lock();
        if (element == nullptr) return false;

        auto parent = element->GetParent();
        if (parent == nullptr) return false;
        return parent->GetReference()->CanGotoDefinition();
    }
};

#endif // _ALITTLE_ALITTLESCRIPTREGEXREFERENCE_H_