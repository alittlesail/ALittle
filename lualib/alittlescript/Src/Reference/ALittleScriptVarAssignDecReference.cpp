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

ALittleScriptVarAssignDecReference::ALittleScriptVarAssignDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptVarAssignDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
}

std::shared_ptr<ALittleScriptClassDecElement> ALittleScriptVarAssignDecReference::GetClassDec()
{
    auto class_dec = m_class_dec.lock();
    if (class_dec != nullptr) return class_dec;
    const auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    class_dec = ALittleScriptUtility::FindClassDecFromParent(element);
    m_class_dec = class_dec;
    return class_dec;
}

std::shared_ptr<ALittleScriptTemplateDecElement> ALittleScriptVarAssignDecReference::GetTemplateDec()
{
    auto template_param_dec = m_template_param_dec.lock();
    if (template_param_dec != nullptr) return template_param_dec;
    const auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    template_param_dec = ALittleScriptUtility::FindMethodTemplateDecFromParent(element);
    m_template_param_dec = template_param_dec;
    return template_param_dec;
}

ABnfGuessError ALittleScriptVarAssignDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    
    auto all_type = element->GetAllType();
    if (all_type != nullptr) return all_type->GuessTypes(guess_list);

    guess_list.resize(0);
    const auto name_dec = element->GetVarAssignNameDec();
    if (name_dec == nullptr) return nullptr;

    auto parent = std::dynamic_pointer_cast<ALittleScriptVarAssignExprElement>(element->GetParent());
    auto value_stat = parent->GetValueStat();
    if (value_stat == nullptr)
        return ABnfGuessError(name_dec, u8"û�и�ֵ�����޷��Ƶ�����");

    // ��ȡ�Ⱥ���ߵı��������б�
    const auto& pair_dec_list = parent->GetVarAssignDecList();
    // ���㵱ǰ�ǵڼ�������
    int index = -1;
    for (size_t i = 0; i < pair_dec_list.size(); ++i)
    {
        if (pair_dec_list[i] == element)
        {
            index = static_cast<int>(i);
            break;
        }
    }
    // ��ȡ������Ӧ���Ǹ�����ֵ����
    std::vector<ABnfGuessPtr> method_call_guess_list;
    auto error = value_stat->GuessTypes(method_call_guess_list);
    if (error) return error;
    // �����"..."��Ϊ����ֵ��β
    const bool hasTail = !method_call_guess_list.empty() && std::dynamic_pointer_cast<ALittleScriptGuessReturnTail>(method_call_guess_list[method_call_guess_list.size() - 1]);
    if (hasTail)
    {
        if (index >= static_cast<int>(method_call_guess_list.size()) - 1)
            guess_list.push_back(ALittleScriptStatic::Inst().sAnyGuess);
        else
            guess_list.push_back(method_call_guess_list[index]);
    }
    else
    {
        if (index >= static_cast<int>(method_call_guess_list.size()))
            return ABnfGuessError(element, u8"û�и�ֵ�����޷��Ƶ�����");
        guess_list.push_back(method_call_guess_list[index]);
    }

    return nullptr;
}

bool ALittleScriptVarAssignDecReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;
    auto* index = GetIndex();
    if (index == nullptr) return false;

    // ���Ҹ��������µ�
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
                list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
            }
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

    // ���Ҷ�Ӧ�������µ�����
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS, dec->GetDescriptor());
    }
    // ������ģ��
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
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptIconType::TEMPLATE, dec->GetDescriptor());
            }
        }
    }
    // ���Һ���ģ��
    {
        auto template_dec = GetTemplateDec();
        if (template_dec != nullptr)
        {
            const auto& pair_dec_list = template_dec->GetTemplatePairDecList();
            for (const auto& pair_dec : pair_dec_list)
            {
                auto pair_name_dec = pair_dec->GetTemplateNameDec();
                if (pair_name_dec != nullptr)
                    list.emplace_back(pair_name_dec->GetElementText(), ALittleScriptIconType::TEMPLATE, pair_name_dec->GetDescriptor());
            }
        }
    }
    // �ṹ����
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
    }
    // ö����
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::ENUM, dec->GetDescriptor());
    }
    // ����ȫ�ֺ���
    {
        std::vector<ABnfElementPtr> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::GLOBAL_METHOD, element->GetFile(), m_namespace_name, u8"", true, dec_list);
        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::GLOBAL_METHOD, dec->GetDescriptor());
    }
    // ��������������
    {
        std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> dec_map;
        index->FindNamespaceNameDecList("", dec_map);
        for (auto& pair : dec_map)
            list.emplace_back(pair.second->GetElementText(), ALittleScriptIconType::NAMESPACE, pair.second->GetDescriptor());
    }

    return true;
}
