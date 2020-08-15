#include "ALittleScriptOp7StatElement.h"

#include "ALittleScriptOp7SuffixElement.h"
#include "ALittleScriptOp7SuffixExElement.h"

std::shared_ptr<ALittleScriptOp7SuffixElement> ALittleScriptOp7StatElement::GetOp7Suffix()
{
    if (m_flag_Op7Suffix) return m_cache_Op7Suffix;
    m_flag_Op7Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp7SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op7Suffix = node;
            break;
        }
    }
    return m_cache_Op7Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp7SuffixExElement>>& ALittleScriptOp7StatElement::GetOp7SuffixExList()
{
    if (m_flag_Op7SuffixEx) return m_list_Op7SuffixEx;
    m_flag_Op7SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp7SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op7SuffixEx.push_back(node);
    }
    return m_list_Op7SuffixEx;
}

