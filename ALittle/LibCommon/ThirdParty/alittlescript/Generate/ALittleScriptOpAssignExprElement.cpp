#include "ALittleScriptOpAssignExprElement.h"

#include "ALittleScriptPropertyValueElement.h"
#include "ALittleScriptOpAssignElement.h"
#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptPropertyValueElement>>& ALittleScriptOpAssignExprElement::GetPropertyValueList()
{
    if (m_flag_PropertyValue) return m_list_PropertyValue;
    m_flag_PropertyValue = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(child);
        if (node != nullptr)
            m_list_PropertyValue.push_back(node);
    }
    return m_list_PropertyValue;
}
std::shared_ptr<ALittleScriptOpAssignElement> ALittleScriptOpAssignExprElement::GetOpAssign()
{
    if (m_flag_OpAssign) return m_cache_OpAssign;
    m_flag_OpAssign = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOpAssignElement>(child);
        if (node != nullptr)
        {
            m_cache_OpAssign = node;
            break;
        }
    }
    return m_cache_OpAssign;
}
std::shared_ptr<ALittleScriptValueStatElement> ALittleScriptOpAssignExprElement::GetValueStat()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptOpAssignExprElement::GetStringList()
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

