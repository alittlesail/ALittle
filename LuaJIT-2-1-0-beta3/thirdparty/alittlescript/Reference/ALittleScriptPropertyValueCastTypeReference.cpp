#include "ALittleScriptPropertyValueCastTypeReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"

ABnfGuessError ALittleScriptPropertyValueCastTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto all_type = element->GetAllType();
    if (all_type != nullptr)
        return all_type->GuessTypes(guess_list);

    guess_list.resize(0);
    return ABnfGuessError(element, u8"ALittlePropertyValueCastType出现未知的子节点");
}

ABnfGuessError ALittleScriptPropertyValueCastTypeReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"重复定义");
    return nullptr;
}
