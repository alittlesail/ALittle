#include "ALittleScriptPropertyValueCustomTypeReference.h"

#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptStructNameDecElement.h"
#include "../Generate/ALittleScriptVarAssignDecElement.h"
#include "../Generate/ALittleScriptVarAssignExprElement.h"
#include "../Generate/ALittleScriptInstanceDecElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptUsingNameDecElement.h"
#include "../Generate/ALittleScriptUsingDecElement.h"
#include "../Generate/ALittleScriptMethodParamNameDecElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"
#include "../Generate/ALittleScriptMethodBodyDecElement.h"
#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessNamespaceName.h"
#include "../Guess/ALittleScriptGuessClassName.h"
#include "../Guess/ALittleScriptGuessStructName.h"
#include "../Guess/ALittleScriptGuessEnumName.h"
#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessEnum.h"

ALittleScriptPropertyValueCustomTypeReference::ALittleScriptPropertyValueCustomTypeReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueCustomTypeElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
    m_key = element->GetElementText();
    ReloadInfo();
}

int ALittleScriptPropertyValueCustomTypeReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    auto element = m_element.lock();
    if (element == nullptr) return 0;

    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return 0;
    if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
        auto guess_element = guess_functor->GetElement();
        if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(guess_element)
            || std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(guess_element)
            || std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(guess_element)
            || std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(guess_element)
            || std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(guess_element))
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

void ALittleScriptPropertyValueCustomTypeReference::ReloadInfo()
{
    m_method_dec = ABnfElementPtr();
    ABnfElementPtr parent = m_element.lock();
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent)) {
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
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)) {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)->GetMethodBodyDec();
            break;
        }

        parent = parent->GetParent();
    }
}

ABnfGuessError ALittleScriptPropertyValueCustomTypeReference::CalcNamespaceName(std::string& namespace_name)
{
    namespace_name = "";
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    std::vector<ABnfElementPtr> result_list;
    CalcResolve(result_list);
    for (auto& result : result_list)
    {
        if (std::dynamic_pointer_cast<ALittleScriptNamespaceNameDecElement>(result))
        {
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(result))
        {
            ABnfGuessPtr class_guess;
            auto error = result->GuessType(class_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess))
                return ABnfGuessError(element, u8"ALittleClassNameDec->GuessType()的结果不是ALittleScriptGuessClass");

            auto class_guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess);
            namespace_name = class_guess_class->namespace_name;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(result))
        {
            ABnfGuessPtr struct_guess;
            auto error = result->GuessType(struct_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess))
                return ABnfGuessError(element, u8"ALittleStructNameDec->GuessType()的结果不是ALittleScriptGuessStruct");
            auto struct_guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess);
            namespace_name = struct_guess_struct->namespace_name;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(result))
        {
            ABnfGuessPtr enum_guess;
            auto error = result->GuessType(enum_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess))
                return ABnfGuessError(element, u8"ALittleEnumNameDec->GuessType()的结果不是ALittleScriptGuessEnum");
            auto enum_guess_enum = std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess);
            namespace_name = enum_guess_enum->namespace_name;
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptMethodParamNameDecElement>(result))
        {
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(result))
        {
            auto assign_dec = std::dynamic_pointer_cast<ALittleScriptVarAssignDecElement>(result->GetParent());
            if (assign_dec == nullptr) return nullptr;
            auto expr_dec = std::dynamic_pointer_cast<ALittleScriptVarAssignExprElement>(assign_dec->GetParent());
            if (expr_dec == nullptr)
                return ABnfGuessError(element, u8"ALittleScriptVarAssignDecElement的父节点不是ALittleScriptVarAssignExprElement");

            // 如果父节点是instance
            auto instance_dec = std::dynamic_pointer_cast<ALittleScriptInstanceDecElement>(expr_dec->GetParent());
            if (instance_dec == nullptr) return nullptr;

            auto element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(instance_dec->GetParent());
            if (element_dec == nullptr)
                return ABnfGuessError(element, u8"ALittleScriptInstanceDecElement的父节点不是ALittleScriptNamespaceElementDecElement");
            auto access_type = ALittleScriptUtility::CalcAccessType(element_dec->GetModifierList());
            if (access_type == ClassAccessType::PROTECTED)
                namespace_name = ALittleScriptUtility::GetNamespaceName(result);
            return nullptr;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(result))
        {
            ABnfGuessPtr method_guess;
            auto error = result->GuessType(method_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(method_guess))
                return ABnfGuessError(element, u8"ALittleScriptMethodNameDecElement->GuessType()的结果不是ALittleScriptGuessFunctor");
            auto method_guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(method_guess);
            auto method_guess_functor_element = method_guess_functor->GetElement();
            if (method_guess_functor_element != nullptr && std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(method_guess_functor_element))
            {
                auto element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(method_guess_functor_element->GetParent());
                if (element_dec == nullptr)
                    return ABnfGuessError(element, u8"ALittleScriptGlobalMethodDecElement的父节点不是ALittleScriptNamespaceElementDecElement");
                auto access_type = ALittleScriptUtility::CalcAccessType(element_dec->GetModifierList());
                if (access_type != ClassAccessType::PRIVATE)
                    namespace_name = ALittleScriptUtility::GetNamespaceName(method_guess_functor_element);
            }
            return nullptr;

        }
        else if (std::dynamic_pointer_cast<ALittleScriptUsingNameDecElement>(result))
        {
            auto using_dec = std::dynamic_pointer_cast<ALittleScriptUsingDecElement>(result->GetParent());
            if (using_dec == nullptr)
                return ABnfGuessError(element, u8"ALittleScriptUsingNameDecElement的父节点不是ALittleScriptUsingDecElement");
            auto element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(using_dec->GetParent());
            if (element_dec == nullptr)
                return ABnfGuessError(element, u8"ALittleScriptUsingDecElement的父节点不是ALittleScriptNamespaceElementDecElement");
            auto access_type = ALittleScriptUtility::CalcAccessType(element_dec->GetModifierList());
            if (access_type != ClassAccessType::PRIVATE)
                namespace_name = ALittleScriptUtility::GetNamespaceName(result);
            return nullptr;
        }
    }

    return nullptr;
}

