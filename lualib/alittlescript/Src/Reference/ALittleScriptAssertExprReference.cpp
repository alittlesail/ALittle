#include "ALittleScriptAssertExprReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ABnfGuessError ALittleScriptAssertExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"assert���ʽ����û�в���");

    if (value_stat_list.size() != 2)
        return ABnfGuessError(element, u8"assert���ҽ���������������һ�����������ͣ��ڶ�����string");

    auto value_stat = value_stat_list[0];

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

    ABnfGuessPtr guess;
    error = value_stat->GuessType(guess);
    if (error) return error;

    value_stat = value_stat_list[1];

    return_count = 0;
    guess_list.resize(0);
    error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

    error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess))
        return ABnfGuessError(value_stat, u8"assert���ʽ�ڶ�������������string����");
    return nullptr;
}
