#include "ALittleScriptOp11SuffixElement.h"

#include "ALittleScriptOp11Element.h"
#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp11SuffixEeElement.h"

std::shared_ptr<ALittleScriptOp11Element> ALittleScriptOp11SuffixElement::GetOp11()
{
    if (m_flag_Op11) return m_cache_Op11;
    m_flag_Op11 = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp11Element>(child);
        if (node != nullptr)
        {
            m_cache_Op11 = node;
            break;
        }
    }
    return m_cache_Op11;
}
std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptOp11SuffixElement::GetValueFactorStat()
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
std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp11SuffixElement::GetOp2Value()
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
const std::vector<std::shared_ptr<ALittleScriptOp11SuffixEeElement>>& ALittleScriptOp11SuffixElement::GetOp11SuffixEeList()
{
    if (m_flag_Op11SuffixEe) return m_list_Op11SuffixEe;
    m_flag_Op11SuffixEe = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp11SuffixEeElement>(child);
        if (node != nullptr)
            m_list_Op11SuffixEe.push_back(node);
    }
    return m_list_Op11SuffixEe;
}

