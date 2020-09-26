#include "ALittleScriptNamespaceNameDecReference.h"

#include "../Index/ALittleScriptIndex.h"

ALittleScriptNamespaceNameDecReference::ALittleScriptNamespaceNameDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptNamespaceNameDecElement>(element)
{
    m_key = element->GetElementText();
}

int ALittleScriptNamespaceNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::DEFINE_NAME;
}

ABnfGuessError ALittleScriptNamespaceNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto* index = GetIndex();
    if (index == nullptr) return ABnfGuessError(nullptr, u8"不再工程中");

    guess_list.resize(0);
    if (m_key.size() == 0) return nullptr;

    std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> name_dec_map;
    index->FindNamespaceNameDecList(m_key, name_dec_map);
    for (auto& pair : name_dec_map)
    {
        auto parent = pair.second->GetParent();
        if (parent == nullptr) continue;
        ABnfGuessPtr guess;
        auto error = parent->GuessType(guess);
        if (error) return error;
        guess_list.push_back(guess);
    }
    return nullptr;
}

ABnfGuessError ALittleScriptNamespaceNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    if (element->GetElementText().find("___") == 0)
        return ABnfGuessError(element, u8"命名域不能以3个下划线开头");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    return nullptr;
}

ABnfElementPtr ALittleScriptNamespaceNameDecReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    auto* index = GetIndex();
    if (index == nullptr) return nullptr;

    std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> name_dec_map;
    index->FindNamespaceNameDecList(m_key, name_dec_map);
    for (auto& pair : name_dec_map) return pair.second;
    return nullptr;
}

bool ALittleScriptNamespaceNameDecReference::QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list)
{
    auto* index = GetIndex();
    if (index == nullptr) return false;
    std::unordered_map<std::string, std::shared_ptr<ALittleScriptNamespaceNameDecElement>> name_dec_map;
    index->FindNamespaceNameDecList("", name_dec_map);
    for (auto& pair : name_dec_map)
    {
        if (m_key == pair.second->GetElementText()) continue;
        list.emplace_back(pair.second->GetElementText(), ALittleScriptIconType::NAMESPACE, pair.second->GetDescriptor());
    }
    return true;
}
