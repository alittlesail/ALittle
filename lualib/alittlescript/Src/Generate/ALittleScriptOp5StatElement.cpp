#include "ALittleScriptOp5StatElement.h"

#include "ALittleScriptOp5SuffixElement.h"
#include "ALittleScriptOp5SuffixExElement.h"

std::shared_ptr<ALittleScriptOp5SuffixElement> ALittleScriptOp5StatElement::GetOp5Suffix()
{
    if (m_flag_Op5Suffix) return m_cache_Op5Suffix;
    m_flag_Op5Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp5SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op5Suffix = node;
            break;
        }
    }
    return m_cache_Op5Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp5SuffixExElement>>& ALittleScriptOp5StatElement::GetOp5SuffixExList()
{
    if (m_flag_Op5SuffixEx) return m_list_Op5SuffixEx;
    m_flag_Op5SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp5SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op5SuffixEx.push_back(node);
    }
    return m_list_Op5SuffixEx;
}

