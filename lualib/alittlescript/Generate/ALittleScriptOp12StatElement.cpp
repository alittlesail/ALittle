#include "ALittleScriptOp12StatElement.h"

#include "ALittleScriptOp12SuffixElement.h"
#include "ALittleScriptOp12SuffixExElement.h"

std::shared_ptr<ALittleScriptOp12SuffixElement> ALittleScriptOp12StatElement::GetOp12Suffix()
{
    if (m_flag_Op12Suffix) return m_cache_Op12Suffix;
    m_flag_Op12Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp12SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op12Suffix = node;
            break;
        }
    }
    return m_cache_Op12Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp12SuffixExElement>>& ALittleScriptOp12StatElement::GetOp12SuffixExList()
{
    if (m_flag_Op12SuffixEx) return m_list_Op12SuffixEx;
    m_flag_Op12SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp12SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op12SuffixEx.push_back(node);
    }
    return m_list_Op12SuffixEx;
}

