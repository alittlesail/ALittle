#include "ALittleScriptOp.h"

#include "../Generate/ALittleScriptOp8SuffixElement.h"
#include "../Generate/ALittleScriptOp7SuffixElement.h"
#include "../Generate/ALittleScriptOp6SuffixElement.h"
#include "../Generate/ALittleScriptOp5SuffixElement.h"
#include "../Generate/ALittleScriptOp4SuffixElement.h"
#include "../Generate/ALittleScriptOp3SuffixElement.h"
#include "../Generate/ALittleScriptOp8Element.h"
#include "../Generate/ALittleScriptOp7Element.h"
#include "../Generate/ALittleScriptOp6Element.h"
#include "../Generate/ALittleScriptOp5Element.h"
#include "../Generate/ALittleScriptOp4Element.h"
#include "../Generate/ALittleScriptOp3Element.h"
#include "../Generate/ALittleScriptOp8SuffixEeElement.h"
#include "../Generate/ALittleScriptOp7SuffixEeElement.h"
#include "../Generate/ALittleScriptOp6SuffixEeElement.h"
#include "../Generate/ALittleScriptOp5SuffixEeElement.h"
#include "../Generate/ALittleScriptOp4SuffixEeElement.h"

#include "../Generate/ALittleScriptOp8SuffixExElement.h"
#include "../Generate/ALittleScriptOp7SuffixExElement.h"
#include "../Generate/ALittleScriptOp6SuffixExElement.h"
#include "../Generate/ALittleScriptOp5SuffixExElement.h"
#include "../Generate/ALittleScriptOp4SuffixExElement.h"
#include "../Generate/ALittleScriptOp3SuffixExElement.h"
#include "../Generate/ALittleScriptOp2SuffixExElement.h"

#include "../Generate/ALittleScriptOp8StatElement.h"
#include "../Generate/ALittleScriptOp7StatElement.h"
#include "../Generate/ALittleScriptOp6StatElement.h"
#include "../Generate/ALittleScriptOp5StatElement.h"
#include "../Generate/ALittleScriptOp4StatElement.h"
#include "../Generate/ALittleScriptOp3StatElement.h"
#include "../Generate/ALittleScriptOp2StatElement.h"
#include "../Generate/ALittleScriptOp2ValueElement.h"
#include "../Generate/ALittleScriptOp2Element.h"

#include "../Generate/ALittleScriptValueFactorStatElement.h"
#include "../Generate/ALittleScriptValueOpStatElement.h"
#include "../Generate/ALittleScriptStructDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"

#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessStruct.h"

