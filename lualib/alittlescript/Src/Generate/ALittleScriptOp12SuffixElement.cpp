#include "ALittleScriptOp12SuffixElement.h"

#include "ALittleScriptOp12Element.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp12SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp12Element> ALittleScriptOp12SuffixElement::GetOp12()
{
    if (m_flag_Op12) return m_cache_Op12;
    m_flag_Op12 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp12Element>(child);
        if (node != nullptr)
        {
            m_cache_Op12 = node;
            break;
        }
    }
    return m_cache_Op12;
}
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp12SuffixElement::GetOp2Value()
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
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp12SuffixElement::GetValueFactorStat()
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
const std::vector<std::shared_ptr<ALittleScriptOp12SuffixEeElement>>& ALittleScriptOp12SuffixElement::GetOp12SuffixEeList()
{
    if (m_flag_Op12SuffixEe) return m_list_Op12SuffixEe;
    m_flag_Op12SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp12SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op12SuffixEe.push_back(node);
    }
    return m_list_Op12SuffixEe;
}

