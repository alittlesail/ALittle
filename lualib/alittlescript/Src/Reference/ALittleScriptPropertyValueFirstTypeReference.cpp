#include "ALittleScriptPropertyValueFirstTypeReference.h"

#include "../Generate/ALittleScriptPropertyValueCustomTypeElement.h"
#include "../Generate/ALittleScriptPropertyValueThisTypeElement.h"
#include "../Generate/ALittleScriptPropertyValueCastTypeElement.h"

ABnfGuessError ALittleScriptPropertyValueFirstTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    if (element->GetPropertyValueCastType() != nullptr)
        return element->GetPropertyValueCastType()->GuessTypes(guess_list);
    else if (element->GetPropertyValueCustomType() != nullptr)
        return element->GetPropertyValueCustomType()->GuessTypes(guess_list);
    else if (element->GetPropertyValueThisType() != nullptr)
        return element->GetPropertyValueThisType()->GuessTypes(guess_list);
    guess_list.resize(0);
    return nullptr;
}
