#include "ALittleScriptOp3StatElement.h"

#include "ALittleScriptOp3SuffixElement.h"
#include "ALittleScriptOp3SuffixExElement.h"

std::shared_ptr<ALittleScriptOp3SuffixElement> ALittleScriptOp3StatElement::GetOp3Suffix()
{
    if (m_flag_Op3Suffix) return m_cache_Op3Suffix;
    m_flag_Op3Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp3SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op3Suffix = node;
            break;
        }
    }
    return m_cache_Op3Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp3SuffixExElement>>& ALittleScriptOp3StatElement::GetOp3SuffixExList()
{
    if (m_flag_Op3SuffixEx) return m_list_Op3SuffixEx;
    m_flag_Op3SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp3SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op3SuffixEx.push_back(node);
    }
    return m_list_Op3SuffixEx;
}

