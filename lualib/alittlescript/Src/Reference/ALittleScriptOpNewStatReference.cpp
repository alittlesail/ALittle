#include "ALittleScriptOpNewStatReference.h"

#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptGenericTypeElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"

#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"

ABnfGuessError ALittleScriptOpNewStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    if (element->GetCustomType() != nullptr)
        return element->GetCustomType()->GuessTypes(guess_list);
    else if (element->GetGenericType() != nullptr)
        return element->GetGenericType()->GuessTypes(guess_list);
    guess_list.resize(0);
    return ABnfGuessError(element, u8"ALittleOpNewStat����δ֪���ӽڵ�");
}

ABnfGuessError ALittleScriptOpNewStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto& value_stat_list = element->GetValueStatList();

    if (element->GetGenericType() != nullptr)
    {
        if (value_stat_list.size() > 0)
            return ABnfGuessError(element, u8"��������ʵ���������в���");
        if (element->GetGenericType()->GetGenericFunctorType() != nullptr)
            return ABnfGuessError(element, u8"Functor����new");
        return nullptr;
    }

    if (element->GetCustomType() != nullptr)
    {
        auto custom_type = element->GetCustomType();
        ABnfGuessPtr guess;
        auto error = custom_type->GuessType(guess);
        if (error) return error;
        if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        {
            if (value_stat_list.size() > 0)
                return ABnfGuessError(element, u8"new�Ľṹ�岻���в���");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
        {
            if (value_stat_list.size() > 0)
                return ABnfGuessError(element, u8"new��Map�����в���");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
        {
            if (value_stat_list.size() > 0)
                return ABnfGuessError(element, u8"new��List�����в���");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
        {
            const auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
            if (guess_template->template_extends.lock() != nullptr)
                guess = guess_template->template_extends.lock();
            else if (guess_template->is_struct)
            {
                if (value_stat_list.size() > 0)  return ABnfGuessError(element, u8"new�Ľṹ�岻���в���");
                return nullptr;
            }
            else if (guess_template->is_class)
            {
                return ABnfGuessError(element, u8"���Ҫnew��ģ�����ͣ��벻Ҫʹ��class���޷�ȷ�����Ĺ��캯������");
            }
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        {
            if (value_stat_list.size() > 0) return ABnfGuessError(element, u8"new�Ľṹ�岻���в���");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        {
            const auto class_dec = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess)->class_dec.lock();
            auto ctor_dec = ALittleScriptUtility::FindFirstCtorDecFromExtends(class_dec, 100);
            if (ctor_dec == nullptr)
            {
                if (value_stat_list.size() > 0)
                    return ABnfGuessError(element, u8"new����Ĺ��캯��û�в���");
                return nullptr;
            }

            auto param_dec = ctor_dec->GetMethodParamDec();
            if (param_dec == nullptr)
            {
                if (value_stat_list.size() > 0)
                    return ABnfGuessError(element, u8"new����Ĺ��캯��û�в���");
                return nullptr;
            }

            const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
            std::vector<ABnfGuessPtr> param_guess_list;
            std::vector<bool> param_nullable_list;
            bool has_param_tail = false;
            for (const auto& param_one_dec : param_one_dec_list)
            {
                auto all_type = param_one_dec->GetAllType();
                auto param_tail = param_one_dec->GetMethodParamTailDec();
                if (all_type != nullptr)
                {
                    ABnfGuessPtr all_type_guess;
                    error = all_type->GuessType(all_type_guess);
                    if (error) return error;
                    param_guess_list.push_back(all_type_guess);
                    param_nullable_list.push_back(ALittleScriptUtility::IsNullable(param_one_dec->GetModifierList()));
                }
                else if (param_tail != nullptr)
                {
                    has_param_tail = true;
                }
            }

            // ��������������������
            if (value_stat_list.size() < param_guess_list.size())
            {
                // ����Ĳ��֣��������붼��nullable
                for (size_t i = value_stat_list.size(); i < param_nullable_list.size(); ++i)
                {
                    if (!param_nullable_list[i])
                    {
                        // ����������Ҫ�Ĳ�������
                        size_t count = param_nullable_list.size();
                        for (int j = static_cast<int>(param_nullable_list.size()) - 1; j >= 0; --j)
                        {
                            if (param_nullable_list[j])
                                --count;
                            else
                                break;
                        }
                        return ABnfGuessError(element, u8"new����Ĺ��캯��������Ҫ" + std::to_string(count) + u8"������,������:" + std::to_string(value_stat_list.size()) + u8"��");
                    }
                }
            }

            for (size_t i = 0; i < value_stat_list.size(); ++i)
            {
                auto value_stat = value_stat_list[i];

                int return_count = 0;
                std::vector<ABnfGuessPtr> guess_list;
                error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
                if (error) return error;
                if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

                ABnfGuessPtr value_stat_guess;
                error = value_stat->GuessType(value_stat_guess);
                if (error) return error;
                // ����������ص�������tail����ô�Ϳ��Բ��ü��
                if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(value_stat_guess)) continue;

                if (i >= param_guess_list.size())
                {
                    // ����в���ռλ������ô��ֱ���������������
                    // ���û�У��ͱ�ʾ��������������
                    if (has_param_tail)
                        break;
                    else
                        return ABnfGuessError(element, u8"�ù��캯��������Ҫ" + std::to_string(param_guess_list.size()) + u8"��������������" + std::to_string(value_stat_list.size()) + u8"��");
                }

                error = ALittleScriptOp::GuessTypeEqual(param_guess_list[i], value_stat, value_stat_guess, false, false);
                if (error)
                    return ABnfGuessError(value_stat, u8"��" + std::to_string(i + 1) + u8"���������ͺͺ�������Ĳ������Ͳ�ͬ:" + error.error);
            }
            return nullptr;
        }

        return ABnfGuessError(element, u8"ֻ��new�ṹ�����");
    }

    return nullptr;
}
