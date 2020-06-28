
#include "ABnfFileClass.h"
#include "ABnfCommonReference.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnfNodeElement.h"
#include "ALittle/LibCommon/ThirdParty/alanguage/Model/ABnf.h"
#include "ALittle/LibCommon/Helper/StringHelper.h"
#include "ABnfIdReference.h"
#include "ABnfFileClass.h"

#include <unordered_set>

ABnfIdReference::ABnfIdReference(ABnfElementPtr element) : ABnfCommonReference(element)
{
}

void ABnfIdReference::QueryQuickInfo(std::string& info)
{
    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(m_element->GetFile());
    if (file == nullptr) return;

    auto it = file->GetRuleSet().find(m_element->GetElementText());
    if (it == file->GetRuleSet().end()) return;

    std::vector<std::string> content_list;
    for (auto rule : it->second)
        content_list.push_back(rule->GetElementText());

    info = ALittle::StringHelper::Join(content_list, "\n");
}

bool ABnfIdReference::QueryCompletion(int offset, std::vector<ALanguageCompletionInfo>& list)
{
    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(m_element->GetFile());
    if (file == nullptr) return false;

    for (auto& pair : file->GetRuleSet())
    {
        if (pair.first.find(m_element->GetElementText()) == 0)
        {
            ALanguageCompletionInfo info;
            info.display = pair.first;
            list.push_back(info);
        }
    }
    return true;
}

// ¼ì²é´íÎó
bool ABnfIdReference::CheckError(ABnfGuessError& error)
{
    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(m_element->GetFile());
    if (file == nullptr) return false;

    const auto& text = m_element->GetElementText();

    auto it = file->GetRuleSet().find(text);
    if (it == file->GetRuleSet().end())
    {
        auto parent = m_element->GetParent();
        if (parent == nullptr || parent->GetNodeType() != "Expression")
        {
            error.element = m_element;
            error.error = "unknow type";
            return true;
        }
    }
    else if (it->second.size() > 1)
    {
        error.element = m_element;
        error.error = "repeated define";
        return true;
    }

    if (text.size() != 0 && text[0] >= '0' && text[0] <= '9')
    {
        error.element = m_element;
        error.error = "rule name must not start with number";
        return true;
    }

    return false;
}

void ABnfIdReference::QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list)
{
    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(m_element->GetFile());
    if (file == nullptr) return;

    auto it = file->GetIndex().find(m_element->GetElementText());
    if (it == file->GetIndex().end()) return;

    for (auto element : it->second)
    {
        ALanguageHighlightWordInfo info;
        info.line_start = element->GetStartLine();
        info.char_start = element->GetStartCol();
        info.line_end = element->GetEndLine();
        info.char_end = element->GetEndCol();
        list.push_back(info);
    }
}

// Ìø×ª
ABnfElementPtr ABnfIdReference::GotoDefinition()
{
    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(m_element->GetFile());
    if (file == nullptr) return nullptr;

    auto it = file->GetRuleSet().find(m_element->GetElementText());
    if (it == file->GetRuleSet().end())
        return nullptr;

    for (auto e : it->second) return e;
    return nullptr;
}
