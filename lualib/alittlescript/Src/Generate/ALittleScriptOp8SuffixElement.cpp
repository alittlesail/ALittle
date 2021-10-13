#include "ALittleScriptOp8SuffixElement.h"

#include "ALittleScriptOp8Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp8SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp8Element> ALittleScriptOp8SuffixElement::GetOp8()
{
    if (m_flag_Op8) return m_cache_Op8;
    m_flag_Op8 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp8Element>(child);
        if (node != nullptr)
        {
            m_cache_Op8 = node;
            break;
        }
    }
    return m_cache_Op8;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp8SuffixElement::GetValueFactorStat()
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
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp8SuffixElement::GetOp2Value()
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
const std::vector<std::shared_ptr<ALittleScriptOp8SuffixEeElement>>& ALittleScriptOp8SuffixElement::GetOp8SuffixEeList()
{
    if (m_flag_Op8SuffixEe) return m_list_Op8SuffixEe;
    m_flag_Op8SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp8SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op8SuffixEe.push_back(node);
    }
    return m_list_Op8SuffixEe;
}

