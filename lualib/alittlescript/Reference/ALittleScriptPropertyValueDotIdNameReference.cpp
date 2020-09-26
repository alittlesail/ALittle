#include "ALittleScriptPropertyValueDotIdNameReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptFileClass.h"

#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptPropertyValueDotIdElement.h"
#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"
#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptPropertyValueFirstTypeElement.h"
#include "../Generate/ALittleScriptOpAssignExprElement.h"
#include "../Generate/ALittleScriptStructVarDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptPropertyValueMethodCallElement.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptClassVarDecElement.h"
#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptEnumDecElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"

#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessNamespaceName.h"
#include "../Guess/ALittleScriptGuessClassName.h"
#include "../Guess/ALittleScriptGuessEnumName.h"
#include "../Guess/ALittleScriptGuessEnum.h"
#include "../Guess/ALittleScriptGuessStructName.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ALittleScriptPropertyValueDotIdNameReference::ALittleScriptPropertyValueDotIdNameReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueDotIdNameElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
    m_key = element->GetElementText();
}

void ALittleScriptPropertyValueDotIdNameReference::ReloadInfo()
{
    m_method_dec = ABnfElementPtr();
    ABnfElementPtr parent = m_element.lock();
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent)->GetMethodBodyDec();
            break;

        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)->GetMethodBodyDec();
            break;
        }

        parent = parent->GetParent();
    }
}

