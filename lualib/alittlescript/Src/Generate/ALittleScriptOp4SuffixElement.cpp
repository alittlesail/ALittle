#include "ALittleScriptOp4SuffixElement.h"

#include "ALittleScriptOp4Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp4SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp4Element> ALittleScriptOp4SuffixElement::GetOp4()
{
    if (m_flag_Op4) return m_cache_Op4;
    m_flag_Op4 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp4Element>(child);
        if (node != nullptr)
        {
            m_cache_Op4 = node;
            break;
        }
    }
    return m_cache_Op4;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp4SuffixElement::GetValueFactorStat()
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
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp4SuffixElement::GetOp2Value()
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
const std::vector<std::shared_ptr<ALittleScriptOp4SuffixEeElement>>& ALittleScriptOp4SuffixElement::GetOp4SuffixEeList()
{
    if (m_flag_Op4SuffixEe) return m_list_Op4SuffixEe;
    m_flag_Op4SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp4SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op4SuffixEe.push_back(node);
    }
    return m_list_Op4SuffixEe;
}

