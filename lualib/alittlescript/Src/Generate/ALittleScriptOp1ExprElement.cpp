#include "ALittleScriptOp1ExprElement.h"

#include "ALittleScriptOp1Element.h"
#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptOp1Element> ALittleScriptOp1ExprElement::GetOp1()
{
    if (m_flag_Op1) return m_cache_Op1;
    m_flag_Op1 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp1Element>(child);
        if (node != nullptr)
        {
            m_cache_Op1 = node;
            break;
        }
    }
    return m_cache_Op1;
}
std::shared_ptr<ALittleScriptValueStatElement> ALittleScriptOp1ExprElement::GetValueStat()
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
std::shared_ptr<ALittleScriptStringElement> ALittleScriptOp1ExprElement::GetString()
{
    if (m_flag_String) return m_cache_String;
    m_flag_String = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
        if (node != nullptr)
        {
            m_cache_String = node;
            break;
        }
    }
    return m_cache_String;
}

