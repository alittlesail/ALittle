#include "ALittleScriptOp1ExprReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"

#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptOp1ExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto value_stat = element->GetValueStat();
    if (value_stat == nullptr) return nullptr;

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

    ABnfGuessPtr guess;
    error = value_stat->GuessType(guess);
    if (error) return error;

    if (guess->is_const)
        return ABnfGuessError(element, u8"const类型不能使用--或者++运算符");
    return nullptr;
}
