#include "ALittleScriptPropertyValueMethodTemplateReference.h"

ABnfGuessError ALittleScriptPropertyValueMethodTemplateReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    if (element->GetAllTypeList().size() == 0) return ABnfGuessError(element, u8"����д����");

    return nullptr;
}
