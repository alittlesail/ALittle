#include "ALittleScriptPathsValueElement.h"

#include "ALittleScriptTextElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptTextElement> ALittleScriptPathsValueElement::GetText()
{
    if (m_flag_Text) return m_cache_Text;
    m_flag_Text = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTextElement>(child);
        if (node != nullptr)
        {
            m_cache_Text = node;
            break;
        }
    }
    return m_cache_Text;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptPathsValueElement::GetKey()
{
    if (m_flag_Key) return m_cache_Key;
    m_flag_Key = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptKeyElement>(child);
        if (node != nullptr)
        {
            m_cache_Key = node;
            break;
        }
    }
    return m_cache_Key;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptPathsValueElement::GetStringList()
{
    if (m_flag_String) return m_list_String;
    m_flag_String = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
        if (node != nullptr)
            m_list_String.push_back(node);
    }
    return m_list_String;
}