void ALittleScriptPropertyValueCustomTypeReference::CalcResolve(std::vector<ABnfElementPtr>& result_list)
{
    if (m_key.size() == 0) return;

    auto element = m_element.lock();
    if (element == nullptr) return;
    auto* index = GetIndex();
    if (index == nullptr) return;

    // 处理命名域
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_map;
        index->FindNamespaceNameDecList(m_key, dec_map);
        if (dec_map.size() > 0) result_list.clear();
        for (auto& pair : dec_map)
            result_list.push_back(pair.second);
    }
    // 处理全局函数
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        if (dec_list.size() > 0) result_list.clear();
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
    // 处理类名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        if (dec_list.size() > 0) result_list.clear();
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
    // 处理结构体名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        if (dec_list.size() > 0) result_list.clear();
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
    // 处理using
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
    // 处理枚举名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        if (dec_list.size() > 0) result_list.clear();
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
    // 处理单例
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::INSTANCE_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
        if (dec_list.size() > 0) result_list.clear();
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
    // 处理参数
    auto method_dec = m_method_dec.lock();
    if (method_dec != nullptr)
    {
        std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>> dec_list;
        ALittleScriptUtility::FindMethodParamNameDecList(method_dec, m_key, dec_list);
        if (dec_list.size() > 0) result_list.clear();
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
    // 处理表达式定义
    {
        std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>> dec_list;
        ALittleScriptUtility::FindVarAssignNameDecList(element, m_key, dec_list);
        if (dec_list.size() > 0) result_list.clear();
        for (auto& dec : dec_list)
            result_list.push_back(dec);
    }
}

ABnfGuessError ALittleScriptPropertyValueCustomTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);
    // 标记是否已经包含了命名域，命名域的guess不要重复
    bool has_namespace = false;

    std::vector<ABnfElementPtr> result_list;
    CalcResolve(result_list);
    for (auto& result : result_list)
    {
        ABnfGuessPtr guess;
        if (std::dynamic_pointer_cast<ALittleScriptNamespaceNameDecElement>(result))
        {
            if (!has_namespace)
            {
                ABnfGuessPtr result_guess;
                auto error = result->GuessType(result_guess);
                if (error) return error;
                has_namespace = true;
                auto guess_namespace_name = ABnfGuessPtr(new ALittleScriptGuessNamespaceName(
                    result_guess->GetValue(),
                    std::dynamic_pointer_cast<ALittleScriptNamespaceNameDecElement>(result)
                ));
                guess_namespace_name->UpdateValue();
                element->GetFile()->AddGuessType(guess_namespace_name);
                guess = guess_namespace_name;
            }
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(result))
        {
            ABnfGuessPtr class_guess;
            auto error = result->GuessType(class_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess))
                return ABnfGuessError(element, u8"ALittleClassNameDec->GuessType()的结果不是ALittleScriptGuessClass");

            auto class_guess_class = std::dynamic_pointer_cast<ALittleScriptGuessClass>(class_guess);
            if (class_guess_class->template_list.size() > 0)
                return ABnfGuessError(element, u8"模板类" + class_guess_class->GetValue() + u8"不能直接使用");

            auto guess_class_name = ABnfGuessPtr(new ALittleScriptGuessClassName(class_guess_class->namespace_name,
                class_guess_class->class_name, std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(result)));
            guess_class_name->UpdateValue();
            element->GetFile()->AddGuessType(guess_class_name);
            guess = guess_class_name;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(result))
        {
            ABnfGuessPtr struct_guess;
            auto error = result->GuessType(struct_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess))
                return ABnfGuessError(element, u8"ALittleStructNameDec->GuessType()的结果不是ALittleScriptGuessStruct");
            auto struct_guess_struct = std::dynamic_pointer_cast<ALittleScriptGuessStruct>(struct_guess);

            auto guess_struct_name = ABnfGuessPtr(new ALittleScriptGuessStructName(struct_guess_struct->namespace_name,
                struct_guess_struct->struct_name, std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(result)));
            guess_struct_name->UpdateValue();
            element->GetFile()->AddGuessType(guess_struct_name);
            guess = guess_struct_name;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(result))
        {
            ABnfGuessPtr enum_guess;
            auto error = result->GuessType(enum_guess);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess))
                return ABnfGuessError(element, u8"ALittleEnumNameDec->GuessType()的结果不是ALittleScriptGuessEnum");
            auto enum_guess_enum = std::dynamic_pointer_cast<ALittleScriptGuessEnum>(enum_guess);

            auto guess_enum_name = ABnfGuessPtr(new ALittleScriptGuessEnumName(enum_guess_enum->namespace_name,
                enum_guess_enum->enum_name, std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(result)));
            guess_enum_name->UpdateValue();
            element->GetFile()->AddGuessType(guess_enum_name);
            guess = guess_enum_name;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptMethodParamNameDecElement>(result))
        {
            auto error = result->GuessType(guess);
            if (error) return error;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(result))
        {
            auto error = result->GuessType(guess);
            if (error) return error;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(result))
        {
            auto error = result->GuessType(guess);
            if (error) return error;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptUsingNameDecElement>(result))
        {
            auto error = result->GuessType(guess);
            if (error) return error;
        }

        if (guess != nullptr) guess_list.push_back(guess);
    }

    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueCustomTypeReference::CheckError()
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

