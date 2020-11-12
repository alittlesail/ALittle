
#include "ABnfIdReference.h"
#include "../../alanguage/Model/ABnfElement.h"
#include "../../alanguage/Model/ABnfNodeElement.h"
#include "../../alanguage/Model/ABnf.h"
#include "../../alanguage/Index/ABnfFactory.h"
#include "../Index/ABnfFileClass.h"

#include <unordered_set>

ABnfIdReference::ABnfIdReference(const ABnfElementPtr& element) : ABnfCommonReference(element)
{
}

void ABnfIdReference::QueryQuickInfo(std::string& info)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    auto* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return;

    auto it = file->GetRuleSet().find(element->GetElementText());
    if (it == file->GetRuleSet().end()) return;

    std::vector<std::string> content_list;
    for (const auto& pair : it->second)
        content_list.push_back(pair.first->GetElementText());

    info = ABnfFactory::Join(content_list, "\n");
}

bool ABnfIdReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    auto* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return false;

    for (const auto& pair : file->GetRuleSet())
    {
        if (pair.first.find(element->GetElementText()) == 0)
        {
            ALanguageCompletionInfo info;
            info.display = pair.first;
            if (!pair.second.empty())
                info.descriptor = pair.second.begin()->second;
            list.push_back(info);
        }
    }
    return true;
}

// ¼ì²é´íÎó
ABnfGuessError ABnfIdReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    auto* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return nullptr;

    const auto& text = element->GetElementText();

    const auto it = file->GetRuleSet().find(text);
    if (it == file->GetRuleSet().end())
    {
        auto parent = element->GetParent();
        if (parent == nullptr || parent->GetNodeType() != "Expression")
            return ABnfGuessError(element, "unknown type");
    }
    else if (it->second.size() > 1)
        return ABnfGuessError(element, "repeated define");

    if (!text.empty() && text[0] >= '0' && text[0] <= '9')
        return ABnfGuessError(element, "rule name must not start with number");

    return nullptr;
}

void ABnfIdReference::QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    auto* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return;

    auto it = file->GetIndex().find(element->GetElementText());
    if (it == file->GetIndex().end()) return;

    for (const auto& child : it->second)
    {
        ALanguageHighlightWordInfo info;
        info.line_start = child->GetStartLine();
        info.char_start = child->GetStartCol();
        info.line_end = child->GetEndLine();
        info.char_end = child->GetEndCol();
        list.push_back(info);
    }
}

// Ìø×ª
ABnfElementPtr ABnfIdReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    auto* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return nullptr;

    auto it = file->GetRuleSet().find(element->GetElementText());
    if (it == file->GetRuleSet().end())
        return nullptr;

    for (const auto& pair : it->second)
    {
        if (!pair.first->GetChilds().empty())
            return pair.first->GetChilds()[0];
    }
    return nullptr;
}
