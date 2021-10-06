#include "ALittleScriptEnumNameDecReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

ALittleScriptEnumNameDecReference::ALittleScriptEnumNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptEnumNameDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
    m_key = element->GetElementText();
}

int ALittleScriptEnumNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::DEFINE_NAME;
}

ABnfGuessError ALittleScriptEnumNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    return element->GetParent()->GuessTypes(guess_list);
}

ABnfElementPtr ALittleScriptEnumNameDecReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    auto* index = GetIndex();
    std::vector<ABnfElementPtr> dec_list;
    index->FindALittleNameDecList(
        ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);
    for (auto& dec : dec_list) return dec;
    return nullptr;
}

bool ALittleScriptEnumNameDecReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return false;

    auto* index = GetIndex();
    std::vector<ABnfElementPtr> dec_list;
    index->FindALittleNameDecList(
        ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);

    for (auto& dec : dec_list)
    {
        if (m_key == dec->GetElementText()) continue;
        list.emplace_back(dec->GetElementText(), ALittleScriptIconType::ENUM, dec->GetDescriptor());
    }   

    return true;
}

ABnfGuessError ALittleScriptEnumNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetElementText().find("___") == 0)
        return ABnfGuessError(element, u8"ö����������3���»��߿�ͷ");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"δ֪����");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"�ظ�����");
    return nullptr;
}
