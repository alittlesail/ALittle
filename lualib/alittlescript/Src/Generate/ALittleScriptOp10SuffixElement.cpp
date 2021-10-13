#include "ALittleScriptOp10SuffixElement.h"

#include "ALittleScriptOp10Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp10SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp10Element> ALittleScriptOp10SuffixElement::GetOp10()
{
    if (m_flag_Op10) return m_cache_Op10;
    m_flag_Op10 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp10Element>(child);
        if (node != nullptr)
        {
            m_cache_Op10 = node;
            break;
        }
    }
    return m_cache_Op10;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp10SuffixElement::GetValueFactorStat()
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
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp10SuffixElement::GetOp2Value()
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
const std::vector<std::shared_ptr<ALittleScriptOp10SuffixEeElement>>& ALittleScriptOp10SuffixElement::GetOp10SuffixEeList()
{
    if (m_flag_Op10SuffixEe) return m_list_Op10SuffixEe;
    m_flag_Op10SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp10SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op10SuffixEe.push_back(node);
    }
    return m_list_Op10SuffixEe;
}

