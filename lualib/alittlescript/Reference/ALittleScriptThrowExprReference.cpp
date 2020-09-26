#include "ALittleScriptThrowExprReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptThrowExprReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"throw表达式不能没有参数");

    if (value_stat_list.size() != 1)
        return ABnfGuessError(element, u8"throw只有string一个参数");

    auto value_stat = value_stat_list[0];
    ABnfGuessPtr guess;
    auto error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess))
        return ABnfGuessError(value_stat, u8"throw表达式第一个参数必须是string类型");

    return nullptr;
}

ABnfGuessError ALittleScriptThrowExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"throw表达式不能没有参数");

    if (value_stat_list.size() != 1)
        return ABnfGuessError(element, u8"throw只有string一个参数");

    auto value_stat = value_stat_list[0];

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

    ABnfGuessPtr guess;
    error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessString>(guess))
        return ABnfGuessError(value_stat, u8"throw表达式第一个参数必须是string类型");

    return nullptr;
}
