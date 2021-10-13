#include "ALittleScriptOp3SuffixElement.h"

#include "ALittleScriptOp3Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp2ValueElement.h"

std::shared_ptr<ALittleScriptOp3Element> ALittleScriptOp3SuffixElement::GetOp3()
{
    if (m_flag_Op3) return m_cache_Op3;
    m_flag_Op3 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp3Element>(child);
        if (node != nullptr)
        {
            m_cache_Op3 = node;
            break;
        }
    }
    return m_cache_Op3;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp3SuffixElement::GetValueFactorStat()
{
    if (m_flag_ValueFactorStat) return m_cache_ValueFactorStat;
    m_flag_ValueFactorStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueFactorStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ValueFactorStat = node;
            break;
        }
    }
    return m_cache_ValueFactorStat;
}
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp3SuffixElement::GetOp2Value()
{
    if (m_flag_Op2Value) return m_cache_Op2Value;
    m_flag_Op2Value = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp2ValueElement>(child);
        if (node != nullptr)
        {
            m_cache_Op2Value = node;
            break;
        }
    }
    return m_cache_Op2Value;
}

