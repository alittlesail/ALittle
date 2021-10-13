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
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto& property_value_list = element->GetPropertyValueList();
    auto value_stat = element->GetValueStat();
    if (value_stat == nullptr)
    {
        if (property_value_list.size() != 1)
            return ABnfGuessError(element, u8"û�и�ֵ���ʽʱ��ֻ����һ����������");
        auto property_value = property_value_list[0];
        const auto& suffix_list = property_value->GetPropertyValueSuffixList();
        if (suffix_list.size() == 0)
            return ABnfGuessError(element, u8"û�и�ֵ���ʽʱ��ֻ����һ����������");
        auto suffix = suffix_list[suffix_list.size() - 1];
        if (suffix->GetPropertyValueMethodCall() == nullptr)
            return ABnfGuessError(element, u8"û�и�ֵ���ʽʱ��ֻ����һ����������");
        return nullptr;
    }

    if (property_value_list.empty()) return nullptr;

    // �������ֵֻ��һ����������
    if (property_value_list.size() > 1)
    {
        if (value_stat == nullptr)
            return ABnfGuessError(element, u8"���õĺ���û�з���ֵ");
        // ��ȡ�ұ߱��ʽ��
        std::vector<ABnfGuessPtr> method_call_guess_list;
        auto guess_error = value_stat->GuessTypes(method_call_guess_list);
        if (guess_error) return guess_error;
        if (method_call_guess_list.size() == 0)
            return ABnfGuessError(value_stat, u8"���õĺ���û�з���ֵ");

        const bool hasTail = std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(method_call_guess_list[method_call_guess_list.size() - 1]) != nullptr;
        if (hasTail)
        {
            // �������
        }
        else
        {
            if (method_call_guess_list.size() < property_value_list.size())
                return ABnfGuessError(value_stat, u8"���õĺ�������ֵ�������ڶ���ı�������");
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
                return ABnfGuessError(value_stat, u8"�Ⱥ���ߵĵ�" + std::to_string(i + 1) + u8"�����������ͺ�������ķ���ֵ���Ͳ����:" + guess_error.error);
        }

        return nullptr;
    }

    auto op_assign = element->GetOpAssign();
    if (op_assign == nullptr)
        return ABnfGuessError(element, u8"û�и�ֵ����");
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
            return ABnfGuessError(value_stat, u8"�Ⱥ���ߵı����ͱ��ʽ�����Ͳ�ͬ");
    }

    if (op_string == "=")
    {
        error = ALittleScriptOp::GuessTypeEqual(pair_guess, value_stat, value_guess, true, false);
        if (error)
            return ABnfGuessError(error.element, u8"�Ⱥ���ߵı����ͱ��ʽ�����Ͳ�ͬ:" + error.error);
    }
    else
    {
        int return_count = 0;
        std::vector<ABnfGuessPtr> guess_list;
        error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;

        if (return_count != 1)
            return ABnfGuessError(value_stat, op_string + u8"�ұ߱���ֻ����һ������ֵ");

        if (pair_guess->is_const)
            return ABnfGuessError(property_value_list[0], u8"const���Ͳ���ʹ��" + op_string + u8"�����");

        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(pair_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessDouble>(pair_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(pair_guess))
            return ABnfGuessError(property_value_list[0], op_string + u8"��߱�����int, double, long");

        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(value_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessDouble>(value_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(value_guess))
            return ABnfGuessError(value_stat, op_string + u8"�ұ߱�����int, double, long");
    }
    return nullptr;
}
