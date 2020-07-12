#include "ALittleScriptPropertyValueMethodCallReference.h"

#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"
#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptPropertyValueFirstTypeElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptPropertyValueMethodTemplateElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"

#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"

#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"

inline ABnfGuessError ALittleScriptPropertyValueMethodCallReference::GuessPreType(ABnfGuessPtr& guess)
{
    guess = nullptr;
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    // 获取父节点
    auto property_value_suffix = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(element->GetParent());
    auto property_value = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(property_value_suffix->GetParent());
    auto property_value_first_type = property_value->GetPropertyValueFirstType();
    const auto& suffix_list = property_value->GetPropertyValueSuffixList();

    // 获取所在位置
    int index = -1;
    for (size_t i = 0; i < suffix_list.size(); ++i)
    {
        if (suffix_list[i] == property_value_suffix)
        {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1) return nullptr;

    // 获取前一个类型
    ABnfGuessPtr pre_type;
    ABnfGuessPtr pre_pre_type;
    ABnfGuessError error;
    if (index == 0)
    {
        error = property_value_first_type->GuessType(pre_type);
        if (error) return error;
    }
    else if (index == 1)
    {
        error = suffix_list[index - 1]->GuessType(pre_type);
        if (error) return error;
        error = property_value_first_type->GuessType(pre_pre_type);
        if (error) return error;
    }
    else
    {
        error = suffix_list[index - 1]->GuessType(pre_type);
        if (error) return error;
        error = suffix_list[index - 2]->GuessType(pre_pre_type);
        if (error) return error;
    }

    // 如果是Functor
    if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(pre_type))
    {
        auto pre_type_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(pre_type);
        if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(pre_pre_type))
            pre_pre_type = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(pre_pre_type)->template_extends.lock();

        // 如果再往前一个是一个Class实例对象，那么就要去掉第一个参数
        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(pre_pre_type) && pre_type_functor->param_list.size() > 0
            && (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(pre_type_functor->GetElement())
                || std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(pre_type_functor->GetElement())
                || std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(pre_type_functor->GetElement()))) {
            auto new_pre_type_functor = std::shared_ptr<ALittleScriptGuessFunctor>(new ALittleScriptGuessFunctor(pre_type_functor->GetElement()));
            pre_type = new_pre_type_functor;

            new_pre_type_functor->await_modifier = pre_type_functor->await_modifier;
            new_pre_type_functor->const_modifier = pre_type_functor->const_modifier;
            new_pre_type_functor->proto = pre_type_functor->proto;
            new_pre_type_functor->template_param_list = pre_type_functor->template_param_list;
            new_pre_type_functor->param_list = pre_type_functor->param_list;
            new_pre_type_functor->param_nullable_list = pre_type_functor->param_nullable_list;
            new_pre_type_functor->param_name_list = pre_type_functor->param_name_list;
            new_pre_type_functor->param_tail = pre_type_functor->param_tail;
            new_pre_type_functor->return_list = pre_type_functor->return_list;
            new_pre_type_functor->return_tail = pre_type_functor->return_tail;

            // 移除掉第一个参数
            new_pre_type_functor->param_list.erase(new_pre_type_functor->param_list.begin());
            new_pre_type_functor->param_nullable_list.erase(new_pre_type_functor->param_nullable_list.begin());
            new_pre_type_functor->param_name_list.erase(new_pre_type_functor->param_name_list.begin());

            new_pre_type_functor->UpdateValue();
            element->GetFile()->AddGuessType(new_pre_type_functor);
        }
    }

    guess = pre_type;
    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueMethodCallReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);

    std::unordered_map<std::string, std::shared_ptr<ALittleScriptGuessTemplate>> src_map;
    std::unordered_map<std::string, ABnfGuessPtr> fill_map;
    std::shared_ptr<ALittleScriptGuessFunctor> pre_type_functor;
    auto error = CheckTemplateMap(src_map, fill_map, pre_type_functor);
    if (error) return error;
    if (pre_type_functor == nullptr) return nullptr;

    for (auto& guess : pre_type_functor->return_list)
    {
        auto guess_e = guess.lock();
        if (guess_e == nullptr) return nullptr;

        if (guess_e->NeedReplace())
        {
            auto replace = guess_e->ReplaceTemplate(element->GetFile(), fill_map);
            if (replace == nullptr) return ABnfGuessError(element, u8"模板替换失败:" + guess_e->GetValue());
            guess_list.push_back(replace);
        }
        else
            guess_list.push_back(guess_e);
    }

    auto return_tail_e = pre_type_functor->return_tail.lock();
    if (return_tail_e != nullptr)
        guess_list.push_back(return_tail_e);

    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueMethodCallReference::AnalysisTemplate(std::unordered_map<std::string, ABnfGuessPtr>& fill_map, ABnfGuessPtr left_guess, ABnfElementPtr right_src, ABnfGuessPtr right_guess, bool assign_or_call)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    // 如果值等于null，那么可以赋值
    if (right_guess->GetValue() == "null") return nullptr;

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

    // 如果任何一方是any，那么就认为可以相等
    if (std::dynamic_pointer_cast<ALittleScriptGuessAny>(left_guess)) return nullptr;

    if (std::dynamic_pointer_cast<ALittleScriptGuessPrimitive>(left_guess)
        || std::dynamic_pointer_cast<ALittleScriptGuessStruct>(left_guess))
    {
        return ALittleScriptOp::GuessTypeEqual(left_guess, right_src, right_guess, assign_or_call, false);
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(left_guess))
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessMap>(right_guess))
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());


        auto error = AnalysisTemplate(fill_map, std::dynamic_pointer_cast<ALittleScriptGuessMap>(left_guess)->key_type.lock(), right_src, std::dynamic_pointer_cast<ALittleScriptGuessMap>(right_guess)->key_type.lock(), false);
        if (error) return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        error = AnalysisTemplate(fill_map, std::dynamic_pointer_cast<ALittleScriptGuessMap>(left_guess)->value_type.lock(), right_src, std::dynamic_pointer_cast<ALittleScriptGuessMap>(right_guess)->value_type.lock(), false);
        if (error) return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(left_guess))
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessList>(right_guess))
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        auto error = AnalysisTemplate(fill_map, std::dynamic_pointer_cast<ALittleScriptGuessList>(left_guess)->sub_type.lock(), right_src, std::dynamic_pointer_cast<ALittleScriptGuessList>(right_guess)->sub_type.lock(), false);
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
            auto error = AnalysisTemplate(fill_map, left_guess_functor->template_param_list[i].lock(), right_src, right_guess_functor->template_param_list[i].lock(), false);
            if (error) return error;
        }

        for (int i = 0; i < left_guess_functor->param_list.size(); ++i)
        {
            auto error = AnalysisTemplate(fill_map, left_guess_functor->param_list[i].lock(), right_src, right_guess_functor->param_list[i].lock(), false);
            if (error) return error;
        }

        for (int i = 0; i < left_guess_functor->param_nullable_list.size(); ++i)
        {
            if (left_guess_functor->param_nullable_list[i] != right_guess_functor->param_nullable_list[i])
                return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }

        for (int i = 0; i < left_guess_functor->return_list.size(); ++i)
        {
            auto error = AnalysisTemplate(fill_map, left_guess_functor->return_list[i].lock(), right_src, right_guess_functor->return_list[i].lock(), false);
            if (error) return error;
        }
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(left_guess))
    {
        if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
            right_guess = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess)->template_extends.lock();

        if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess))
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());

        if (left_guess->GetValue() == right_guess->GetValue()) return nullptr;

        bool result = false;
        auto error = ALittleScriptUtility::IsClassSuper(std::dynamic_pointer_cast<ALittleScriptGuessClass>(left_guess)->class_dec.lock(), right_guess->GetValue(), result);
        if (error) return error;
        if (result) return nullptr;
        error = ALittleScriptUtility::IsClassSuper(std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess)->class_dec.lock(), left_guess->GetValue(), result);
        if (error) return error;
        if (result) return nullptr;

        return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(left_guess)) {
        auto left_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(left_guess);

        // 查看模板是否已经被填充，那么就按填充的检查
        auto it = fill_map.find(left_guess_template->GetValue());
        if (it != fill_map.end())
            return ALittleScriptOp::GuessTypeEqual(it->second, right_src, right_guess, false, false);

        // 处理还未填充
        if (left_guess_template->template_extends.lock() != nullptr)
        {
            auto error = AnalysisTemplate(fill_map, left_guess_template->template_extends.lock(), right_src, right_guess, false);
            if (error) return error;
            if (right_guess->is_const)
            {
                right_guess = right_guess->Clone();
                right_guess->is_const = false;
                right_guess->UpdateValue();
                element->GetFile()->AddGuessType(right_guess);
            }
            fill_map[left_guess_template->GetValueWithoutConst()] = right_guess;
            return nullptr;
        }
        else if (left_guess_template->is_class)
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess))
            {
                if (right_guess->is_const)
                {
                    right_guess = right_guess->Clone();
                    right_guess->is_const = false;
                    right_guess->UpdateValue();
                    element->GetFile()->AddGuessType(right_guess);
                }
                fill_map[left_guess_template->GetValueWithoutConst()] = right_guess;
                return nullptr;
            }
            else if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
            {
                auto right_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess);
                if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(right_guess_template->template_extends.lock()) || right_guess_template->is_class)
                {
                    if (right_guess->is_const)
                    {
                        right_guess = right_guess->Clone();
                        right_guess->is_const = false;
                        right_guess->UpdateValue();
                        element->GetFile()->AddGuessType(right_guess);
                    }
                    fill_map[right_guess_template->GetValueWithoutConst()] = right_guess;
                    return nullptr;
                }
            }
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }
        else if (left_guess_template->is_struct)
        {
            if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(right_guess))
            {
                if (right_guess->is_const)
                {
                    right_guess = right_guess->Clone();
                    right_guess->is_const = false;
                    right_guess->UpdateValue();
                    element->GetFile()->AddGuessType(right_guess);
                }
                fill_map[left_guess_template->GetValueWithoutConst()] = right_guess;
                return nullptr;
            }
            else if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess))
            {
                auto right_guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(right_guess);
                if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(right_guess_template->template_extends.lock()) || right_guess_template->is_struct)
                {
                    if (right_guess->is_const)
                    {
                        right_guess = right_guess->Clone();
                        right_guess->is_const = false;
                        right_guess->UpdateValue();
                        element->GetFile()->AddGuessType(right_guess);
                    }
                    fill_map[left_guess_template->GetValue()] = right_guess;
                    return nullptr;
                }
            }
            return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
        }

        if (right_guess->is_const)
        {
            right_guess = right_guess->Clone();
            right_guess->is_const = false;
            right_guess->UpdateValue();
            element->GetFile()->AddGuessType(right_guess);
        }
        fill_map[left_guess_template->GetValueWithoutConst()] = right_guess;
        return nullptr;
    }

    return ABnfGuessError(right_src, u8"要求是" + left_guess->GetValue() + u8",不能是:" + right_guess->GetValue());
}

