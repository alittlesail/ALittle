#include "ALittleScriptAllExprReference.h"

#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptAllExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ㶪ʧ");

    return ALittleScriptUtility::CheckError(element, element->GetModifierList());
}

int ALittleScriptAllExprReference::QueryClassificationTag(bool& blur)
{
    auto element = m_element.lock();
    if (element == nullptr) return 0;

    blur = !ALittleScriptUtility::IsLanguageEnable(element->GetModifierList());
    return 0;
}
