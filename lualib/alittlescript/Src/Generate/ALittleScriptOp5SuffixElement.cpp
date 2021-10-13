#include "ALittleScriptOp5SuffixElement.h"

#include "ALittleScriptOp5Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp5SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp5Element> ALittleScriptOp5SuffixElement::GetOp5()
{
    if (m_flag_Op5) return m_cache_Op5;
    m_flag_Op5 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp5Element>(child);
        if (node != nullptr)
        {
            m_cache_Op5 = node;
            break;
        }
    }
    return m_cache_Op5;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp5SuffixElement::GetValueFactorStat()
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
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp5SuffixElement::GetOp2Value()
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
const std::vector<std::shared_ptr<ALittleScriptOp5SuffixEeElement>>& ALittleScriptOp5SuffixElement::GetOp5SuffixEeList()
{
    if (m_flag_Op5SuffixEe) return m_list_Op5SuffixEe;
    m_flag_Op5SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp5SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op5SuffixEe.push_back(node);
    }
    return m_list_Op5SuffixEe;
}

