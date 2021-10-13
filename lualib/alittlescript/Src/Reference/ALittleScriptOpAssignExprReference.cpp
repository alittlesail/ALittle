#include "ALittleScriptOpAssignExprReference.h"

#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptOpAssignElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"

#include "../Guess/ALittleScriptGuessReturnTail.h"
#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ABnfGuessError ALittleScriptOpAssignExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    const auto& property_value_list = element->GetPropertyValueList();
    auto value_stat = element->GetValueStat();
    if (value_stat == nullptr)
    {
        if (property_value_list.size() != 1)
            return ABnfGuessError(element, u8"没有赋值表达式时，只能是一个函数调用");
        auto property_value = property_value_list[0];
        const auto& suffix_list = property_value->GetPropertyValueSuffixList();
        if (suffix_list.size() == 0)
            return ABnfGuessError(element, u8"没有赋值表达式时，只能是一个函数调用");
        auto suffix = suffix_list[suffix_list.size() - 1];
        if (suffix->GetPropertyValueMethodCall() == nullptr)
            return ABnfGuessError(element, u8"没有赋值表达式时，只能是一个函数调用");
        return nullptr;
    }

    if (property_value_list.empty()) return nullptr;

    // 如果返回值只有一个函数调用
    if (property_value_list.size() > 1)
    {
        if (value_stat == nullptr)
            return ABnfGuessError(element, u8"调用的函数没有返回值");
        // 获取右边表达式的
        std::vector<ABnfGuessPtr> method_call_guess_list;
        auto guess_error = value_stat->GuessTypes(method_call_guess_list);
        if (guess_error) return guess_error;
        if (method_call_guess_list.size() == 0)
            return ABnfGuessError(value_stat, u8"调用的函数没有返回值");

        const bool hasTail = std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(method_call_guess_list[method_call_guess_list.size() - 1]) != nullptr;
        if (hasTail)
        {
            // 不做检查
        }
        else
        {
            if (method_call_guess_list.size() < property_value_list.size())
                return ABnfGuessError(value_stat, u8"调用的函数返回值数量少于定义的变量数量");
        }

        for (size_t i = 0; i < property_value_list.size(); ++i)
        {
            auto pair_dec = property_value_list[i];
            if (i >= method_call_guess_list.size()) break;
            if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(method_call_guess_list[i])) break;
            ABnfGuessPtr pair_dec_guess;
            guess_error = pair_dec->GuessType(pair_dec_guess);
            if (guess_error) return guess_error;
            guess_error = ALittleScriptOp::GuessTypeEqual(pair_dec_guess, value_stat, method_call_guess_list[i], true, false);
            if (guess_error)
                return ABnfGuessError(value_stat, u8"等号左边的第" + std::to_string(i + 1) + u8"个变量数量和函数定义的返回值类型不相等:" + guess_error.error);
        }

        return nullptr;
    }

    auto op_assign = element->GetOpAssign();
    if (op_assign == nullptr)
        return ABnfGuessError(element, u8"没有赋值符号");
    const auto& op_string = op_assign->GetElementText();

    ABnfGuessPtr pair_guess;
    auto error = property_value_list[0]->GuessType(pair_guess);
    if (error) return error;
    ABnfGuessPtr value_guess;
    error = value_stat->GuessType(value_guess);
    if (error) return error;
    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(pair_guess))
    {
        if (pair_guess->GetValue() != value_guess->GetValue() && value_guess->GetValue() != "null")
            return ABnfGuessError(value_stat, u8"等号左边的变量和表达式的类型不同");
    }

    if (op_string == "=")
    {
        error = ALittleScriptOp::GuessTypeEqual(pair_guess, value_stat, value_guess, true, false);
        if (error)
            return ABnfGuessError(error.element, u8"等号左边的变量和表达式的类型不同:" + error.error);
    }
    else
    {
        int return_count = 0;
        std::vector<ABnfGuessPtr> guess_list;
        error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;

        if (return_count != 1)
            return ABnfGuessError(value_stat, op_string + u8"右边必须只能是一个返回值");

        if (pair_guess->is_const)
            return ABnfGuessError(property_value_list[0], u8"const类型不能使用" + op_string + u8"运算符");

        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(pair_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessDouble>(pair_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(pair_guess))
            return ABnfGuessError(property_value_list[0], op_string + u8"左边必须是int, double, long");

        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(value_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessDouble>(value_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(value_guess))
            return ABnfGuessError(value_stat, op_string + u8"右边必须是int, double, long");
    }
    return nullptr;
}