ABnfGuessError ALittleScriptPropertyValueDotIdNameReference::ReplaceTemplate(ABnfGuessPtr guess, ABnfGuessPtr& result)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    result = nullptr;
    auto class_guess = m_class_guess.lock();
    if (class_guess == nullptr)
    {
        result = guess;
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess) && class_guess->template_map.size() > 0)
    {
        auto it = class_guess->template_map.find(guess->GetValueWithoutConst());
        if (it != class_guess->template_map.end() && it->second.lock())
        {
            auto guess_template = it->second.lock();
            if (guess->is_const && !guess_template->is_const)
            {
                guess_template = guess_template->Clone();
                guess_template->is_const = true;
                guess_template->UpdateValue();
                element->GetFile()->AddGuessType(guess_template);

            }
            result = guess_template;
        }
        else
            result = guess;
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
        auto info = std::shared_ptr<ALittleScriptGuessFunctor>(new ALittleScriptGuessFunctor(guess_functor->GetElement()));
        info->await_modifier = guess_functor->await_modifier;
        info->const_modifier = guess_functor->const_modifier;
        info->proto = guess_functor->proto;
        info->template_param_list = guess_functor->template_param_list;
        info->param_tail = guess_functor->param_tail;
        info->param_name_list = guess_functor->param_name_list;
        info->return_tail = guess_functor->return_tail;

        auto guess_functor_element = guess_functor->GetElement();
        int start_index = 0;
        if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(guess_functor_element))
        {
            info->param_list.push_back(class_guess);
            info->param_nullable_list.push_back(false);
            if (info->param_name_list.size() > 0)
                info->param_name_list[0] = class_guess->GetValue();
            start_index = 1;
        }
        for (int i = start_index; i < guess_functor->param_list.size(); ++i)
        {
            ABnfGuessPtr guess_info;
            auto error = ReplaceTemplate(guess_functor->param_list[i].lock(), guess_info);
            if (error) return error;
            info->param_list.push_back(guess_info);
        }
        for (int i = start_index; i < guess_functor->param_nullable_list.size(); ++i)
        {
            info->param_nullable_list.push_back(guess_functor->param_nullable_list[i]);
        }
        for (int i = 0; i < guess_functor->return_list.size(); ++i)
        {
            ABnfGuessPtr guess_info;
            auto error = ReplaceTemplate(guess_functor->return_list[i].lock(), guess_info);
            if (error) return error;
            info->return_list.push_back(guess_info);
        }
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        result = info;
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(guess))
    {
        auto guess_list = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess);
        ABnfGuessPtr sub_info;
        auto error = ReplaceTemplate(guess_list->sub_type.lock(), sub_info);
        if (error) return error;
        auto info = ABnfGuessPtr(new ALittleScriptGuessList(sub_info, guess_list->is_const, guess_list->is_native));
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        result = info;
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
    {
        auto guess_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess);
        ABnfGuessPtr key_info;
        auto error = ReplaceTemplate(guess_map->key_type.lock(), key_info);
        if (error) return error;
        ABnfGuessPtr value_info;
        error = ReplaceTemplate(guess_map->value_type.lock(), value_info);
        if (error) return error;

        auto info = ABnfGuessPtr(new ALittleScriptGuessMap(key_info, value_info, guess->is_const));
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        result = info;
        return nullptr;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
    {
        auto guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess);
        auto info = std::shared_ptr<ALittleScriptGuessClass>(new ALittleScriptGuessClass(guess_class->namespace_name,
            guess_class->class_name, guess_class->class_dec.lock(), guess_class->using_name, guess_class->is_const, guess_class->is_native));
        info->template_list = guess_class->template_list;
        for (auto& pair : guess_class->template_map)
        {
            info->template_map.erase(pair.first);
            ABnfGuessPtr replace_guess;
            auto error = ReplaceTemplate(pair.second.lock(), replace_guess);
            if (error) return error;
            info->template_map[pair.first] = replace_guess;
        }

        auto src_class_dec = guess_class->class_dec.lock();
        if (src_class_dec == nullptr || src_class_dec->GetClassNameDec() != nullptr)
        {
            auto src_class_name_dec = src_class_dec->GetClassNameDec();
            if (src_class_name_dec == nullptr)
                return ABnfGuessError(element, u8"类模板没有定义类名");
        }
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        result = info;
        return nullptr;
    }

    result = guess;
    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueDotIdNameReference::CalcResolve(std::vector<ABnfElementPtr>& result_list, ABnfGuessPtr& pre_type)
{
    pre_type = nullptr;
    result_list.resize(0);
    if (m_key.size() == 0) return nullptr;
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto* index_e = GetIndex();
    if (index_e == nullptr) return ABnfGuessError(element, u8"不在工程中");

    // 获取父节点
    auto property_value_dot_id = std::dynamic_pointer_cast<ALittleScriptPropertyValueDotIdElement>(element->GetParent());
    auto property_value_suffix = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(property_value_dot_id->GetParent());
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

    ABnfGuessError error;
    if (index == 0)
        error = property_value_first_type->GuessType(pre_type);
    else
        error = suffix_list[index - 1]->GuessType(pre_type);
    if (error) return error;

    // 判断当前后缀是否是最后一个后缀
    std::shared_ptr<ALittleScriptPropertyValueSuffixElement> next_suffix;
    if (index + 1 < suffix_list.size())
        next_suffix = suffix_list[index + 1];

    bool is_const = false;
    if (pre_type != nullptr) is_const = pre_type->is_const;

    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(pre_type))
    {
        pre_type = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(pre_type)->template_extends.lock();
        if (pre_type != nullptr && is_const && !pre_type->is_const)
        {
            pre_type = pre_type->Clone();
            pre_type->is_const = true;
            pre_type->UpdateValue();
            element->GetFile()->AddGuessType(pre_type);
        }
    }

    if (pre_type == nullptr) return nullptr;

    // 处理类的实例对象
    if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(pre_type))
    {
        auto class_guess = std::dynamic_pointer_cast<ALittleScriptGuessClass>(pre_type);
        m_class_guess = class_guess;
        auto class_dec = class_guess->class_dec.lock();

        // 计算当前元素对这个类的访问权限
        int access_level = ALittleScriptUtility::CalcAccessLevelByTargetClassDecForElement(element, class_dec);

        // 所有成员变量
        std::vector<ABnfElementPtr> class_var_dec_list;
        ALittleScriptUtility::FindClassAttrList(class_dec,
            access_level, ClassAttrType::VAR, m_key, class_var_dec_list, 100);
        for (auto& class_var_dec : class_var_dec_list)
            result_list.push_back(class_var_dec);

        std::vector<ABnfElementPtr> class_method_name_dec_list;
        // 在当前情况下，只有当前property_value在等号的左边，并且是最后一个属性才是setter，否则都是getter
        if (next_suffix == nullptr && std::dynamic_pointer_cast<ALittleScriptOpAssignExprElement>(property_value->GetParent())) {
            std::vector<ABnfElementPtr> setter_list;
            ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::SETTER, m_key, setter_list, 100);
            class_method_name_dec_list = setter_list;
            m_setter_list.resize(0);
            for (auto& setter : setter_list) m_setter_list.push_back(setter);
        }
        else
        {
            std::vector<ABnfElementPtr> getter_list;
            ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::GETTER, m_key, getter_list, 100);
            class_method_name_dec_list = getter_list;
            m_getter_list.resize(0);
            for (auto& getter : getter_list) m_getter_list.push_back(getter);
        }
        // 所有成员函数
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::FUN, m_key, class_method_name_dec_list, 100);
        // 添加函数名元素
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
            result_list.push_back(class_method_name_dec);
        // 处理结构体的实例对象
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type))
    {
        auto struct_dec = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(pre_type)->struct_dec.lock();
        std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>> struct_var_dec_list;
        // 所有成员变量
        ALittleScriptUtility::FindStructVarDecList(struct_dec, m_key, struct_var_dec_list, 100);
        for (auto& struct_var_dec : struct_var_dec_list)
            result_list.push_back(struct_var_dec);
        // 比如 ALittleName.XXX
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(pre_type))
    {
        auto namespace_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(pre_type)->namespace_name_dec.lock();
        const auto& namespace_name = namespace_name_dec->GetElementText();
        // 所有枚举名
        std::vector<ABnfElementPtr> enum_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), namespace_name, m_key, true, enum_name_dec_list);
        for (auto& enum_name_dec : enum_name_dec_list)
            result_list.push_back(enum_name_dec);
        // 所有全局函数
        std::vector<ABnfElementPtr> method_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), namespace_name, m_key, true, method_name_dec_list);
        for (auto& method_name_dec : method_name_dec_list)
            result_list.push_back(method_name_dec);
        // 所有类名
        std::vector<ABnfElementPtr> class_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), namespace_name, m_key, true, class_name_dec_list);
        for (auto& class_name_dec : class_name_dec_list)
            result_list.push_back(class_name_dec);
        // 所有结构体名
        std::vector<ABnfElementPtr> struct_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), namespace_name, m_key, true, struct_name_dec_list);
        for (auto& struct_name_dec : struct_name_dec_list)
            result_list.push_back(struct_name_dec);
        // 所有单例
        std::vector<ABnfElementPtr> instance_name_dec_list;
        index_e->FindALittleNameDecList(
            ABnfElementType::INSTANCE_NAME, element->GetFile(), namespace_name, m_key, false, instance_name_dec_list);
        for (auto& instance_name_dec : instance_name_dec_list)
            result_list.push_back(instance_name_dec);
        // 比如 AClassName.XXX
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_type))
    {
        auto class_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessClassName>(pre_type)->class_name_dec.lock();
        auto class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(class_name_dec->GetParent());

        // 计算当前元素对这个类的访问权限
        int access_level = ALittleScriptUtility::CalcAccessLevelByTargetClassDecForElement(element, class_dec);

        // 所有静态函数
        std::vector<ABnfElementPtr> class_method_name_dec_list;
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::STATIC, m_key, class_method_name_dec_list, 100);

        // 如果后面那个是MethodCall，并且有两个参数的是setter，是一个参数的是getter，否则两个都不是
        if (next_suffix != nullptr)
        {
            auto method_call_stat = next_suffix->GetPropertyValueMethodCall();
            if (method_call_stat != nullptr)
            {
                int paramCount = static_cast<int>(method_call_stat->GetValueStatList().size());
                if (paramCount == 1)
                {
                    // 所有getter
                    ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::GETTER, m_key, class_method_name_dec_list, 100);
                }
                else if (paramCount == 2)
                {
                    // 所有setter
                    ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::SETTER, m_key, class_method_name_dec_list, 100);
                }
            }
        }

        // 所有成员函数
        ALittleScriptUtility::FindClassAttrList(class_dec, access_level, ClassAttrType::FUN, m_key, class_method_name_dec_list, 100);
        ALittleScriptUtility::FilterSameName(class_method_name_dec_list, class_method_name_dec_list);
        for (auto& class_method_name_dec : class_method_name_dec_list)
            result_list.push_back(class_method_name_dec);
        // 比如 AEnumName.XXX
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(pre_type)) {
        // 所有枚举字段
        auto enum_name_dec = std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(pre_type)->enum_name_dec.lock();
        auto enum_dec = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(enum_name_dec->GetParent());
        std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>> var_dec_list;
        ALittleScriptUtility::FindEnumVarDecList(enum_dec, m_key, var_dec_list);
        for (auto& var_name_dec : var_dec_list)
            result_list.push_back(var_name_dec);
    }

    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueDotIdNameReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    
    guess_list.resize(0);

    m_getter_list.resize(0);
    m_setter_list.resize(0);
    m_class_guess = std::shared_ptr<ALittleScriptGuessClass>();
    
    std::vector<ABnfElementPtr> result_list;
    ABnfGuessPtr pre_type;
    auto error = CalcResolve(result_list, pre_type);
    if (error) return error;
    for (auto& result : result_list)
    {
        ABnfGuessPtr guess;
        if (std::dynamic_pointer_cast<ALittleScriptClassVarDecElement>(result))
        {
            error = result->GuessType(guess);
            if (error) return error;

            std::shared_ptr<ALittleScriptGuessClass> class_guess = m_class_guess.lock();
            if (class_guess != nullptr && std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
            {
                ABnfGuessPtr guess_template;
                auto it = class_guess->template_map.find(guess->GetValueWithoutConst());
                if (it != class_guess->template_map.end())
                    guess_template = it->second.lock();
                else
                {
                    for (int i = 0; i < class_guess->template_list.size(); ++i)
                    {
                        guess_template = class_guess->template_list[i].lock();

                        if (guess_template->GetValueWithoutConst() == guess->GetValueWithoutConst())
                            break;
                    }
                }

                if (guess_template != nullptr)
                {
                    if (guess->is_const && !guess_template->is_const)
                    {
                        guess_template = guess_template->Clone();
                        guess_template->is_const = true;
                        guess_template->UpdateValue();
                        element->GetFile()->AddGuessType(guess_template);
                    }

                    guess = guess_template;
                }
            }
        }
        else if (std::dynamic_pointer_cast<ALittleScriptStructVarDecElement>(result))
        {
            error = result->GuessType(guess);
            if (error) return error;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptEnumVarDecElement>(result))
        {
            error = result->GuessType(guess);
            if (error) return error;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(result))
        {
            error = result->GuessType(guess);
            if (error) return error;

            // 如果前一个数据是const，那么调用的函数也必须是const
            if (pre_type != nullptr && pre_type->is_const)
            {
                auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
                if (guess_functor != nullptr && !guess_functor->const_modifier)
                    return ABnfGuessError(element, u8"请使用带Const修饰的函数");
            }

            if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(result->GetParent()))
            {
                bool find = false;
                for (auto& getter : m_getter_list)
                {
                    if (getter.lock() == result)
                    {
                        find = true;
                        break;
                    }
                }
                if (find && std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
                    guess = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess)->return_list[0].lock();
            }
            else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(result->GetParent()))
            {
                bool find = false;
                for (auto& setter : m_setter_list)
                {
                    if (setter.lock() == result)
                    {
                        find = true;
                        break;
                    }
                }
                if (find && std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
                {
                    guess = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess)->param_list[1].lock();
                }
            }
            error = ReplaceTemplate(guess, guess);
            if (error) return error;

        }
        else if (std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(result)) {
            error = result->GuessType(guess);
            if (error) return error;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(result)) {
            ABnfGuessPtr enum_guess;
            error = result->GuessType(enum_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess))
                return ABnfGuessError(element, u8"ALittleEnumNameDec.guessType的结果不是ALittleGuessEnum");
            auto enum_guess_enum = std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess);
            auto info = ABnfGuessPtr(new ALittleScriptGuessEnumName(enum_guess_enum->namespace_name, enum_guess_enum->enum_name, std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(result)));
            info->UpdateValue();
            element->GetFile()->AddGuessType(info);
            guess = info;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(result)) {
            ABnfGuessPtr struct_guess;
            error = result->GuessType(struct_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess))
                return ABnfGuessError(element, u8"ALittleStructNameDec.guessType的结果不是ALittleGuessStruct");
            auto struct_guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess);
            auto info = ABnfGuessPtr(new ALittleScriptGuessStructName(struct_guess_struct->namespace_name, struct_guess_struct->struct_name, std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(result)));
            info->UpdateValue();
            element->GetFile()->AddGuessType(info);
            guess = info;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(result)) {
            ABnfGuessPtr class_guess;
            error = result->GuessType(class_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess))
                return ABnfGuessError(element, u8"ALittleClassNameDec.guessType的结果不是ALittleGuessClass");
            auto class_guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess);
            if (class_guess_class->template_list.size() > 0)
                return ABnfGuessError(element, u8"模板类" + class_guess_class->GetValue() + u8"不能直接使用");
            auto info = ABnfGuessPtr(new ALittleScriptGuessClassName(class_guess_class->namespace_name, class_guess_class->class_name, std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(result)));
            info->UpdateValue();
            element->GetFile()->AddGuessType(info);
            guess = info;
        }

        if (guess != nullptr)
        {
            if (pre_type != nullptr && pre_type->is_const && !guess->is_const)
            {
                if (std::dynamic_pointer_cast<ALittleScriptGuessPrimitive>(guess))
                {
                    auto it = ALittleScriptStatic::Inst().sPrimitiveGuessMap.find("const " + guess->GetValue());
                    if (it != ALittleScriptStatic::Inst().sPrimitiveGuessMap.end()) guess = it->second;
                    else return ABnfGuessError(element, u8"找不到const " + guess->GetValue());
                }
                else
                {
                    guess = guess->Clone();
                    guess->is_const = true;
                    guess->UpdateValue();
                    element->GetFile()->AddGuessType(guess);
                }
            }
            guess_list.push_back(guess);
        }
    }

    m_getter_list.resize(0);
    m_setter_list.resize(0);
    m_class_guess = std::shared_ptr<ALittleScriptGuessClass>();

    return nullptr;
}

