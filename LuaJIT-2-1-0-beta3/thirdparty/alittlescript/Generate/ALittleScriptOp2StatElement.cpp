#include "ALittleScriptOp2StatElement.h"

#include "ALittleScriptOp2ValueElement.h"
#include "ALittleScriptOp2SuffixExElement.h"

std::shared_ptr<ALittleScriptOp2ValueElement> ALittleScriptOp2StatElement::GetOp2Value()
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
const std::vector<std::shared_ptr<ALittleScriptOp2SuffixExElement>>& ALittleScriptOp2StatElement::GetOp2SuffixExList()
{
    if (m_flag_Op2SuffixEx) return m_list_Op2SuffixEx;
    m_flag_Op2SuffixEx = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp2SuffixExElement>(child);
        if (node != nullptr)
            m_list_Op2SuffixEx.push_back(node);
    }
    return m_list_Op2SuffixEx;
}

