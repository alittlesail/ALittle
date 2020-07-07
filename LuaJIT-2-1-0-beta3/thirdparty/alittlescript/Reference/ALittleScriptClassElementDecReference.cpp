#include "ALittleScriptClassElementDecReference.h"

#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptClassElementDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"½ÚµãÊ§Ð§");
    return ALittleScriptUtility::CheckError(element, element->GetModifierList());
}

int ALittleScriptClassElementDecReference::QueryClassificationTag(bool& blur)
{
    auto element = m_element.lock();
    if (element == nullptr) return 0;
    blur = !ALittleScriptUtility::IsLanguageEnable(element->GetModifierList());
    return 0;
}