int ALittleScriptPropertyValueDotIdNameReference::QueryClassificationTag(bool& blur)
{
    auto element = m_element.lock();
    if (element == nullptr) return 0;

    blur = false;
    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return 0;

    if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
        auto guess_functor_element = guess_functor->GetElement();
        if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(guess_functor_element))
            return ALittleScriptColorType::METHOD_NAME;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(guess)
        || std::dynamic_pointer_cast<ALittleScriptGuessClassName>(guess)
        || std::dynamic_pointer_cast<ALittleScriptGuessStructName>(guess)
        || std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(guess))
    {
        return ALittleScriptColorType::CUSTOM_NAME;
    }

    return ALittleScriptColorType::VAR_NAME;
}

ABnfGuessError ALittleScriptPropertyValueDotIdNameReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"重复定义");
    return nullptr;
}

bool ALittleScriptPropertyValueDotIdNameReference::QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    auto parent = element->GetParent();
    if (parent == nullptr) return false;

    return parent->GetReference()->QueryCompletion(select, list);
}

ABnfElementPtr ALittleScriptPropertyValueDotIdNameReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    std::vector<ABnfElementPtr> result_list;
    ABnfGuessPtr pre_type;
    auto error = CalcResolve(result_list, pre_type);
    if (error) return nullptr;
    for (auto& result : result_list)
        return result;
    return nullptr;
}

