#include "ALittleScriptOp2ValueElement.h"

#include "ALittleScriptOp2Element.h"
#include "ALittleScriptValueFactorStatElement.h"

std::shared_ptr<ALittleScriptOp2Element> ALittleScriptOp2ValueElement::GetOp2()
{
    if (m_flag_Op2) return m_cache_Op2;
    m_flag_Op2 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp2Element>(child);
        if (node != nullptr)
        {
            m_cache_Op2 = node;
            break;
        }
    }
    return m_cache_Op2;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp2ValueElement::GetValueFactorStat()
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

