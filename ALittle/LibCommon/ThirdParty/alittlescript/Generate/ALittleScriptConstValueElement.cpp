#include "ALittleScriptConstValueElement.h"

#include "ALittleScriptTextElement.h"
#include "ALittleScriptNumberElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptTextElement> ALittleScriptConstValueElement::GetText()
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
std::shared_ptr<ALittleScriptNumberElement> ALittleScriptConstValueElement::GetNumber()
{
    if (m_flag_Number) return m_cache_Number;
    m_flag_Number = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptNumberElement>(child);
        if (node != nullptr)
        {
            m_cache_Number = node;
            break;
        }
    }
    return m_cache_Number;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptConstValueElement::GetKey()
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

