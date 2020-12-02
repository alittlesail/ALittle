#include "ALittleScriptOp9SuffixElement.h"

#include "ALittleScriptOp9Element.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp9SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp9Element> ALittleScriptOp9SuffixElement::GetOp9()
{
    if (m_flag_Op9) return m_cache_Op9;
    m_flag_Op9 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp9Element>(child);
        if (node != nullptr)
        {
            m_cache_Op9 = node;
            break;
        }
    }
    return m_cache_Op9;
}
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp9SuffixElement::GetOp2Value()
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
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp9SuffixElement::GetValueFactorStat()
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
const std::vector<std::shared_ptr<ALittleScriptOp9SuffixEeElement>>& ALittleScriptOp9SuffixElement::GetOp9SuffixEeList()
{
    if (m_flag_Op9SuffixEe) return m_list_Op9SuffixEe;
    m_flag_Op9SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp9SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op9SuffixEe.push_back(node);
    }
    return m_list_Op9SuffixEe;
}

