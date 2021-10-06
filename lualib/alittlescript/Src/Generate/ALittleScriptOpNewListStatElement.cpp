#include "ALittleScriptOpNewListStatElement.h"

#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& ALittleScriptOpNewListStatElement::GetValueStatList()
{
    if (m_flag_ValueStat) return m_list_ValueStat;
    m_flag_ValueStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
        if (node != nullptr)
            m_list_ValueStat.push_back(node);
    }
    return m_list_ValueStat;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptOpNewListStatElement::GetStringList()
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

