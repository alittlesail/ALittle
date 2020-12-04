#include "ALittleScriptOp12SuffixExElement.h"

#include "ALittleScriptOp12SuffixElement.h"

std::shared_ptr<ALittleScriptOp12SuffixElement> ALittleScriptOp12SuffixExElement::GetOp12Suffix()
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
