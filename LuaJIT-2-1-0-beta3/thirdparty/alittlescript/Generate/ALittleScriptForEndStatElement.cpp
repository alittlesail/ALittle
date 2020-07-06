#include "ALittleScriptForEndStatElement.h"

#include "ALittleScriptValueStatElement.h"

std::shared_ptr<ALittleScriptValueStatElement> ALittleScriptForEndStatElement::GetValueStat()
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

