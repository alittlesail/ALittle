#include "ALittleScriptPropertyValueReference.h"

#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"
#include "../Generate/ALittleScriptPropertyValueFirstTypeElement.h"

ABnfGuessError ALittleScriptPropertyValueReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    const auto& suffixList = element->GetPropertyValueSuffixList();
    if (suffixList.size() == 0)
    {
        auto first_type = element->GetPropertyValueFirstType();
        if (first_type != nullptr)
            return first_type->GuessTypes(guess_list);
    }
    else
    {
        return suffixList[suffixList.size() - 1]->GuessTypes(guess_list);
    }
    guess_list.resize(0);
    return nullptr;
}
