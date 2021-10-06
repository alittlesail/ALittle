#include "ALittleScriptElseIfConditionReference.h"

#include "../Index/ALittleScriptUtility.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ABnfGuessError ALittleScriptElseIfConditionReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto value_stat = element->GetValueStat();
    if (value_stat == nullptr)
        return ABnfGuessError(element, u8"没有条件表达式");

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

    ABnfGuessPtr guess;
    error = value_stat->GuessType(guess);
    if (error) return error;
    if (std::dynamic_pointer_cast<ALittleScriptGuessBool>(guess)) return nullptr;

    return ABnfGuessError(element, u8"这里必须是一个bool表达式");
}
