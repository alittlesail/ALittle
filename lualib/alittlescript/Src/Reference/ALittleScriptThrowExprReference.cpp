#include "ALittleScriptThrowExprReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptThrowExprReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"throw���ʽ����û�в���");

    if (value_stat_list.size() != 1)
        return ABnfGuessError(element, u8"throwֻ��stringһ������");

    auto value_stat = value_stat_list[0];
    ABnfGuessPtr guess;
    auto error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess))
        return ABnfGuessError(value_stat, u8"throw���ʽ��һ������������string����");

    return nullptr;
}

ABnfGuessError ALittleScriptThrowExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"throw���ʽ����û�в���");

    if (value_stat_list.size() != 1)
        return ABnfGuessError(element, u8"throwֻ��stringһ������");

    auto value_stat = value_stat_list[0];

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

    ABnfGuessPtr guess;
    error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess))
        return ABnfGuessError(value_stat, u8"throw���ʽ��һ������������string����");

    return nullptr;
}
