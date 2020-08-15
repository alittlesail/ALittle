#include "ALittleScriptOp4StatElement.h"

#include "ALittleScriptOp4SuffixElement.h"
#include "ALittleScriptOp4SuffixExElement.h"

std::shared_ptr<ALittleScriptOp4SuffixElement> ALittleScriptOp4StatElement::GetOp4Suffix()
{
    if (m_flag_Op4Suffix) return m_cache_Op4Suffix;
    m_flag_Op4Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp4SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op4Suffix = node;
            break;
        }
    }
    return m_cache_Op4Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp4SuffixExElement>>& ALittleScriptOp4StatElement::GetOp4SuffixExList()
{
    if (m_flag_Op4SuffixEx) return m_list_Op4SuffixEx;
    m_flag_Op4SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp4SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op4SuffixEx.push_back(node);
    }
    return m_list_Op4SuffixEx;
}

