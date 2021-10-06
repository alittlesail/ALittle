#include "ALittleScriptPropertyValueSuffixReference.h"

#include "../Generate/ALittleScriptPropertyValueMethodCallElement.h"
#include "../Generate/ALittleScriptPropertyValueDotIdElement.h"
#include "../Generate/ALittleScriptPropertyValueBracketValueElement.h"

ABnfGuessError ALittleScriptPropertyValueSuffixReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    if (element->GetPropertyValueMethodCall() != nullptr)
        return element->GetPropertyValueMethodCall()->GuessTypes(guess_list);
    else if (element->GetPropertyValueDotId() != nullptr)
        return element->GetPropertyValueDotId()->GuessTypes(guess_list);
    else if (element->GetPropertyValueBracketValue() != nullptr)
        return element->GetPropertyValueBracketValue()->GuessTypes(guess_list);
    guess_list.resize(0);
    return nullptr;
}
