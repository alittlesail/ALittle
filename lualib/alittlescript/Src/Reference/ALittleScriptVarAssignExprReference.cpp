#include "ALittleScriptVarAssignExprReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptVarAssignDecElement.h"

#include "../Guess/ALittleScriptGuessReturnTail.h"
#include "../Index/ALittleScriptOp.h"

ABnfGuessError ALittleScriptVarAssignExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    auto value_stat = element->GetValueStat();
    if (value_stat == nullptr) return nullptr;

    const auto& pair_dec_list = element->GetVarAssignDecList();
    if (pair_dec_list.size() == 0) return nullptr;

    // �������ֵֻ��һ����������
    if (pair_dec_list.size() > 1)
    {
        // ��ȡ�ұ߱��ʽ��
        std::vector<ABnfGuessPtr> method_call_guess_list;
        auto guess_error = value_stat->GuessTypes(method_call_guess_list);
        if (guess_error) return guess_error;
        if (method_call_guess_list.size() == 0)
            return ABnfGuessError(value_stat, u8"���õĺ���û�з���ֵ");
        const bool has_tail = std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(method_call_guess_list[method_call_guess_list.size() - 1]) != nullptr;
        if (has_tail)
        {
            // ����Ҫ���
        }
        else
        {
            if (method_call_guess_list.size() < pair_dec_list.size())
                return ABnfGuessError(value_stat, u8"���õĺ�������ֵ�������ڶ���ı�������");
        }

        for (size_t i = 0; i < pair_dec_list.size(); ++i)
        {
            auto pair_dec = pair_dec_list[i];
            if (i >= method_call_guess_list.size()) break;
            if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(method_call_guess_list[i])) break;

            ABnfGuessPtr pair_dec_guess;
            guess_error = pair_dec->GuessType(pair_dec_guess);
            if (guess_error) return guess_error;
            guess_error = ALittleScriptOp::GuessTypeEqual(pair_dec_guess, value_stat, method_call_guess_list[i], true, false);
            if (guess_error)
                return ABnfGuessError(value_stat, u8"�Ⱥ���ߵĵ�" + std::to_string(i + 1) + u8"�����������ͺ�������ķ���ֵ���Ͳ����:" + guess_error.error);
        }
        return nullptr;
    }

    ABnfGuessPtr pair_guess;
    auto error = pair_dec_list[0]->GuessType(pair_guess);
    if (error) return error;
    ABnfGuessPtr value_guess;
    error = value_stat->GuessType(value_guess);
    if (error) return error;

    error = ALittleScriptOp::GuessTypeEqual(pair_guess, value_stat, value_guess, true, false);
    if (error)
        return ABnfGuessError(error.element, u8"�Ⱥ���ߵı����ͱ��ʽ�����Ͳ�ͬ:" + error.error);

    return nullptr;
}