bool ALittleScriptPropertyValueCustomTypeReference::QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    auto* index = GetIndex();
    if (index == nullptr) return false;

    // 处理命名域
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_map;
        index->FindNamespaceNameDecList("", dec_map);
        for (auto& pair : dec_map)
            list.emplace_back(pair.second->GetElementText(), ALittleScriptIconType::NAMESPACE, pair.second->GetDescriptor());
    }
    // 处理全局函数
    {
        std::vector<std::shared_ptr<ABnfElement>> dec_list;
        index->FindALittleNameDecList(ABnfElementType::GLOBAL_METHOD, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::GLOBAL_METHOD, dec->GetDescriptor());
    }
    // 处理类名
    {
        std::vector<std::shared_ptr<ABnfElement>> dec_list;
        index->FindALittleNameDecList(ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
    }
    // 处理结构体名
    {
        std::vector<std::shared_ptr<ABnfElement>> dec_list;
        index->FindALittleNameDecList(ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
    }
    // 处理using
    {
        std::vector<std::shared_ptr<ABnfElement>> dec_list;
        index->FindALittleNameDecList(ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error)
                list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
            else
            {
                if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
                    list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
                else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
                    list.emplace_back(dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
                else
                    list.emplace_back(dec->GetElementText(), ALittleScriptIconType::PROPERTY, dec->GetDescriptor());
            }
        }
    }
    // 处理枚举名
    {
        std::vector<std::shared_ptr<ABnfElement>> dec_list;
        index->FindALittleNameDecList(ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::ENUM, dec->GetDescriptor());
    }
    // 处理单例
    {
        std::vector<std::shared_ptr<ABnfElement>> dec_list;
        index->FindALittleNameDecList(ABnfElementType::INSTANCE_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::INSTANCE, dec->GetDescriptor());
    }

    // 处理参数
    auto method_dec = m_method_dec.lock();
    if (method_dec != nullptr)
    {
        std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>> dec_list;
        ALittleScriptUtility::FindMethodParamNameDecList(method_dec, u8"", dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::PARAM, dec->GetDescriptor());
    }

    // 处理表达式
    {
        std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>> dec_list;
        ALittleScriptUtility::FindVarAssignNameDecList(element, u8"", dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::VARIABLE, dec->GetDescriptor());
    }

    return true;
}

ABnfElementPtr ALittleScriptPropertyValueCustomTypeReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    std::vector<ABnfElementPtr> result_list;
    CalcResolve(result_list);
    for (auto& result : result_list)
        return result;
    return nullptr;
}

void ALittleScriptPropertyValueCustomTypeReference::QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return;

    CollectHighlight(guess, m_method_body_dec.lock(), list);

    // 处理参数
    auto method_dec = m_method_dec.lock();
    if (method_dec != nullptr)
    {
        std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>> dec_list;
        ALittleScriptUtility::FindMethodParamNameDecList(method_dec, m_key, dec_list);
        for (auto& dec : dec_list)
        {
            ALanguageHighlightWordInfo info;
            info.line_start = dec->GetStartLine();
            info.char_start = dec->GetStartCol();
            info.line_end = dec->GetEndLine();
            info.char_end = dec->GetEndCol();
            list.push_back(info);
        }
    }
}

void ALittleScriptPropertyValueCustomTypeReference::CollectHighlight(ABnfGuessPtr target_guess, ABnfElementPtr element, std::vector<ALanguageHighlightWordInfo>& list)
{
    if (std::dynamic_pointer_cast<ALittleScriptPropertyValueCustomTypeElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(element))
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
    if (node != nullptr)
    {
        const auto& childs = node->GetChilds();
        for (auto& child : childs)
            CollectHighlight(target_guess, child, list);
    }
}
