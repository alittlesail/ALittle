
#ifndef _ALITTLE_ALITTLESCRIPTCLASSSETTERDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSSETTERDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassSetterDecElement.h"

class ALittleScriptClassSetterDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassSetterDecElement>
{
public:
    ALittleScriptClassSetterDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptClassSetterDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptClassSetterDecReference(element); }
    ABnfGuessError CheckError() override
    {
        auto element = m_element.lock();
        if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
        if (element->GetMethodNameDec() == nullptr)
            return ABnfGuessError(element, u8"没有函数名");

        if (element->GetMethodBodyDec() == nullptr)
            return ABnfGuessError(element, u8"没有函数体");
        return nullptr;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSSETTERDECREFERENCE_H_