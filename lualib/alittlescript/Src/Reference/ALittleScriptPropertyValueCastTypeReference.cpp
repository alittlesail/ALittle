#include "ALittleScriptPropertyValueCastTypeReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"

ABnfGuessError ALittleScriptPropertyValueCastTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    auto all_type = element->GetAllType();
    if (all_type != nullptr)
        return all_type->GuessTypes(guess_list);

    guess_list.resize(0);
    return ABnfGuessError(element, u8"ALittlePropertyValueCastType����δ֪���ӽڵ�");
}

ABnfGuessError ALittleScriptPropertyValueCastTypeReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");

    if (element->GetAllType() == nullptr) return ABnfGuessError(element, u8"����дҪת��������");
    if (element->GetValueFactorStat() == nullptr) return ABnfGuessError(element, u8"����дҪת���Ķ���");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"δ֪����");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"�ظ�����");
    return nullptr;
}
