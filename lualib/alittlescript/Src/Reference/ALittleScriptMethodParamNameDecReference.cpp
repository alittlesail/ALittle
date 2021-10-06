#include "ALittleScriptMethodParamNameDecReference.h"

#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"

int ALittleScriptMethodParamNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::VAR_NAME;
}

ABnfGuessError ALittleScriptMethodParamNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    guess_list.resize(0);
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    const auto parent = element->GetParent();
    auto one_dec = std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(parent);
    if (one_dec != nullptr)
    {
        auto all_type = one_dec->GetAllType();
        if (all_type != nullptr)
            return all_type->GuessTypes(guess_list);
    }
    return nullptr;
}

ABnfGuessError ALittleScriptMethodParamNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"δ֪����");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"�ظ�����");
    return nullptr;
}
