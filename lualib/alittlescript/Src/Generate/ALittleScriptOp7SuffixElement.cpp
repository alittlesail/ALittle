#include "ALittleScriptOp7SuffixElement.h"

#include "ALittleScriptOp7Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp7SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp7Element> ALittleScriptOp7SuffixElement::GetOp7()
{
    if (m_flag_Op7) return m_cache_Op7;
    m_flag_Op7 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp7Element>(child);
        if (node != nullptr)
        {
            m_cache_Op7 = node;
            break;
        }
    }
    return m_cache_Op7;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp7SuffixElement::GetValueFactorStat()
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
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp7SuffixElement::GetOp2Value()
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
const std::vector<std::shared_ptr<ALittleScriptOp7SuffixEeElement>>& ALittleScriptOp7SuffixElement::GetOp7SuffixEeList()
{
    if (m_flag_Op7SuffixEe) return m_list_Op7SuffixEe;
    m_flag_Op7SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp7SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op7SuffixEe.push_back(node);
    }
    return m_list_Op7SuffixEe;
}

