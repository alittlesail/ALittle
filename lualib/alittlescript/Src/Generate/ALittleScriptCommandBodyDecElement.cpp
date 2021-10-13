#include "ALittleScriptCommandBodyDecElement.h"

#include "ALittleScriptTextElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptTextElement> ALittleScriptCommandBodyDecElement::GetText()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptCommandBodyDecElement::GetStringList()
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

