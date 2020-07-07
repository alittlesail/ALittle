
#ifndef _ALITTLE_ALITTLESCRIPTCLASSGETTERDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSGETTERDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassGetterDecElement.h"

class ALittleScriptClassGetterDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassGetterDecElement>
{
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

#endif // _ALITTLE_ALITTLESCRIPTCLASSGETTERDECREFERENCE_H_