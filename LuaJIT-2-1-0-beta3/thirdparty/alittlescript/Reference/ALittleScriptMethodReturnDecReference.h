
#ifndef _ALITTLE_ALITTLESCRIPTMETHODRETURNDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODRETURNDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodReturnDecElement.h"

class ALittleScriptMethodReturnDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodReturnDecElement>
{
public:
    ALittleScriptMethodReturnDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptMethodReturnDecElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptMethodReturnDecReference(element); }

    ABnfGuessError CheckError() override
    {
        auto element = m_element.lock();
        if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
        if (element->GetMethodReturnOneDecList().size() == 0)
            return ABnfGuessError(element, u8"没有定义返回值类型");
        return nullptr;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODRETURNDECREFERENCE_H_