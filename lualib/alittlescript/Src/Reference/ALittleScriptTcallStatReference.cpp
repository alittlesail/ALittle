#include "ALittleScriptTcallStatReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"
#include "../Guess/ALittleScriptGuessFunctor.h"

ABnfGuessError ALittleScriptTcallStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    guess_list.resize(0);
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"tcall���ʽ����û�в���");

    // ��һ�����������Ǻ���
    auto value_stat = value_stat_list[0];
    ABnfGuessPtr guess;
    auto error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
        return ABnfGuessError(value_stat, u8"tcall���ʽ��һ������������һ������");

    auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
    if (guess_functor->template_param_list.size() > 0)
        return ABnfGuessError(value_stat, u8"tcall���ʽҪ�󶨵ĺ���������ģ�嶨��");

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
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"tcall���ʽ����û�в���");

    // ��һ�����������Ǻ���
    auto value_stat = value_stat_list[0];

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

    ABnfGuessPtr guess;
    error = value_stat->GuessType(guess);
    if (error) return error;
    if (!std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
        return ABnfGuessError(value_stat, u8"tcall���ʽ��һ������������һ������");

    auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
    if (guess_functor->template_param_list.size() > 0)
        return ABnfGuessError(value_stat, u8"tcall���ʽҪ�󶨵ĺ���������ģ�嶨��");

    // ������Ĳ����������ܳ�����������Ĳ�������
    if (value_stat_list.size() - 1 > guess_functor->param_list.size())
    {
        if (guess_functor->param_tail.lock() == nullptr)
            return ABnfGuessError(element, u8"tcall���ʽ����̫����");
    }

    // �������еı��ʽ�������Ƿ����
    for (size_t i = 1; i < value_stat_list.size(); ++i)
    {
        if (i - 1 >= guess_functor->param_list.size()) break;
        auto param_guess = guess_functor->param_list[i - 1];
        auto param_value_stat = value_stat_list[i];

        guess_list.resize(0);
        error = ALittleScriptUtility::CalcReturnCount(param_value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(param_value_stat, u8"���ʽ����ֻ����һ������ֵ");

        ABnfGuessPtr param_value_stat_guess;
        error = param_value_stat->GuessType(param_value_stat_guess);
        if (error) return error;
        error = ALittleScriptOp::GuessTypeEqual(param_guess.lock(), param_value_stat, param_value_stat_guess, false, false);
        if (error)
            return ABnfGuessError(param_value_stat, u8"��" + std::to_string(i) + u8"���������ͺͺ�������Ĳ������Ͳ�ͬ:" + error.error);
    }

    // �����������ǲ���await
    if (guess_functor->await_modifier)
    {
        // ���������ڵĺ�������Ҫ��await����async����
        error = ALittleScriptUtility::CheckInvokeAwait(element);
        if (error) return error;
    }
    return nullptr;
}
