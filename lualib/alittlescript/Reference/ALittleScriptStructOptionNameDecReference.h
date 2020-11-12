#ifndef _ALITTLE_ALITTLESCRIPTSTRUCTOPTIONNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTSTRUCTOPTIONNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptStructOptionNameDecElement.h"

class ALittleScriptStructOptionNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptStructOptionNameDecElement>
{
public:
    ALittleScriptStructOptionNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptStructOptionNameDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptStructOptionNameDecReference(element); }
    int QueryClassificationTag(bool& blur) override
    {
        auto element = m_element.lock();
        if (element == nullptr) return 0;

        blur = false;
        auto text = element->GetElementText();
        if (text == "primary" || text == "unique" || text == "index")
            return ALittleScriptColorType::CTRL_KEYWORD;
        return ALittleScriptColorType::VAR_NAME;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTSTRUCTOPTIONNAMEDECREFERENCE_H_