#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptOp::GuessTypeForOp8Impl(const std::string& op_string, ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, ABnfElementPtr right_src, ABnfGuessPtr right_guess_type, std::shared_ptr<ALittleScriptOp8SuffixElement> op_8_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;

    if (!std::dynamic_pointer_cast<ALittleScriptGuessBool>(left_guess_type))
        return ABnfGuessError(left_src, op_string + u8"运算符左边必须是bool类型.不能是:" + left_guess_type->GetValue());

    if (!std::dynamic_pointer_cast<ALittleScriptGuessBool>(right_guess_type))
        return ABnfGuessError(right_src, op_string + u8"运算符右边边必须是bool类型.不能是:" + right_guess_type->GetValue());

    guess = ALittleScriptStatic::Inst().sBoolGuess;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp8(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp8SuffixElement> op_8_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    const auto& op_string = op_8_suffix->GetOp8()->GetElementText();

    ABnfGuessPtr suffix_guess_type;
    ABnfElementPtr last_src;

    auto value_factor_stat = op_8_suffix->GetValueFactorStat();
    auto op_2_value = op_8_suffix->GetOp2Value();
    if (value_factor_stat != nullptr)
    {
        auto error = value_factor_stat->GuessType(suffix_guess_type);
        if (error) return error;
        last_src = value_factor_stat;
    }
    else if (op_2_value != nullptr)
    {
        auto error = GuessType(op_2_value, suffix_guess_type);
        if (error) return error;
        last_src = op_2_value;
    }
    else
    {
        return ABnfGuessError(op_8_suffix, u8"未知的表达式");
    }

    const auto& suffix_ee_list = op_8_suffix->GetOp8SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        if (suffix_ee->GetOp3Suffix() != nullptr)
        {
            auto error = GuessTypeForOp3(last_src, suffix_guess_type, suffix_ee->GetOp3Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp3Suffix();
        }
        else if (suffix_ee->GetOp4Suffix() != nullptr)
        {
            auto error = GuessTypeForOp4(last_src, suffix_guess_type, suffix_ee->GetOp4Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp4Suffix();
        }
        else if (suffix_ee->GetOp5Suffix() != nullptr)
        {
            auto error = GuessTypeForOp5(last_src, suffix_guess_type, suffix_ee->GetOp5Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp5Suffix();
        }
        else if (suffix_ee->GetOp6Suffix() != nullptr)
        {
            auto error = GuessTypeForOp6(last_src, suffix_guess_type, suffix_ee->GetOp6Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp6Suffix();
        }
        else if (suffix_ee->GetOp7Suffix() != nullptr)
        {
            auto error = GuessTypeForOp7(last_src, suffix_guess_type, suffix_ee->GetOp7Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp7Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ee, u8"未知的表达式");
        }
    }

    return GuessTypeForOp8Impl(op_string, left_src, left_guess_type, last_src, suffix_guess_type, op_8_suffix, guess);
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp7(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp7SuffixElement> op_7_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    const auto& op_string = op_7_suffix->GetOp7()->GetElementText();

    ABnfGuessPtr suffix_guess_type;
    ABnfElementPtr last_src;

    auto value_factor_stat = op_7_suffix->GetValueFactorStat();
    auto op_2_value = op_7_suffix->GetOp2Value();
    if (value_factor_stat != nullptr)
    {
        auto error = value_factor_stat->GuessType(suffix_guess_type);
        if (error) return error;
        last_src = value_factor_stat;
    }
    else if (op_2_value != nullptr)
    {
        auto error = GuessType(op_2_value, suffix_guess_type);
        if (error) return error;
        last_src = op_2_value;
    }
    else
    {
        return ABnfGuessError(op_7_suffix, u8"未知的表达式");
    }

    const auto& suffix_ee_list = op_7_suffix->GetOp7SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        if (suffix_ee->GetOp3Suffix() != nullptr)
        {
            auto error = GuessTypeForOp3(last_src, suffix_guess_type, suffix_ee->GetOp3Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp3Suffix();
        }
        else if (suffix_ee->GetOp4Suffix() != nullptr)
        {
            auto error = GuessTypeForOp4(last_src, suffix_guess_type, suffix_ee->GetOp4Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp4Suffix();
        }
        else if (suffix_ee->GetOp5Suffix() != nullptr)
        {
            auto error = GuessTypeForOp5(last_src, suffix_guess_type, suffix_ee->GetOp5Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp5Suffix();
        }
        else if (suffix_ee->GetOp6Suffix() != nullptr)
        {
            auto error = GuessTypeForOp6(last_src, suffix_guess_type, suffix_ee->GetOp6Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp6Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ee, u8"未知的表达式");
        }
    }

    return GuessTypeForOp7Impl(op_string, left_src, left_guess_type, last_src, suffix_guess_type, op_7_suffix, guess);
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp6Impl(const std::string& op_string, ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, ABnfElementPtr right_src, ABnfGuessPtr right_guess_type, std::shared_ptr<ALittleScriptOp6SuffixElement> op_6_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    if (op_string == "==" || op_string == "!=")
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessAny>(left_guess_type) || left_guess_type->GetValue() == "null"
            || std::dynamic_pointer_cast<ALittleScriptGuessAny>(right_guess_type) || right_guess_type->GetValue() == "null")
        {
            guess = ALittleScriptStatic::Inst().sBoolGuess;
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessDouble>(left_guess_type))
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type)
                || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type)
                || std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type))
            {
                guess = ALittleScriptStatic::Inst().sBoolGuess;
                return nullptr;
            }
            return ABnfGuessError(right_src, op_string + u8"运算符左边是数字，那么右边必须是int,long,double,any,null类型.不能是:" + right_guess_type->GetValue());
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessString>(left_guess_type))
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessString>(right_guess_type))
            {
                guess = ALittleScriptStatic::Inst().sBoolGuess;
                return nullptr;
            }
            return ABnfGuessError(right_src, op_string + u8"运算符左边是字符串，那么右边必须是string,any,null类型.不能是:" + right_guess_type->GetValue());
        }

        guess = ALittleScriptStatic::Inst().sBoolGuess;
        return nullptr;
    }
    else
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessDouble>(left_guess_type))
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type))
            {
                guess = ALittleScriptStatic::Inst().sBoolGuess;
                return nullptr;
            }
            return ABnfGuessError(right_src, op_string + u8"运算符左边是数字，那么右边必须是int,long,double类型.不能是:" + right_guess_type->GetValue());
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessString>(left_guess_type))
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessString>(right_guess_type))
            {
                guess = ALittleScriptStatic::Inst().sBoolGuess;
                return nullptr;
            }
            return ABnfGuessError(right_src, op_string + u8"运算符左边是字符串，那么右边必须是string类型.不能是:" + right_guess_type->GetValue());
        }

        return ABnfGuessError(left_src, op_string + u8"运算符左边必须是int,long,double,string类型.不能是:" + left_guess_type->GetValue());
    }
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp6(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp6SuffixElement> op_6_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    const auto& op_string = op_6_suffix->GetOp6()->GetElementText();

    ABnfGuessPtr suffix_guess_type;
    ABnfElementPtr last_src;

    auto value_factor_stat = op_6_suffix->GetValueFactorStat();
    auto op_2_value = op_6_suffix->GetOp2Value();
    if (value_factor_stat != nullptr)
    {
        auto error = value_factor_stat->GuessType(suffix_guess_type);
        if (error) return error;
        last_src = value_factor_stat;
    }
    else if (op_2_value != nullptr)
    {
        auto error = GuessType(op_2_value, suffix_guess_type);
        if (error) return error;
        last_src = op_2_value;
    }
    else
    {
        return ABnfGuessError(op_6_suffix, u8"未知的表达式");
    }

    const auto& suffix_ee_list = op_6_suffix->GetOp6SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        if (suffix_ee->GetOp3Suffix() != nullptr)
        {
            auto error = GuessTypeForOp3(last_src, suffix_guess_type, suffix_ee->GetOp3Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp3Suffix();
        }
        else if (suffix_ee->GetOp4Suffix() != nullptr)
        {
            auto error = GuessTypeForOp4(last_src, suffix_guess_type, suffix_ee->GetOp4Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp4Suffix();
        }
        else if (suffix_ee->GetOp5Suffix() != nullptr)
        {
            auto error = GuessTypeForOp5(last_src, suffix_guess_type, suffix_ee->GetOp5Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp5Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ee, u8"未知的表达式");
        }
    }
    return GuessTypeForOp6Impl(op_string, left_src, left_guess_type, last_src, suffix_guess_type, op_6_suffix, guess);
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp5Impl(const std::string& op_string, ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, ABnfElementPtr right_src, ABnfGuessPtr right_guess_type, std::shared_ptr<ALittleScriptOp5SuffixElement> op_5_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    bool left_check = std::dynamic_pointer_cast<ALittleScriptGuessInt>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessDouble>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessString>(left_guess_type);
    if (!left_check)
        return ABnfGuessError(left_src, op_string + u8"运算符左边必须是int,long,double,string类型.不能是:" + left_guess_type->GetValue());

    bool right_check = std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessString>(right_guess_type);
    if (!right_check)
        return ABnfGuessError(right_src, op_string + u8"运算符右边必须是int,long,double,string类型.不能是:" + right_guess_type->GetValue());

    if (!(std::dynamic_pointer_cast<ALittleScriptGuessString>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessString>(right_guess_type)))
        return ABnfGuessError(left_src, op_string + u8"运算符左边和右边至少一个是string类型.不能是:" + left_guess_type->GetValue() + u8"和" + right_guess_type->GetValue());

    guess = ALittleScriptStatic::Inst().sStringGuess;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp5(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp5SuffixElement> op_5_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    const auto& op_string = op_5_suffix->GetOp5()->GetElementText();

    ABnfGuessPtr suffix_guess_type;
    ABnfElementPtr last_src;

    auto value_factor_stat = op_5_suffix->GetValueFactorStat();
    auto op_2_value = op_5_suffix->GetOp2Value();
    if (value_factor_stat != nullptr)
    {
        auto error = value_factor_stat->GuessType(suffix_guess_type);
        if (error) return error;
        last_src = value_factor_stat;
    }
    else if (op_2_value != nullptr)
    {
        auto error = GuessType(op_2_value, suffix_guess_type);
        if (error) return error;
        last_src = op_2_value;
    }
    else
    {
        return ABnfGuessError(op_5_suffix, u8"未知的表达式");
    }

    const auto& suffix_ee_list = op_5_suffix->GetOp5SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        if (suffix_ee->GetOp3Suffix() != nullptr)
        {
            auto error = GuessTypeForOp3(last_src, suffix_guess_type, suffix_ee->GetOp3Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp3Suffix();
        }
        else if (suffix_ee->GetOp4Suffix() != nullptr)
        {
            auto error = GuessTypeForOp4(last_src, suffix_guess_type, suffix_ee->GetOp4Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp4Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ee, u8"未知的表达式");
        }
    }

    return GuessTypeForOp5Impl(op_string, left_src, left_guess_type, last_src, suffix_guess_type, op_5_suffix, guess);
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp4Impl(const std::string& op_string, ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, ABnfElementPtr right_src, ABnfGuessPtr right_guess_type, std::shared_ptr<ALittleScriptOp4SuffixElement> op_4_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(left_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(left_guess_type))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type))
        {
            guess = left_guess_type;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type))
        {
            guess = right_guess_type;
            return nullptr;
        }
        else
            return ABnfGuessError(right_src, op_string + u8"运算符右边必须是int,long,double类型.不能是:" + right_guess_type->GetValue());
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(left_guess_type))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type))
        {
            guess = left_guess_type;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type))
        {
            guess = right_guess_type;
            return nullptr;
        }

        else
            return ABnfGuessError(right_src, op_string + u8"运算符右边必须是int,long,double类型.不能是:" + right_guess_type->GetValue());
    }

    return ABnfGuessError(left_src, op_string + u8"运算符左边必须是int,long,double类型.不能是:" + left_guess_type->GetValue());
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp4(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp4SuffixElement> op_4_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    const auto& op_string = op_4_suffix->GetOp4()->GetElementText();

    ABnfGuessPtr suffix_guess_type;
    ABnfElementPtr last_src;

    auto value_factor_stat = op_4_suffix->GetValueFactorStat();
    auto op_2_value = op_4_suffix->GetOp2Value();
    if (value_factor_stat != nullptr)
    {
        auto error = value_factor_stat->GuessType(suffix_guess_type);
        if (error) return error;
        last_src = value_factor_stat;
    }
    else if (op_2_value != nullptr)
    {
        auto error = GuessType(op_2_value, suffix_guess_type);
        if (error) return error;
        last_src = op_2_value;
    }
    else
    {
        return ABnfGuessError(op_4_suffix, u8"未知的表达式");
    }

    const auto& suffix_ee_list = op_4_suffix->GetOp4SuffixEeList();
    for (auto& suffix_ee : suffix_ee_list)
    {
        if (suffix_ee->GetOp3Suffix() != nullptr)
        {
            auto error = GuessTypeForOp3(last_src, suffix_guess_type, suffix_ee->GetOp3Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ee->GetOp3Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ee, u8"未知的表达式");
        }
    }

    return GuessTypeForOp4Impl(op_string, left_src, left_guess_type, last_src, suffix_guess_type, op_4_suffix, guess);
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp3(ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, std::shared_ptr<ALittleScriptOp3SuffixElement> op_3_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    const auto& op_string = op_3_suffix->GetOp3()->GetElementText();

    ABnfGuessPtr right_guess_type;
    ABnfElementPtr right_src;

    auto value_factor_stat = op_3_suffix->GetValueFactorStat();
    auto op_2_value = op_3_suffix->GetOp2Value();
    if (value_factor_stat != nullptr)
    {
        auto error = value_factor_stat->GuessType(right_guess_type);
        if (error) return error;
        right_src = value_factor_stat;
    }
    else if (op_2_value != nullptr)
    {
        auto error = GuessType(op_2_value, right_guess_type);
        if (error) return error;
        right_src = op_2_value;
    }
    else
    {
        return ABnfGuessError(op_3_suffix, u8"未知的表达式");
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(left_guess_type))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type))
        {
            // 这个是特殊的
            if (op_string == "/")
            {
                guess = ALittleScriptStatic::Inst().sDoubleGuess;
                return nullptr;
            }
            guess = left_guess_type;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type))
        {
            // 这个是特殊的
            if (op_string == "/")
            {
                guess = ALittleScriptStatic::Inst().sDoubleGuess;
                return nullptr;
            }
            guess = right_guess_type;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type))
        {
            guess = right_guess_type;
            return nullptr;
        }
        else
        {
            return ABnfGuessError(right_src, op_string + u8"运算符右边必须是int,long,double类型.不能是:" + right_guess_type->GetValue());
        }
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessLong>(left_guess_type))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type))
        {
            // 这个是特殊的
            if (op_string == "/")
            {
                guess = ALittleScriptStatic::Inst().sDoubleGuess;
                return nullptr;
            }
            guess = left_guess_type;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type))
        {
            guess = right_guess_type;
            return nullptr;
        }
        else
        {
            return ABnfGuessError(right_src, op_string + u8"运算符右边必须是int,long,double类型.不能是:" + right_guess_type->GetValue());
        }
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(left_guess_type))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess_type) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess_type))
        {
            guess = left_guess_type;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess_type))
        {
            guess = right_guess_type;
            return nullptr;
        }
        else
            return ABnfGuessError(right_src, op_string + u8"运算符右边必须是int,long,double类型.不能是:" + right_guess_type->GetValue());
    }

    return ABnfGuessError(left_src, op_string + u8"运算符左边必须是int,long,double类型.不能是:" + left_guess_type->GetValue());
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp3StatElement> op_3_stat, ABnfGuessPtr& guess)
{
    guess = nullptr;
    ABnfGuessPtr factor_guess_type;
    auto error = value_factor_stat->GuessType(factor_guess_type);
    if (error) return error;

    ABnfGuessPtr suffix_guess_type;
    error = GuessTypeForOp3(value_factor_stat, factor_guess_type, op_3_stat->GetOp3Suffix(), suffix_guess_type);
    if (error) return error;

    ABnfElementPtr last_src = op_3_stat->GetOp3Suffix();
    const auto& suffix_ex_list = op_3_stat->GetOp3SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        if (suffix_ex->GetOp3Suffix() != nullptr)
        {
            error = GuessTypeForOp3(last_src, suffix_guess_type, suffix_ex->GetOp3Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp3Suffix();
        }
        else if (suffix_ex->GetOp4Suffix() != nullptr)
        {
            error = GuessTypeForOp4(last_src, suffix_guess_type, suffix_ex->GetOp4Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp4Suffix();
        }
        else if (suffix_ex->GetOp5Suffix() != nullptr)
        {
            error = GuessTypeForOp5(last_src, suffix_guess_type, suffix_ex->GetOp5Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp5Suffix();
        }
        else if (suffix_ex->GetOp6Suffix() != nullptr)
        {
            error = GuessTypeForOp6(last_src, suffix_guess_type, suffix_ex->GetOp6Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp6Suffix();
        }
        else if (suffix_ex->GetOp7Suffix() != nullptr)
        {
            error = GuessTypeForOp7(last_src, suffix_guess_type, suffix_ex->GetOp7Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp7Suffix();
        }
        else if (suffix_ex->GetOp8Suffix() != nullptr)
        {
            error = GuessTypeForOp8(last_src, suffix_guess_type, suffix_ex->GetOp8Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp8Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ex, u8"未知的表达式");
        }
    }

    guess = suffix_guess_type;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessTypes(std::shared_ptr<ALittleScriptValueOpStatElement> value_op_stat, std::vector<ABnfGuessPtr>& guess_list)
{
    guess_list.resize(0);
    auto value_factor_stat = value_op_stat->GetValueFactorStat();

    if (value_op_stat->GetOp3Stat() != nullptr)
    {
        guess_list.resize(0);
        ABnfGuessPtr guess;
        auto error = GuessType(value_factor_stat, value_op_stat->GetOp3Stat(), guess);
        if (error) return error;
        guess_list.push_back(guess);
        return nullptr;
    }
    else if (value_op_stat->GetOp4Stat() != nullptr)
    {
        guess_list.resize(0);
        ABnfGuessPtr guess;
        auto error = GuessType(value_factor_stat, value_op_stat->GetOp4Stat(), guess);
        if (error) return error;
        guess_list.push_back(guess);
        return nullptr;
    }
    else if (value_op_stat->GetOp5Stat() != nullptr)
    {
        guess_list.resize(0);
        ABnfGuessPtr guess;
        auto error = GuessType(value_factor_stat, value_op_stat->GetOp5Stat(), guess);
        if (error) return error;
        guess_list.push_back(guess);
        return nullptr;
    }
    else if (value_op_stat->GetOp6Stat() != nullptr)
    {
        guess_list.resize(0);
        ABnfGuessPtr guess;
        auto error = GuessType(value_factor_stat, value_op_stat->GetOp6Stat(), guess);
        if (error) return error;
        guess_list.push_back(guess);
        return nullptr;
    }
    else if (value_op_stat->GetOp7Stat() != nullptr)
    {
        guess_list.resize(0);
        ABnfGuessPtr guess;
        auto error = GuessType(value_factor_stat, value_op_stat->GetOp7Stat(), guess);
        if (error) return error;
        guess_list.push_back(guess);
        return nullptr;
    }
    else if (value_op_stat->GetOp8Stat() != nullptr)
    {
        guess_list.resize(0);
        ABnfGuessPtr guess;
        auto error = GuessType(value_factor_stat, value_op_stat->GetOp8Stat(), guess);
        if (error) return error;
        guess_list.push_back(guess);
        return nullptr;
    }
    return value_factor_stat->GuessTypes(guess_list);
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptOp2StatElement> op_2_stat, ABnfGuessPtr& guess)
{
    guess = nullptr;
    auto op_2_value = op_2_stat->GetOp2Value();
    ABnfGuessPtr suffix_guess_type;
    auto error = GuessType(op_2_value, suffix_guess_type);
    if (error) return error;

    ABnfElementPtr last_src = op_2_value;
    const auto& suffix_ex_list = op_2_stat->GetOp2SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        if (suffix_ex->GetOp3Suffix() != nullptr)
        {
            error = GuessTypeForOp3(last_src, suffix_guess_type, suffix_ex->GetOp3Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp3Suffix();
        }
        else if (suffix_ex->GetOp4Suffix() != nullptr)
        {
            error = GuessTypeForOp4(last_src, suffix_guess_type, suffix_ex->GetOp4Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp4Suffix();
        }
        else if (suffix_ex->GetOp5Suffix() != nullptr)
        {
            error = GuessTypeForOp5(last_src, suffix_guess_type, suffix_ex->GetOp5Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp5Suffix();
        }
        else if (suffix_ex->GetOp6Suffix() != nullptr)
        {
            error = GuessTypeForOp6(last_src, suffix_guess_type, suffix_ex->GetOp6Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp6Suffix();
        }
        else if (suffix_ex->GetOp7Suffix() != nullptr)
        {
            error = GuessTypeForOp7(last_src, suffix_guess_type, suffix_ex->GetOp7Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp7Suffix();
        }
        else if (suffix_ex->GetOp8Suffix() != nullptr)
        {
            error = GuessTypeForOp8(last_src, suffix_guess_type, suffix_ex->GetOp8Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp8Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ex, u8"未知的表达式");
        }
    }

    guess = suffix_guess_type;
    return nullptr;
}

// assign_or_call 填true表示赋值，否则是函数调用的参数传递

ABnfGuessError ALittleScriptOp::GuessTypeEqual(ABnfGuessPtr left_guess, ABnfElementPtr right_src, ABnfGuessPtr right_guess, bool assign_or_call, bool is_return)
{
    // 如果值等于null，那么可以赋值
    if (right_guess->GetValue() == "null") return nullptr;

    // 如果字符串直接相等，那么直接返回成功
    if (!std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(left_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess)
        && left_guess->GetValue() == right_guess->GetValue()) return nullptr;

    // const是否可以赋值给非const
    if (assign_or_call)
    {
        if (left_guess->is_const && !right_guess->is_const)
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8", 不能是:" + right_guess->GetValue());
    }
    else
    {
        // 如果不是基本变量类型（排除any），基本都是值传递，函数调用时就不用检查const
        if (!std::dynamic_pointer_cast<ALittleScriptGuessPrimitive>(left_guess) || left_guess->GetValueWithoutConst() == "any")
        {
            if (!left_guess->is_const && right_guess->is_const)
                return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8", 不能是:" + right_guess->GetValue());
        }
    }

    // 如果字符串直接相等，那么直接返回成功
    if (!std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(left_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess)
        && left_guess->GetValueWithoutConst() == right_guess->GetValueWithoutConst()) return nullptr;

    // 如果任何一方是any，那么就认为是相等
    if (std::dynamic_pointer_cast<ALittleScriptGuessAny>(left_guess) || std::dynamic_pointer_cast<ALittleScriptGuessAny>(right_guess)) return nullptr;

    // 基本变量类型检查
    if (std::dynamic_pointer_cast<ALittleScriptGuessBool>(left_guess))
        return ABnfGuessError(right_src, u8"要求是bool,不能是:" + right_guess->GetValue());

    if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(left_guess))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess))
            return ABnfGuessError(right_src, u8"long赋值给int，需要使用cast<int>()做强制类型转换");
        if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess))
            return ABnfGuessError(right_src, u8"double赋值给int，需要使用cast<int>()做强制类型转换");
        return ABnfGuessError(right_src, u8"要求是int, 不能是:" + right_guess->GetValue());
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessLong>(left_guess))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess)) return nullptr;

        if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(right_guess))
            return ABnfGuessError(right_src, u8"double赋值给long，需要使用cast<long>()做强制类型转换");
        return ABnfGuessError(right_src, u8"要求是long, 不能是:" + right_guess->GetValue());
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessDouble>(left_guess))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessInt>(right_guess) || std::dynamic_pointer_cast<ALittleScriptGuessLong>(right_guess)) return nullptr;
        return ABnfGuessError(right_src, u8"要求是double, 不能是:" + right_guess->GetValue());
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessString>(left_guess))
        return ABnfGuessError(right_src, u8"要求是string,不能是:" + right_guess->GetValue());

    if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(left_guess))
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessMap>(right_guess))
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());

        auto error = GuessTypeEqual(std::dynamic_pointer_cast<ALittleScriptGuessMap>(left_guess)->key_type.lock(), right_src, std::dynamic_pointer_cast<ALittleScriptGuessMap>(right_guess)->key_type.lock(), assign_or_call, is_return);
        if (error) return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        error = GuessTypeEqual(std::dynamic_pointer_cast<ALittleScriptGuessMap>(left_guess)->value_type.lock(), right_src, std::dynamic_pointer_cast<ALittleScriptGuessMap>(right_guess)->value_type.lock(), assign_or_call, is_return);
        if (error) return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(left_guess))
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessList>(right_guess))
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());

        auto error = GuessTypeEqual(std::dynamic_pointer_cast<ALittleScriptGuessList>(left_guess)->sub_type.lock(), right_src, std::dynamic_pointer_cast<ALittleScriptGuessList>(right_guess)->sub_type.lock(), assign_or_call, is_return);
        if (error) return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(left_guess))
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(right_guess))
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());

        auto left_guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(left_guess);
        auto right_guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(right_guess);

        if (left_guess_functor->param_list.size() != right_guess_functor->param_list.size()
            || left_guess_functor->param_nullable_list.size() != right_guess_functor->param_nullable_list.size()
            || left_guess_functor->return_list.size() != right_guess_functor->return_list.size()
            || left_guess_functor->template_param_list.size() != right_guess_functor->template_param_list.size()
            || left_guess_functor->await_modifier != right_guess_functor->await_modifier
            || left_guess_functor->proto.empty() && !right_guess_functor->proto.empty()
            || !left_guess_functor->proto.empty() && right_guess_functor->proto.empty()
            || (!left_guess_functor->proto.empty() && left_guess_functor->proto != right_guess_functor->proto)
            || left_guess_functor->param_tail.lock() == nullptr && right_guess_functor->param_tail.lock() != nullptr
            || left_guess_functor->param_tail.lock() != nullptr && right_guess_functor->param_tail.lock() == nullptr
            || left_guess_functor->return_tail.lock() == nullptr && right_guess_functor->return_tail.lock() != nullptr
            || left_guess_functor->return_tail.lock() != nullptr && right_guess_functor->return_tail.lock() == nullptr
            )
        {
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }

        for (int i = 0; i < left_guess_functor->template_param_list.size(); ++i)
        {
            auto error = GuessTypeEqual(left_guess_functor->template_param_list[i].lock(), right_src, right_guess_functor->template_param_list[i].lock(), assign_or_call, is_return);
            if (error) return error;
        }

        for (int i = 0; i < left_guess_functor->param_list.size(); ++i)
        {
            auto error = GuessTypeEqual(left_guess_functor->param_list[i].lock(), right_src, right_guess_functor->param_list[i].lock(), assign_or_call, is_return);
            if (error) return error;
        }

        for (int i = 0; i < left_guess_functor->param_nullable_list.size(); ++i)
        {
            if (left_guess_functor->param_nullable_list[i] != right_guess_functor->param_nullable_list[i])
                return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }

        for (int i = 0; i < left_guess_functor->return_list.size(); ++i)
        {
            auto error = GuessTypeEqual(left_guess_functor->return_list[i].lock(), right_src, right_guess_functor->return_list[i].lock(), assign_or_call, is_return);
            if (error) return error;
        }
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(left_guess))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
        {
            auto right_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess);
            if (right_guess_template->template_extends.lock() != nullptr)
                right_guess = right_guess_template->template_extends.lock();
        }

        if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess))
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());

        if (left_guess->GetValueWithoutConst() == right_guess->GetValueWithoutConst()) return nullptr;

        bool result = false;
        auto error = ALittleScriptUtility::IsClassSuper(std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess)->class_dec.lock(), left_guess->GetValue(), result);
        if (error) return error;
        if (result) return nullptr;

        return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(left_guess))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
        {
            auto right_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess);
            if (right_guess_template->template_extends.lock() != nullptr)
                right_guess = right_guess_template->template_extends.lock();
        }

        if (!(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(right_guess)))
        {
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }

        if (left_guess->GetValueWithoutConst() == right_guess->GetValueWithoutConst()) return nullptr;

        bool result = false;
        auto error = ALittleScriptUtility::IsStructSuper(std::dynamic_pointer_cast<ALittleScriptGuessStruct>(right_guess)->struct_dec.lock(), left_guess->GetValue(), result);
        if (error) return error;
        if (result) return nullptr;

        return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(left_guess))
    {
        auto left_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(left_guess);
        if (left_guess_template->template_extends.lock() != nullptr)
        {
            auto error = GuessTypeEqual(left_guess_template->template_extends.lock(), right_src, right_guess, assign_or_call, is_return);
            if (error) return error;
            return nullptr;
        }
        else if (left_guess_template->is_class)
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess))
            {
                return nullptr;
            }
            else if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
            {
                auto right_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess);
                if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess_template->template_extends.lock()) || right_guess_template->is_class)
                    return nullptr;
            }
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }
        else if (left_guess_template->is_struct)
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(right_guess))
            {
                return nullptr;
            }
            else if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
            {
                auto right_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess);
                if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(right_guess_template->template_extends.lock()) || right_guess_template->is_struct)
                    return nullptr;
            }
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }
        else
        {
            if (!assign_or_call && !is_return) return nullptr;

            if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
            {
                if (left_guess->GetValue() == right_guess->GetValue())
                    return nullptr;
                if (left_guess->GetValueWithoutConst() == right_guess->GetValue())
                    return nullptr;
            }
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }
    }

    return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptOp2ValueElement> op_2_value, ABnfGuessPtr& guess)
{
    guess = nullptr;

    auto value_factor_stat = op_2_value->GetValueFactorStat();
    if (value_factor_stat == nullptr)
        return ABnfGuessError(value_factor_stat, u8"单目运算没有目标表达式");

    ABnfGuessPtr guess_info;
    auto error = value_factor_stat->GuessType(guess_info);
    if (error) return error;

    const auto& op_2 = op_2_value->GetOp2()->GetElementText();
    // guess_type必须是逻辑运算符
    if (op_2 == "!")
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessBool>(guess_info))
            return ABnfGuessError(value_factor_stat, u8"!运算符右边必须是bool类型.不能是:" + guess_info->GetValue());
        // guess_type必须是数字
    }
    else if (op_2 == "-")
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(guess_info) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(guess_info) && !std::dynamic_pointer_cast<ALittleScriptGuessDouble>(guess_info))
            return ABnfGuessError(value_factor_stat, u8"-运算符右边必须是int,double类型.不能是:" + guess_info->GetValue());
    }
    else
    {
        return ABnfGuessError(op_2_value->GetOp2(), u8"未知的运算符:" + op_2);
    }

    guess = guess_info;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp4StatElement> op_4_stat, ABnfGuessPtr& guess)
{
    guess = nullptr;
    ABnfGuessPtr factor_guess_type;
    auto error = value_factor_stat->GuessType(factor_guess_type);
    if (error) return error;

    ABnfGuessPtr suffix_guess_type;
    error = GuessTypeForOp4(value_factor_stat, factor_guess_type, op_4_stat->GetOp4Suffix(), suffix_guess_type);
    if (error) return error;

    ABnfElementPtr last_src = op_4_stat->GetOp4Suffix();
    const auto& suffix_ex_list = op_4_stat->GetOp4SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        if (suffix_ex->GetOp4Suffix() != nullptr)
        {
            error = GuessTypeForOp4(last_src, suffix_guess_type, suffix_ex->GetOp4Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp4Suffix();
        }
        else if (suffix_ex->GetOp5Suffix() != nullptr)
        {
            error = GuessTypeForOp5(last_src, suffix_guess_type, suffix_ex->GetOp5Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp5Suffix();
        }
        else if (suffix_ex->GetOp6Suffix() != nullptr)
        {
            error = GuessTypeForOp6(last_src, suffix_guess_type, suffix_ex->GetOp6Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp6Suffix();
        }
        else if (suffix_ex->GetOp7Suffix() != nullptr)
        {
            error = GuessTypeForOp7(last_src, suffix_guess_type, suffix_ex->GetOp7Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp7Suffix();
        }
        else if (suffix_ex->GetOp8Suffix() != nullptr)
        {
            error = GuessTypeForOp8(last_src, suffix_guess_type, suffix_ex->GetOp8Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp8Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ex, u8"未知的表达式");
        }
    }

    guess = suffix_guess_type;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp5StatElement> op_5_stat, ABnfGuessPtr& guess)
{
    guess = nullptr;
    ABnfGuessPtr factor_guess_type;
    auto error = value_factor_stat->GuessType(factor_guess_type);
    if (error) return error;

    ABnfGuessPtr suffix_guess_type;
    error = GuessTypeForOp5(value_factor_stat, factor_guess_type, op_5_stat->GetOp5Suffix(), suffix_guess_type);
    if (error) return error;

    ABnfElementPtr last_src = op_5_stat->GetOp5Suffix();
    const auto& suffix_ex_list = op_5_stat->GetOp5SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        if (suffix_ex->GetOp5Suffix() != nullptr)
        {
            error = GuessTypeForOp5(last_src, suffix_guess_type, suffix_ex->GetOp5Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp5Suffix();
        }
        else if (suffix_ex->GetOp6Suffix() != nullptr)
        {
            error = GuessTypeForOp6(last_src, suffix_guess_type, suffix_ex->GetOp6Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp6Suffix();
        }
        else if (suffix_ex->GetOp7Suffix() != nullptr)
        {
            error = GuessTypeForOp7(last_src, suffix_guess_type, suffix_ex->GetOp7Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp7Suffix();
        }
        else if (suffix_ex->GetOp8Suffix() != nullptr)
        {
            error = GuessTypeForOp8(last_src, suffix_guess_type, suffix_ex->GetOp8Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp8Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ex, u8"未知的表达式");
        }
    }

    guess = suffix_guess_type;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp6StatElement> op_6_stat, ABnfGuessPtr& guess)
{
    guess = nullptr;
    ABnfGuessPtr factor_guess_type;
    auto error = value_factor_stat->GuessType(factor_guess_type);
    if (error) return error;

    ABnfGuessPtr suffix_guess_type;
    error = GuessTypeForOp6(value_factor_stat, factor_guess_type, op_6_stat->GetOp6Suffix(), suffix_guess_type);
    if (error) return error;

    ABnfElementPtr last_src = op_6_stat->GetOp6Suffix();
    const auto& suffix_ex_list = op_6_stat->GetOp6SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        if (suffix_ex->GetOp6Suffix() != nullptr)
        {
            error = GuessTypeForOp6(last_src, suffix_guess_type, suffix_ex->GetOp6Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp6Suffix();
        }
        else if (suffix_ex->GetOp7Suffix() != nullptr)
        {
            error = GuessTypeForOp7(last_src, suffix_guess_type, suffix_ex->GetOp7Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp7Suffix();
        }
        else if (suffix_ex->GetOp8Suffix() != nullptr)
        {
            error = GuessTypeForOp8(last_src, suffix_guess_type, suffix_ex->GetOp8Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp8Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ex, u8"未知的表达式");
        }
    }

    guess = suffix_guess_type;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp7StatElement> op_7_stat, ABnfGuessPtr& guess)
{
    guess = nullptr;
    ABnfGuessPtr factor_guess_type;
    auto error = value_factor_stat->GuessType(factor_guess_type);
    if (error) return error;

    ABnfGuessPtr suffix_guess_type;
    error = GuessTypeForOp7(value_factor_stat, factor_guess_type, op_7_stat->GetOp7Suffix(), suffix_guess_type);
    if (error) return error;

    ABnfElementPtr last_src = op_7_stat->GetOp7Suffix();
    const auto& suffix_ex_list = op_7_stat->GetOp7SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        if (suffix_ex->GetOp7Suffix() != nullptr)
        {
            error = GuessTypeForOp7(last_src, suffix_guess_type, suffix_ex->GetOp7Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp7Suffix();
        }
        else if (suffix_ex->GetOp8Suffix() != nullptr)
        {
            error = GuessTypeForOp8(last_src, suffix_guess_type, suffix_ex->GetOp8Suffix(), suffix_guess_type);
            if (error) return error;
            last_src = suffix_ex->GetOp8Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ex, u8"未知的表达式");
        }
    }

    guess = suffix_guess_type;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessType(std::shared_ptr<ALittleScriptValueFactorStatElement> value_factor_stat, std::shared_ptr<ALittleScriptOp8StatElement> op_8_stat, ABnfGuessPtr& guess)
{
    guess = nullptr;
    ABnfGuessPtr factor_guess_type;
    auto error = value_factor_stat->GuessType(factor_guess_type);
    if (error) return error;

    ABnfGuessPtr suffix_guess_type;
    error = GuessTypeForOp8(value_factor_stat, factor_guess_type, op_8_stat->GetOp8Suffix(), suffix_guess_type);
    if (error) return error;

    ABnfElementPtr last_src = op_8_stat->GetOp8Suffix();
    const auto& suffix_ex_list = op_8_stat->GetOp8SuffixExList();
    for (auto& suffix_ex : suffix_ex_list)
    {
        if (suffix_ex->GetOp8Suffix() != nullptr)
        {
            error = GuessTypeForOp8(last_src, suffix_guess_type, suffix_ex->GetOp8Suffix(), suffix_guess_type);
            if (error) return error;
            if (suffix_guess_type == nullptr) return nullptr;
            last_src = suffix_ex->GetOp8Suffix();
        }
        else
        {
            return ABnfGuessError(suffix_ex, u8"未知的表达式");
        }
    }

    guess = suffix_guess_type;
    return nullptr;
}

ABnfGuessError ALittleScriptOp::GuessTypeForOp7Impl(const std::string& op_string, ABnfElementPtr left_src, ABnfGuessPtr left_guess_type, ABnfElementPtr right_src, ABnfGuessPtr right_guess_type, std::shared_ptr<ALittleScriptOp7SuffixElement> op_7_suffix, ABnfGuessPtr& guess)
{
    guess = nullptr;
    if (!(std::dynamic_pointer_cast<ALittleScriptGuessBool>(left_guess_type)))
        return ABnfGuessError(left_src, op_string + u8"运算符左边必须是bool类型.不能是:" + left_guess_type->GetValue());

    if (!(std::dynamic_pointer_cast<ALittleScriptGuessBool>(right_guess_type)))
        return ABnfGuessError(right_src, op_string + u8"运算符右边边必须是bool类型.不能是:" + right_guess_type->GetValue());

    guess = ALittleScriptStatic::Inst().sBoolGuess;
    return nullptr;
}
