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

#include "../Index/ALittleScriptUtility.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"
#include "../Guess/ALittleScriptGuessParamTail.h"

ABnfGuessError ALittleScriptReturnExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    ABnfElementPtr parent;
    if (element->GetReturnYield() != nullptr)
    {
        // 对于ReturnYield就不需要做返回值检查
        // 对所在函数进行检查，必须要有async和await表示
        // 获取对应的函数对象
        ABnfElementPtr element;

        parent = element;
        while (parent != nullptr)
        {
            if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
            {
                auto method_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent);
                auto modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(method_dec->GetParent())->GetModifierList();
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
                auto modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(method_dec->GetParent())->GetModifierList();
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
                auto modifier = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(method_dec->GetParent())->GetModifierList();
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
            return ABnfGuessError(element, u8"函数内部使用了return yield表达式，所以必须使用async或await修饰");
        return nullptr;
    }

    auto value_stat_list = element->GetValueStatList();
    std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> return_type_list;
    std::shared_ptr<ALittleScriptMethodReturnTailDecElement> return_tail_dec;

    // 获取对应的函数对象
    parent = element;
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
                for (auto& return_one : return_one_list)
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
                auto return_one_list = return_dec->GetMethodReturnOneDecList();
                for (auto& return_one : return_one_list)
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
                auto return_one_list = return_dec->GetMethodReturnOneDecList();
                for (auto& return_one : return_one_list)
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

    // 参数的类型
    std::vector<ABnfGuessPtr> guess_list;
    // 如果返回值只有一个函数调用
    if (value_stat_list.size() == 1 && (return_type_list.size() > 1 || return_tail_dec != nullptr))
    {
        auto value_stat = value_stat_list[0];
        auto error = value_stat->GuessTypes(guess_list);
        if (error) return error;
        bool has_value_tail = guess_list.size() > 0
            && std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(guess_list[guess_list.size() - 1]);

        if (return_tail_dec == nullptr)
        {
            if (has_value_tail)
            {
                if (guess_list.size() < return_type_list.size() - 1)
                    return ABnfGuessError(element, u8"return的函数调用的返回值数量超过函数定义的返回值数量");
            }
            else
            {
                if (guess_list.size() != return_type_list.size())
                    return ABnfGuessError(element, u8"return的函数调用的返回值数量和函数定义的返回值数量不相等");
            }
        }
        else
        {
            if (has_value_tail)
            {
                // 不用检查
            }
            else
            {
                if (guess_list.size() < return_type_list.size())
                    return ABnfGuessError(element, u8"return的函数调用的返回值数量少于函数定义的返回值数量");
            }
        }
    }
    else
    {
        if (return_tail_dec == nullptr)
        {
            if (value_stat_list.size() != return_type_list.size())
                return ABnfGuessError(element, u8"return的返回值数量和函数定义的返回值数量不相等");
        }
        else
        {
            if (value_stat_list.size() < return_type_list.size())
                return ABnfGuessError(element, u8"return的返回值数量少于函数定义的返回值数量");
        }
        guess_list.resize(0);
        for (auto& value_stat : value_stat_list)
        {
            int return_count = 0;
            std::vector<ABnfGuessPtr> guess_list;
            auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
            if (error) return error;
            if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

            ABnfGuessPtr guess;
            error = value_stat->GuessType(guess);
            if (error) return error;
            if (std::dynamic_pointer_cast<ALittleScriptGuessParamTail>(guess))
                return ABnfGuessError(value_stat, u8"return表达式不能返回\"...\"");
            ABnfGuessPtr value_stat_guess;
            error = value_stat->GuessType(value_stat_guess);
            if (error) return error;
            guess_list.push_back(value_stat_guess);
        }
    }

    // 每个类型依次检查
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
            return ABnfGuessError(target_value_stat, u8"return的第" + std::to_string(i + 1) + "个返回值数量和函数定义的返回值类型不同:" + error.error);
    }

    return nullptr;
}
