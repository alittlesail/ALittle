#include "ALittleScriptOp6SuffixElement.h"

#include "ALittleScriptOp6Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp6SuffixEeElement.h"
#include "ALittleScriptOp2ValueElement.h"

std::shared_ptr<ALittleScriptOp6Element> ALittleScriptOp6SuffixElement::GetOp6()
{
    if (m_flag_Op6) return m_cache_Op6;
    m_flag_Op6 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp6Element>(child);
        if (node != nullptr)
        {
            m_cache_Op6 = node;
            break;
        }
    }
    return m_cache_Op6;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp6SuffixElement::GetValueFactorStat()
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
const std::vector<std::shared_ptr<ALittleScriptOp6SuffixEeElement>>& ALittleScriptOp6SuffixElement::GetOp6SuffixEeList()
{
    if (m_flag_Op6SuffixEe) return m_list_Op6SuffixEe;
    m_flag_Op6SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp6SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op6SuffixEe.push_back(node);
    }
    return m_list_Op6SuffixEe;
}
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp6SuffixElement::GetOp2Value()
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