bool ALittleScriptPropertyValueDotIdNameReference::PeekHighlightWord()
{
    return true;
}

void ALittleScriptPropertyValueDotIdNameReference::QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    auto method_dec = m_method_dec.lock();
    if (method_dec == nullptr)
        ReloadInfo();

    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return;
    CollectHighlight(guess, method_dec, list);
}

void ALittleScriptPropertyValueDotIdNameReference::CollectHighlight(ABnfGuessPtr target_guess, ABnfElementPtr element, std::vector<ALanguageHighlightWordInfo>& list)
{
    if (std::dynamic_pointer_cast<ALittleScriptPropertyValueDotIdNameElement>(element))
    {
        if (element->GetElementText() != m_key) return;

        ABnfGuessPtr guess;
        auto error = element->GuessType(guess);
        if (error) return;
        if (guess->GetValue() == target_guess->GetValue())
        {
            ALanguageHighlightWordInfo info;
            info.line_start = element->GetStartLine();
            info.char_start = element->GetStartCol();
            info.line_end = element->GetEndLine();
            info.char_end = element->GetEndCol();
            list.push_back(info);
        }
        return;
    }

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node)
    {
        const auto& childs = node->GetChilds();
        for (auto& child : childs)
            CollectHighlight(target_guess, child, list);
    }
}
