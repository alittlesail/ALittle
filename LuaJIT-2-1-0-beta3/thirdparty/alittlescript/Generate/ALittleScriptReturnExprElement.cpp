#include "ALittleScriptReturnExprElement.h"

#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptReturnYieldElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& ALittleScriptReturnExprElement::GetValueStatList()
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
std::shared_ptr<ALittleScriptReturnYieldElement> ALittleScriptReturnExprElement::GetReturnYield()
{
    if (m_flag_ReturnYield) return m_cache_ReturnYield;
    m_flag_ReturnYield = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptReturnYieldElement>(child);
        if (node != nullptr)
        {
            m_cache_ReturnYield = node;
            break;
        }
    }
    return m_cache_ReturnYield;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptReturnExprElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptReturnExprElement::GetStringList()
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

