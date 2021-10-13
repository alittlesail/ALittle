#include "ALittleScriptReturnExprReference.h"

#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptMethodReturnTailDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptMethodReturnDecElement.h"
#include "../Generate/ALittleScriptMethodReturnOneDecElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"
#include "../Guess/ALittleScriptGuessParamTail.h"

ABnfGuessError ALittleScriptReturnExprReference::CheckError()
{
    auto my_element = m_element.lock();
    if (my_element == nullptr) return ABnfGuessError(my_element, u8"�ڵ�ʧЧ");
	
    if (m_element.lock()->GetReturnYield() != nullptr)
    {
        // ����ReturnYield�Ͳ���Ҫ������ֵ���
        // �����ں������м�飬����Ҫ��async��await��ʾ
        // ��ȡ��Ӧ�ĺ�������
        ABnfElementPtr element;
        ABnfElementPtr parent = my_element;
        while (parent != nullptr)
        {
            if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
            {
                auto method_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent);
                const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(method_dec->GetParent())->GetModifierList();
                if (ALittleScriptUtility::GetCoroutineType(modifier).empty())
                {
                    element = method_dec->GetMethodNameDec();
                    if (element == nullptr) element = method_dec;
                }
                break;
            }
            else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
            {
                auto method_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent);
                const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(method_dec->GetParent())->GetModifierList();
                if (ALittleScriptUtility::GetCoroutineType(modifier).empty())
                {
                    element = method_dec->GetMethodNameDec();
                    if (element == nullptr) element = method_dec;
                }
                break;
            }
            else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
            {
                auto method_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent);
                const auto& modifier = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(method_dec->GetParent())->GetModifierList();
                if (ALittleScriptUtility::GetCoroutineType(modifier).empty())
                {
                    element = method_dec->GetMethodNameDec();
                    if (element == nullptr) element = method_dec;
                }
                break;
            }

            parent = parent->GetParent();
        }

        if (element != nullptr)
            return ABnfGuessError(element, u8"�����ڲ�ʹ����return yield���ʽ�����Ա���ʹ��async��await����");
        return nullptr;
    }

    const auto& value_stat_list = m_element.lock()->GetValueStatList();
    std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> return_type_list;
    std::shared_ptr<ALittleScriptMethodReturnTailDecElement> return_tail_dec;

    // ��ȡ��Ӧ�ĺ�������
    ABnfElementPtr parent = my_element;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
        {
            auto getterDec = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent);
            return_type_list.resize(0);
            auto return_type_dec = getterDec->GetAllType();
            if (return_type_dec != nullptr)
                return_type_list.push_back(return_type_dec);
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
        {
            auto method_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent);
            auto return_dec = method_dec->GetMethodReturnDec();
            if (return_dec != nullptr)
            {
                const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
                for (const auto& return_one : return_one_list)
                {
                    auto all_type = return_one->GetAllType();
                    if (all_type != nullptr) return_type_list.push_back(all_type);

                    auto return_tail = return_one->GetMethodReturnTailDec();
                    if (return_tail != nullptr) return_tail_dec = return_tail;
                }
            }
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
        {
            auto method_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent);
            auto return_dec = method_dec->GetMethodReturnDec();
            if (return_dec != nullptr)
            {
                const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
                for (const auto& return_one : return_one_list)
                {
                    auto all_type = return_one->GetAllType();
                    if (all_type != nullptr) return_type_list.push_back(all_type);

                    auto return_tail = return_one->GetMethodReturnTailDec();
                    if (return_tail != nullptr) return_tail_dec = return_tail;
                }
            }
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            auto method_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent);
            auto return_dec = method_dec->GetMethodReturnDec();
            if (return_dec != nullptr)
            {
                const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
                for (const auto& return_one : return_one_list)
                {
                    auto all_type = return_one->GetAllType();
                    if (all_type != nullptr) return_type_list.push_back(all_type);

                    auto return_tail = return_one->GetMethodReturnTailDec();
                    if (return_tail != nullptr) return_tail_dec = return_tail;
                }
            }
            break;
        }

        parent = parent->GetParent();
    }

    // ����������
    std::vector<ABnfGuessPtr> guess_list;
    // �������ֵֻ��һ����������
    if (value_stat_list.size() == 1 && (return_type_list.size() > 1 || return_tail_dec != nullptr))
    {
        auto value_stat = value_stat_list[0];
        auto error = value_stat->GuessTypes(guess_list);
        if (error) return error;
        bool has_value_tail = !guess_list.empty()
	        && std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(guess_list[guess_list.size() - 1]);

        if (return_tail_dec == nullptr)
        {
            if (has_value_tail)
            {
                if (guess_list.size() < return_type_list.size() - 1)
                    return ABnfGuessError(my_element, u8"return�ĺ������õķ���ֵ����������������ķ���ֵ����");
            }
            else
            {
                if (guess_list.size() != return_type_list.size())
                    return ABnfGuessError(my_element, u8"return�ĺ������õķ���ֵ�����ͺ�������ķ���ֵ���������");
            }
        }
        else
        {
            if (has_value_tail)
            {
                // ���ü��
            }
            else
            {
                if (guess_list.size() < return_type_list.size())
                    return ABnfGuessError(my_element, u8"return�ĺ������õķ���ֵ�������ں�������ķ���ֵ����");
            }
        }
    }
    else
    {
        if (return_tail_dec == nullptr)
        {
            if (value_stat_list.size() != return_type_list.size())
                return ABnfGuessError(my_element, u8"return�ķ���ֵ�����ͺ�������ķ���ֵ���������");
        }
        else
        {
            if (value_stat_list.size() < return_type_list.size())
                return ABnfGuessError(my_element, u8"return�ķ���ֵ�������ں�������ķ���ֵ����");
        }
        guess_list.resize(0);
        for (const auto& value_stat : value_stat_list)
        {
            int return_count = 0;
            std::vector<ABnfGuessPtr> guess_temp;
            auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_temp);
            if (error) return error;
            if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

            ABnfGuessPtr guess;
            error = value_stat->GuessType(guess);
            if (error) return error;
            if (std::dynamic_pointer_cast<ALittleScriptGuessParamTail>(guess))
                return ABnfGuessError(value_stat, u8"return���ʽ���ܷ���\"...\"");
            ABnfGuessPtr value_stat_guess;
            error = value_stat->GuessType(value_stat_guess);
            if (error) return error;
            guess_list.push_back(value_stat_guess);
        }
    }

    // ÿ���������μ��
    for (size_t i = 0; i < guess_list.size(); ++i)
    {
        std::shared_ptr<ALittleScriptValueStatElement> target_value_stat;
        if (i < value_stat_list.size())
            target_value_stat = value_stat_list[i];
        else
            target_value_stat = value_stat_list[0];

        if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(guess_list[i])) break;
        if (i >= return_type_list.size()) break;
        ABnfGuessPtr return_type_guess;
        auto error = return_type_list[i]->GuessType(return_type_guess);
        if (error) return error;
        if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(return_type_guess)) break;

        error = ALittleScriptOp::GuessTypeEqual(return_type_guess, target_value_stat, guess_list[i], false, true);
        if (error)
            return ABnfGuessError(target_value_stat, u8"return�ĵ�" + std::to_string(i + 1) + u8"������ֵ�����ͺ�������ķ���ֵ���Ͳ�ͬ:" + error.error);
    }

    return nullptr;
}
