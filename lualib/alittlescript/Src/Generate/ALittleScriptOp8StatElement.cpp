#include "ALittleScriptOp8StatElement.h"

#include "ALittleScriptOp8SuffixElement.h"
#include "ALittleScriptOp8SuffixExElement.h"

std::shared_ptr<ALittleScriptOp8SuffixElement> ALittleScriptOp8StatElement::GetOp8Suffix()
{
    if (m_flag_Op8Suffix) return m_cache_Op8Suffix;
    m_flag_Op8Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp8SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op8Suffix = node;
            break;
        }
    }
    return m_cache_Op8Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp8SuffixExElement>>& ALittleScriptOp8StatElement::GetOp8SuffixExList()
{
    if (m_flag_Op8SuffixEx) return m_list_Op8SuffixEx;
    m_flag_Op8SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp8SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op8SuffixEx.push_back(node);
    }
    return m_list_Op8SuffixEx;
}