ABnfGuessError ALittleScriptPropertyValueMethodCallReference::CheckTemplateMap(std::unordered_map<std::string, std::shared_ptr<ALittleScriptGuessTemplate>>& src_map, std::unordered_map<std::string, ABnfGuessPtr>& fill_map, std::shared_ptr<ALittleScriptGuessFunctor>& guess)
{
    guess = nullptr;

    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    ABnfGuessPtr pre_type;
    auto error = GuessPreType(pre_type);
    if (error) return error;
    if (pre_type == nullptr) return nullptr;

    // 如果需要处理
    if (!std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(pre_type)) return nullptr;
    auto pre_type_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(pre_type);

    const auto& value_stat_list = element->GetValueStatList();
    if (pre_type_functor->param_list.size() < value_stat_list.size() && pre_type_functor->param_tail.lock() == nullptr)
        return ABnfGuessError(element, u8"函数调用最多需要" + std::to_string(pre_type_functor->param_list.size()) + u8"个参数,不能是:" + std::to_string(value_stat_list.size()) + u8"个");

    // 检查模板参数
    if (pre_type_functor->template_param_list.size() > 0)
    {
        for (auto& template_param : pre_type_functor->template_param_list)
        {
            auto template_param_e = template_param.lock();
            if (template_param_e) src_map[template_param_e->GetValue()] = template_param_e;
        }

        auto method_template = element->GetPropertyValueMethodTemplate();
        if (method_template != nullptr)
        {
            const auto& all_type_list = method_template->GetAllTypeList();
            if (all_type_list.size() > pre_type_functor->template_param_list.size())
                return ABnfGuessError(element, u8"函数调用最多需要" + std::to_string(pre_type_functor->template_param_list.size()) + u8"个模板参数,不能是:" + std::to_string(all_type_list.size()) + u8"个");

            for (int i = 0; i < all_type_list.size(); ++i)
            {
                ABnfGuessPtr all_type_guess;
                error = all_type_list[i]->GuessType(all_type_guess);
                if (error) return error;
                auto template_param_e = pre_type_functor->template_param_list[i].lock();
                if (template_param_e == nullptr) continue;
                error = ALittleScriptOp::GuessTypeEqual(template_param_e, all_type_list[i], all_type_guess, false, false);
                if (error) return error;
                auto key = template_param_e->GetValueWithoutConst();
                if (all_type_guess->is_const)
                {
                    all_type_guess = all_type_guess->Clone();
                    all_type_guess->is_const = false;
                    all_type_guess->UpdateValue();
                    element->GetFile()->AddGuessType(all_type_guess);
                }
                fill_map[key] = all_type_guess;
            }
        }

        // 根据填充的参数来分析以及判断
        for (int i = 0; i < value_stat_list.size(); ++i)
        {
            auto value_stat = value_stat_list[i];
            ABnfGuessPtr value_stat_guess;
            error = value_stat->GuessType(value_stat_guess);
            if (error) return error;
            // 如果参数返回的类型是tail，那么就可以不用检查
            if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(value_stat_guess)) continue;
            if (i >= pre_type_functor->param_list.size()) break;

            // 逐个分析，并且填充模板
            error = AnalysisTemplate(fill_map, pre_type_functor->param_list[i].lock(), value_stat, value_stat_guess, false);
            if (error) return error;
        }

        // 判断如果还未有模板解析，就报错
        for (auto& pair : src_map)
        {
            if (fill_map.find(pair.first) == fill_map.end())
                return ABnfGuessError(element, pair.first + u8"模板无法解析");
        }
    }

    guess = pre_type_functor;
    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueMethodCallReference::GenerateTemplateParamList(std::vector<ABnfGuessPtr>& param_list)
{
    param_list.resize(0);

    std::unordered_map<std::string, std::shared_ptr<ALittleScriptGuessTemplate>> src_map;
    std::unordered_map<std::string, ABnfGuessPtr> fill_map;
    std::shared_ptr<ALittleScriptGuessFunctor> pre_type_functor;
    auto error = CheckTemplateMap(src_map, fill_map, pre_type_functor);
    if (error) return error;
    if (pre_type_functor == nullptr) return nullptr;

    for (int i = 0; i < pre_type_functor->template_param_list.size(); ++i)
    {
        auto guess_template = pre_type_functor->template_param_list[i].lock();
        if (guess_template == nullptr) continue;
        if (guess_template->template_extends.lock() != nullptr || guess_template->is_class || guess_template->is_struct)
        {
            auto it = fill_map.find(guess_template->GetValue());
            if (it != fill_map.end()) param_list.push_back(it->second);
        }
    }

    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueMethodCallReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    std::unordered_map<std::string, std::shared_ptr<ALittleScriptGuessTemplate>> src_map;
    std::unordered_map<std::string, ABnfGuessPtr> fill_map;
    std::shared_ptr<ALittleScriptGuessFunctor> pre_type_functor;
    auto error = CheckTemplateMap(src_map, fill_map, pre_type_functor);
    if (error) return error;
    if (pre_type_functor == nullptr) return ABnfGuessError(element, u8"括号前面必须是函数");

    // 检查填写的和函数定义的参数是否一致
    const auto& value_stat_list = element->GetValueStatList();
    for (int i = 0; i < value_stat_list.size(); ++i)
    {
        auto value_stat = value_stat_list[i];

        int return_count = 0;
        std::vector<ABnfGuessPtr> guess_list;
        error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

        ABnfGuessPtr guess;
        error = value_stat->GuessType(guess);
        if (error) return error;
        // 如果参数返回的类型是tail，那么就可以不用检查
        if (std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(guess)) continue;

        if (i >= pre_type_functor->param_list.size())
        {
            // 如果有参数占位符，那么就直接跳出，不检查了
            // 如果没有，就表示超过参数数量了
            if (pre_type_functor->param_tail.lock() != nullptr)
                break;
            else
                return ABnfGuessError(element, u8"该函数调用需要" + std::to_string(pre_type_functor->param_list.size()) + u8"个参数，而不是" + std::to_string(value_stat_list.size()) + u8"个");
        }

        error = ALittleScriptOp::GuessTypeEqual(pre_type_functor->param_list[i].lock(), value_stat, guess, false, false);
        if (error)
            return ABnfGuessError(value_stat, u8"第" + std::to_string(i + 1) + u8"个参数类型和函数定义的参数类型不同:" + error.error);
    }

    // 如果参数数量不足以填充
    if (value_stat_list.size() < pre_type_functor->param_list.size())
    {
        // 不足的部分，参数必须都是nullable
        for (size_t i = value_stat_list.size(); i < pre_type_functor->param_nullable_list.size(); ++i)
        {
            if (!pre_type_functor->param_nullable_list[i])
            {
                // 计算至少需要的参数个数
                size_t count = pre_type_functor->param_nullable_list.size();
                for (int j = static_cast<int>(pre_type_functor->param_nullable_list.size()) - 1; j >= 0; --j)
                {
                    if (pre_type_functor->param_nullable_list[j])
                        --count;
                    else
                        break;
                }
                return ABnfGuessError(element, u8"该函数调用至少需要" + std::to_string(count) + u8"个参数，而不是" + std::to_string(value_stat_list.size()) + u8"个");
            }
        }
    }

    // 检查这个函数是不是await
    if (pre_type_functor->await_modifier)
    {
        // 检查这次所在的函数必须要有await或者async修饰
        error = ALittleScriptUtility::CheckInvokeAwait(element);
        if (error) return error;
    }
    return nullptr;
}
