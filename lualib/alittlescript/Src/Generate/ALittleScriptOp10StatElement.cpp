#include "ALittleScriptOp10StatElement.h"

#include "ALittleScriptOp10SuffixElement.h"
#include "ALittleScriptOp10SuffixExElement.h"

std::shared_ptr<ALittleScriptOp10SuffixElement> ALittleScriptOp10StatElement::GetOp10Suffix()
{
    if (m_flag_Op10Suffix) return m_cache_Op10Suffix;
    m_flag_Op10Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp10SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op10Suffix = node;
            break;
        }
    }
    return m_cache_Op10Suffix;
}
const std::vector<std::shared_ptr<ALittleScriptOp10SuffixExElement>>& ALittleScriptOp10StatElement::GetOp10SuffixExList()
{
    if (m_flag_Op10SuffixEx) return m_list_Op10SuffixEx;
    m_flag_Op10SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp10SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op10SuffixEx.push_back(node);
    }
    return m_list_Op10SuffixEx;
}

