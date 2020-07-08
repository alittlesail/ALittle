#include "ALittleScriptVarAssignDecReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptVarAssignExprElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"
#include "../Generate/ALittleScriptVarAssignDecElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptTemplatePairDecElement.h"
#include "../Generate/ALittleScriptTemplateNameDecElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"
#include "../Guess/ALittleScriptGuessStruct.h"

ALittleScriptVarAssignDecReference::ALittleScriptVarAssignDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptVarAssignDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
}

std::shared_ptr<ALittleScriptClassDecElement> ALittleScriptVarAssignDecReference::GetClassDec()
{
    auto class_dec = m_class_dec.lock();
    if (class_dec != nullptr) return class_dec;
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    class_dec = ALittleScriptUtility::FindClassDecFromParent(element);
    m_class_dec = class_dec;
    return class_dec;
}

std::shared_ptr<ALittleScriptTemplateDecElement> ALittleScriptVarAssignDecReference::GetTemplateDec()
{
    auto template_param_dec = m_template_param_dec.lock();
    if (template_param_dec != nullptr) return template_param_dec;
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    template_param_dec = ALittleScriptUtility::FindMethodTemplateDecFromParent(element);
    m_template_param_dec = template_param_dec;
    return template_param_dec;
}

ABnfGuessError ALittleScriptVarAssignDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    
    auto all_type = element->GetAllType();
    if (all_type != nullptr) return all_type->GuessTypes(guess_list);

    guess_list.resize(0);
    auto name_dec = element->GetVarAssignNameDec();
    if (name_dec == nullptr) return nullptr;

    auto parent = std::dynamic_pointer_cast<ALittleScriptVarAssignExprElement>(element->GetParent());
    auto value_stat = parent->GetValueStat();
    if (value_stat == nullptr)
        return ABnfGuessError(name_dec, u8"没有赋值对象，无法推导类型");

    // 获取等号左边的变量定义列表
    const auto& pair_dec_list = parent->GetVarAssignDecList();
    // 计算当前是第几个参数
    int index = -1;
    for (size_t i = 0; i < pair_dec_list.size(); ++i)
    {
        if (pair_dec_list[i] == element)
        {
            index = static_cast<int>(i);
            break;
        }
    }
    // 获取函数对应的那个返回值类型
    std::vector<ABnfGuessPtr> method_call_guess_list;
    auto error = value_stat->GuessTypes(method_call_guess_list);
    if (error) return error;
    // 如果有"..."作为返回值结尾
    bool hasTail = method_call_guess_list.size() > 0 && std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(method_call_guess_list[method_call_guess_list.size() - 1]);
    if (hasTail)
    {
        if (index >= method_call_guess_list.size() - 1)
            guess_list.push_back(ALittleScriptStatic::Inst().sAnyGuess);
        else
            guess_list.push_back(method_call_guess_list[index]);
    }
    else
    {
        if (index >= method_call_guess_list.size())
            return ABnfGuessError(element, u8"没有赋值对象，无法推导类型");
        guess_list.push_back(method_call_guess_list[index]);
    }

    return nullptr;
}

bool ALittleScriptVarAssignDecReference::QueryCompletion(std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;
    auto* index = GetIndex();
    if (index == nullptr) return false;

    // 查找该命名域下的
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::USING_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
        {
            ABnfGuessPtr guess;
            auto error = dec->GuessType(guess);
            if (error)
            {
                list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
            }
            else
            {
                if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
                    list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
                else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
                    list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptStructName);
                else
                    list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
            }
        }
    }

    // 查找对应命名域下的类名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptClassName);
    }
    // 查找类模板
    {
        auto class_dec = GetClassDec();
        if (class_dec != nullptr)
        {
            std::vector<ABnfElementPtr> dec_list;
            index->FindClassAttrList(class_dec, ALittleScriptUtility::sAccessPrivateAndProtectedAndPublic
                , ClassAttrType::TEMPLATE, u8"", dec_list);
            for (auto& dec : dec_list)
            {
                auto pair_dec = std::dynamic_pointer_cast<ALittleScriptTemplatePairDecElement>(dec);
                auto pair_name_dec = pair_dec->GetTemplateNameDec();
                if (pair_name_dec != nullptr)
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptTemplateName);
            }
        }
    }
    // 查找函数模板
    {
        auto template_dec = GetTemplateDec();
        if (template_dec != nullptr)
        {
            const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
            for (auto& pair_dec : pair_dec_list)
            {
                auto pair_name_dec = pair_dec->GetTemplateNameDec();
                if (pair_name_dec != nullptr)
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptColorType::ALittleScriptTemplateName);
            }
        }
    }
    // 结构体名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptStructName);
    }
    // 枚举名
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptEnumName);
    }
    // 查找全局函数
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptColorType::ALittleScriptGlobalMethodName);
    }
    // 查找所有命名域
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_map;
        index->FindNamespaceNameDecList("", dec_map);
        for (auto& pair : dec_map)
            list.emplace_back(pair.second->GetElementText(), ALittleScriptColorType::ALittleScriptNamespaceName);
    }

    return true;
}
