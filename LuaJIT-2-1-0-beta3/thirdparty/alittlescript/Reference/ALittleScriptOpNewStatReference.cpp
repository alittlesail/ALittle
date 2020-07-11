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
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    if (element->GetCustomType() != nullptr)
        return element->GetCustomType()->GuessTypes(guess_list);
    else if (element->GetGenericType() != nullptr)
        return element->GetGenericType()->GuessTypes(guess_list);
    guess_list.resize(0);
    return ABnfGuessError(element, u8"ALittleOpNewStat出现未知的子节点");
}

ABnfGuessError ALittleScriptOpNewStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    const auto& value_stat_list = element->GetValueStatList();

    if (element->GetGenericType() != nullptr)
    {
        if (value_stat_list.size() > 0)
            return ABnfGuessError(element, u8"创建容器实例对象不能有参数");
        if (element->GetGenericType()->GetGenericFunctorType() != nullptr)
            return ABnfGuessError(element, u8"Functor不能new");
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
                return ABnfGuessError(element, u8"new的结构体不能有参数");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
        {
            if (value_stat_list.size() > 0)
                return ABnfGuessError(element, u8"new的Map不能有参数");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
        {
            if (value_stat_list.size() > 0)
                return ABnfGuessError(element, u8"new的List不能有参数");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
        {
            auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
            if (guess_template->template_extends.lock() != nullptr)
                guess = guess_template->template_extends.lock();
            else if (guess_template->is_struct)
            {
                if (value_stat_list.size() > 0)  return ABnfGuessError(element, u8"new的结构体不能有参数");
                return nullptr;
            }
            else if (guess_template->is_class)
            {
                return ABnfGuessError(element, u8"如果要new改模板类型，请不要使用class，无法确定它的构造函数参数");
            }
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        {
            if (value_stat_list.size() > 0) return ABnfGuessError(element, u8"new的结构体不能有参数");
            return nullptr;
        }

        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        {
            auto class_dec = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess)->class_dec.lock();
            auto ctor_dec = ALittleScriptUtility::FindFirstCtorDecFromExtends(class_dec, 100);
            if (ctor_dec == nullptr)
            {
                if (value_stat_list.size() > 0)
                    return ABnfGuessError(element, u8"new的类的构造函数没有参数");
                return nullptr;
            }

            auto param_dec = ctor_dec->GetMethodParamDec();
            if (param_dec == nullptr)
            {
                if (value_stat_list.size() > 0)
                    return ABnfGuessError(element, u8"new的类的构造函数没有参数");
                return nullptr;
            }

            const auto& param_one_dec_list = param_dec->GetMethodParamOneDecList();
            std::vector<ABnfGuessPtr> param_guess_list;
            std::vector<bool> param_nullable_list;
            bool has_param_tail = false;
            for (auto& param_one_dec : param_one_dec_list)
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

            // 如果参数数量不足以填充
            if (value_stat_list.size() < param_guess_list.size())
            {
                // 不足的部分，参数必须都是nullable
                for (size_t i = value_stat_list.size(); i < param_nullable_list.size(); ++i)
                {
                    if (!param_nullable_list[i])
                    {
                        // 计算至少需要的参数个数
                        size_t count = param_nullable_list.size();
                        for (int j = static_cast<int>(param_nullable_list.size()) - 1; j >= 0; --j)
                        {
                            if (param_nullable_list[j])
                                --count;
                            else
                                break;
                        }
                        return ABnfGuessError(element, u8"new的类的构造函数调用需要" + std::to_string(count) + u8"个参数,不能是:" + std::to_string(value_stat_list.size()) + u8"个");
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
                if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

                ABnfGuessPtr value_stat_guess;
                error = value_stat->GuessType(value_stat_guess);
                if (error) return error;
                // 如果参数返回的类型是tail，那么就可以不用检查
                if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(value_stat_guess)) continue;

                if (i >= param_guess_list.size())
                {
                    // 如果有参数占位符，那么就直接跳出，不检查了
                    // 如果没有，就表示超过参数数量了
                    if (has_param_tail)
                        break;
                    else
                        return ABnfGuessError(element, u8"该构造函数调用需要" + std::to_string(param_guess_list.size()) + u8"个参数，而不是" + std::to_string(value_stat_list.size()) + u8"个");
                }

                error = ALittleScriptOp::GuessTypeEqual(param_guess_list[i], value_stat, value_stat_guess, false, false);
                if (error)
                    return ABnfGuessError(value_stat, u8"第" + std::to_string(i + 1) + u8"个参数类型和函数定义的参数类型不同:" + error.error);
            }
            return nullptr;
        }

        return ABnfGuessError(element, u8"只能new结构体和类");
    }

    return nullptr;
}
