#include "ALittleScriptEnumNameDecReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

ALittleScriptEnumNameDecReference::ALittleScriptEnumNameDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptEnumNameDecElement>(element)
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
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
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

bool ALittleScriptEnumNameDecReference::QueryCompletion(std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    auto* index = GetIndex();
    std::vector<ABnfElementPtr> dec_list;
    index->FindALittleNameDecList(
        ABnfElementType::ENUM_NAME, element->GetFile(), m_namespace_name, m_key, true, dec_list);

    for (auto& dec : dec_list)
        list.emplace_back(dec->GetElementText(), ALittleScriptIconType::ENUM);

    return true;
}

ABnfGuessError ALittleScriptEnumNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    if (element->GetElementText().find("___") == 0)
        return ABnfGuessError(element, u8"枚举名不能以3个下划线开头");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"重复定义");
    return nullptr;
}
