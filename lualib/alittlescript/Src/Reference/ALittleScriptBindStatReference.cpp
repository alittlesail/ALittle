#include "ALittleScriptBindStatReference.h"

#include "alanguage/Src/Index/ABnfFile.h"
#include "alanguage/Src/Model/ABnfGuess.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"

ABnfGuessError ALittleScriptBindStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    guess_list.resize(0);

    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"bind表达式不能没有参数");

    auto value_stat = value_stat_list[0];
    ABnfGuessPtr guess;
    auto error = value_stat->GuessType(guess);
    if (error) return error;

    const auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
    if (guess_functor == nullptr)
        return ABnfGuessError(element, u8"bind表达式第一个参数必须是一个函数");

    if (guess_functor->template_param_list.size() > 0)
        return ABnfGuessError(element, u8"bind表达式要绑定的函数不能有模板定义");

    // 开始构建类型
    auto info = std::make_shared<ALittleScriptGuessFunctor>(element);
    info->await_modifier = guess_functor->await_modifier;
    info->const_modifier = guess_functor->const_modifier;
    info->proto = guess_functor->proto;
    info->template_param_list = guess_functor->template_param_list;
    info->param_list = guess_functor->param_list;
    info->param_nullable_list = guess_functor->param_nullable_list;
    info->param_name_list = guess_functor->param_name_list;
    info->param_tail = guess_functor->param_tail;
    info->return_list = guess_functor->return_list;
    info->return_tail = guess_functor->return_tail;
    // 移除已填写的参数
    int param_count = static_cast<int>(value_stat_list.size()) - 1;
    while (param_count > 0
        && !info->param_list.empty()
        && !info->param_nullable_list.empty()
        && !info->param_name_list.empty())
    {
        info->param_list.erase(info->param_list.begin());
        info->param_nullable_list.erase(info->param_nullable_list.begin());
        info->param_name_list.erase(info->param_name_list.begin());
        --param_count;
    }
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}

ABnfGuessError ALittleScriptBindStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"bind表达式不能没有参数");

    auto value_stat = value_stat_list[0];
    ABnfGuessPtr guess;
    auto error = value_stat->GuessType(guess);
    if (error) return error;

    auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
    if (guess_functor == nullptr)
        return ABnfGuessError(element, u8"bind表达式第一个参数必须是一个函数");

    if (guess_functor->template_param_list.size() > 0)
        return ABnfGuessError(element, u8"bind表达式要绑定的函数不能有模板定义");

    // 后面跟的参数数量不能超过这个函数的参数个数
    if (value_stat_list.size() - 1 > guess_functor->param_list.size())
    {
        if (guess_functor->param_tail.lock() == nullptr)
            return ABnfGuessError(element, u8"bind表达式参数太多了");
    }

    // 遍历所有的表达式，看下是否符合
    for (size_t i = 1; i < value_stat_list.size(); ++i)
    {
        if (i - 1 >= guess_functor->param_list.size()) break;

        auto param_guess = guess_functor->param_list[i - 1];
        value_stat = value_stat_list[i];

        int return_count = 0;
        std::vector<ABnfGuessPtr> guess_list;
        error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

        ABnfGuessPtr value_stat_guess;
        error = value_stat->GuessType(value_stat_guess);
        if (error) return error;
        error = ALittleScriptOp::GuessTypeEqual(param_guess.lock(), value_stat, value_stat_guess, false, false);
        if (error)
            return ABnfGuessError(value_stat, u8"第" + std::to_string(i) + u8"个参数类型和函数定义的参数类型不同:" + error.error);
    }

    return nullptr;
}
