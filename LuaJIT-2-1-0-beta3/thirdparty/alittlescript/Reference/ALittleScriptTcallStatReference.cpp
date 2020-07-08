#include "ALittleScriptTcallStatReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"
#include "../Guess/ALittleScriptGuessFunctor.h"

ABnfGuessError ALittleScriptTcallStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    guess_list.resize(0);
    auto value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"tcall表达式不能没有参数");

    // 第一个参数必须是函数
    auto value_stat = value_stat_list[0];
    ABnfGuessPtr guess;
    auto error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
        return ABnfGuessError(value_stat, u8"tcall表达式第一个参数必须是一个函数");

    auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
    if (guess_functor->template_param_list.size() > 0)
        return ABnfGuessError(value_stat, u8"tcall表达式要绑定的函数不能有模板定义");

    guess_list.resize(0);
    guess_list.push_back(ALittleScriptStatic::Inst().sStringGuess);
    for (auto& return_guess : guess_functor->return_list)
        guess_list.push_back(return_guess.lock());
    if (guess_functor->return_tail.lock() != nullptr)
        guess_list.push_back(guess_functor->return_tail.lock());

    return nullptr;
}

ABnfGuessError ALittleScriptTcallStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"tcall表达式不能没有参数");

    // 第一个参数必须是函数
    auto value_stat = value_stat_list[0];

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

    ABnfGuessPtr guess;
    error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
        return ABnfGuessError(value_stat, u8"tcall表达式第一个参数必须是一个函数");

    auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
    if (guess_functor->template_param_list.size() > 0)
        return ABnfGuessError(value_stat, u8"tcall表达式要绑定的函数不能有模板定义");

    // 后面跟的参数数量不能超过这个函数的参数个数
    if (value_stat_list.size() - 1 > guess_functor->param_list.size())
    {
        if (guess_functor->param_tail.lock() == nullptr)
            return ABnfGuessError(element, u8"tcall表达式参数太多了");
    }

    // 遍历所有的表达式，看下是否符合
    for (int i = 1; i < value_stat_list.size(); ++i)
    {
        if (i - 1 >= guess_functor->param_list.size()) break;
        auto param_guess = guess_functor->param_list[i - 1];
        auto param_value_stat = value_stat_list[i];

        guess_list.resize(0);
        error = ALittleScriptUtility::CalcReturnCount(param_value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(param_value_stat, u8"表达式必须只能是一个返回值");

        ABnfGuessPtr param_value_stat_guess;
        error = param_value_stat->GuessType(param_value_stat_guess);
        if (error) return error;
        error = ALittleScriptOp::GuessTypeEqual(param_guess.lock(), param_value_stat, param_value_stat_guess, false, false);
        if (error)
            return ABnfGuessError(param_value_stat, u8"第" + std::to_string(i) + u8"个参数类型和函数定义的参数类型不同:" + error.error);
    }

    // 检查这个函数是不是await
    if (guess_functor->await_modifier)
    {
        // 检查这次所在的函数必须要有await或者async修饰
        error = ALittleScriptUtility::CheckInvokeAwait(element);
        if (error) return error;
    }
    return nullptr;
}
