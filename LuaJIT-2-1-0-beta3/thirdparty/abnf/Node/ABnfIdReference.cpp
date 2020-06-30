
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
    auto element = m_element.lock();
    if (element == nullptr) return;

    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return;

    auto it = file->GetRuleSet().find(element->GetElementText());
    if (it == file->GetRuleSet().end()) return;

    std::vector<std::string> content_list;
    for (auto pair : it->second)
        content_list.push_back(pair.first->GetElementText());

    info = ALittle::StringHelper::Join(content_list, "\n");
}

bool ABnfIdReference::QueryCompletion(std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return false;

    for (auto& pair : file->GetRuleSet())
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
bool ABnfIdReference::CheckError(ABnfGuessError& error)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return false;

    const auto& text = element->GetElementText();

    auto it = file->GetRuleSet().find(text);
    if (it == file->GetRuleSet().end())
    {
        auto parent = element->GetParent();
        if (parent == nullptr || parent->GetNodeType() != "Expression")
        {
            error.element = element;
            error.error = "unknow type";
            return true;
        }
    }
    else if (it->second.size() > 1)
    {
        error.element = element;
        error.error = "repeated define";
        return true;
    }

    if (text.size() != 0 && text[0] >= '0' && text[0] <= '9')
    {
        error.element = element;
        error.error = "rule name must not start with number";
        return true;
    }

    return false;
}

void ABnfIdReference::QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return;

    auto it = file->GetIndex().find(element->GetElementText());
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
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;

    ABnfFileClass* file = dynamic_cast<ABnfFileClass*>(element->GetFile());
    if (file == nullptr) return nullptr;

    auto it = file->GetRuleSet().find(element->GetElementText());
    if (it == file->GetRuleSet().end())
        return nullptr;

    for (auto pair : it->second)
    {
        if (pair.first->GetChilds().size() > 0)
            return pair.first->GetChilds()[0];
    }
    return nullptr;
}
