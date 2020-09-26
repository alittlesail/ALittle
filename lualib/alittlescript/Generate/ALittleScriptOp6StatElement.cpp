#include "ALittleScriptOp6StatElement.h"

#include "ALittleScriptOp6SuffixElement.h"
#include "ALittleScriptOp6SuffixExElement.h"

std::shared_ptr<ALittleScriptOp6SuffixElement> ALittleScriptOp6StatElement::GetOp6Suffix()
{
    if (m_flag_Op6Suffix) return m_cache_Op6Suffix;
    m_flag_Op6Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp6SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op6Suffix = node;
            break;
        }
    }
    return m_cache_Op6Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp6SuffixExElement>>& ALittleScriptOp6StatElement::GetOp6SuffixExList()
{
    if (m_flag_Op6SuffixEx) return m_list_Op6SuffixEx;
    m_flag_Op6SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp6SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op6SuffixEx.push_back(node);
    }
    return m_list_Op6SuffixEx;
}

