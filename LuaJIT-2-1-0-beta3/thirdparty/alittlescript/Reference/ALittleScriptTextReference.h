#ifndef _ALITTLE_ALITTLESCRIPTTEXTREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTTEXTREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptTextElement.h"

class ALittleScriptTextReference : public ALittleScriptReferenceTemplate<ALittleScriptTextElement>
{
public:
    ALittleScriptTextReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptTextElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptTextReference(element); }
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::TEXT;
    }

    bool CanGotoDefinition() override
    {
        return false;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTTEXTREFERENCE_H_