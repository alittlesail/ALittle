#include "ALittleScriptStructNameDecReference.h"

#include "../Generate/ALittleScriptStructExtendsDecElement.h"
#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptStructDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

ALittleScriptStructNameDecReference::ALittleScriptStructNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptStructNameDecElement>(element)
{
    m_key = element->GetElementText();
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);

    // ������ڵ���extends����ô�ͻ�ȡָ����������
    const auto parent = element->GetParent();
    if (std::dynamic_pointer_cast<ALittleScriptStructExtendsDecElement>(parent))
    {
        auto namespace_name_dec = std::dynamic_pointer_cast<ALittleScriptStructExtendsDecElement>(parent)->GetNamespaceNameDec();
        if (namespace_name_dec != nullptr)
            m_namespace_name = namespace_name_dec->GetElementText();
    }
}

int ALittleScriptStructNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::DEFINE_NAME;
}

ABnfGuessError ALittleScriptStructNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    auto* index = GetIndex();
    if (index == nullptr) return ABnfGuessError(element, u8"���ڹ�����");

    guess_list.resize(0);
    auto parent = element->GetParent();

    // ���ֱ�Ӿ��Ƕ��壬��ôֱ�ӻ�ȡ
    if (std::dynamic_pointer_cast<ALittleScriptStructDecElement>(parent))
    {
        ABnfGuessPtr guess;
        auto error = parent->GuessType(guess);
        if (error) return error;
        guess_list.push_back(guess);
        // ����Ǽ̳���ô�ʹӼ̳��Ǳ߻�ȡ
    }
    else if (std::dynamic_pointer_cast<ALittleScriptStructExtendsDecElement>(parent))
    {
        if (m_key.empty()) return nullptr;
        std::vector<std::shared_ptr<ABnfElement>> struct_name_dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, m_key, true, struct_name_dec_list);
        for (auto& struct_name_dec : struct_name_dec_list)
        {
            ABnfGuessPtr guess;
            auto error = struct_name_dec->GuessType(guess);
            if (error) return error;
            guess_list.push_back(guess);
        }
    }
    return nullptr;
}

ABnfElementPtr ALittleScriptStructNameDecReference::GotoDefinition()
{
    const auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    auto* index = GetIndex();
    if (index == nullptr) return nullptr;

    std::vector<std::shared_ptr<ABnfElement>> dec_list;
    index->FindALittleNameDecList(
        ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
    for (auto& dec : dec_list) return dec;
    return nullptr;
}

bool ALittleScriptStructNameDecReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return false;
    auto* index = GetIndex();
    if (index == nullptr) return false;

    std::vector<std::shared_ptr<ABnfElement>> dec_list;
    index->FindALittleNameDecList(
        ABnfElementType::STRUCT_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);

    for (auto& dec : dec_list)
    {
        if (m_key == dec->GetElementText()) continue;
        list.emplace_back(dec->GetElementText(), ALittleScriptIconType::STRUCT, dec->GetDescriptor());
    }   

    return true;
}

ABnfGuessError ALittleScriptStructNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetElementText().find("___") == 0)
        return ABnfGuessError(element, u8"�ṹ����������3���»��߿�ͷ");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"δ֪����");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"�ظ�����");
    return nullptr;
}
