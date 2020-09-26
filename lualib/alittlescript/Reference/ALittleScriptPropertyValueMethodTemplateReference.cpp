#include "ALittleScriptPropertyValueMethodTemplateReference.h"

ABnfGuessError ALittleScriptPropertyValueMethodTemplateReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    if (element->GetAllTypeList().size() == 0) return ABnfGuessError(element, u8"请填写类型");

    return nullptr;
}
