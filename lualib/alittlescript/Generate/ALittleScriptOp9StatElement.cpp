#include "ALittleScriptOp9StatElement.h"

#include "ALittleScriptOp9SuffixElement.h"
#include "ALittleScriptOp9SuffixExElement.h"

std::shared_ptr<ALittleScriptOp9SuffixElement> ALittleScriptOp9StatElement::GetOp9Suffix()
{
    if (m_flag_Op9Suffix) return m_cache_Op9Suffix;
    m_flag_Op9Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp9SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op9Suffix = node;
            break;
        }
    }
    return m_cache_Op9Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp9SuffixExElement>>& ALittleScriptOp9StatElement::GetOp9SuffixExList()
{
    if (m_flag_Op9SuffixEx) return m_list_Op9SuffixEx;
    m_flag_Op9SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp9SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op9SuffixEx.push_back(node);
    }
    return m_list_Op9SuffixEx;
}

