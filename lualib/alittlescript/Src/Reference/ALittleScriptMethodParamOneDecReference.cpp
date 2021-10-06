#include "ALittleScriptMethodParamOneDecReference.h"

#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptMethodParamOneDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    return ALittleScriptUtility::CheckError(element, element->GetModifierList());
}
