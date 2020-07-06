#include "ALittleScriptElseIfConditionElement.h"

#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptValueStatElement> ALittleScriptElseIfConditionElement::GetValueStat()
{
    if (m_flag_ValueStat) return m_cache_ValueStat;
    m_flag_ValueStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ValueStat = node;
            break;
        }
    }
    return m_cache_ValueStat;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptElseIfConditionElement::GetStringList()
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

