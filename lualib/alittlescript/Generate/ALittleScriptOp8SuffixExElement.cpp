#include "ALittleScriptOp8SuffixExElement.h"

#include "ALittleScriptOp8SuffixElement.h"

std::shared_ptr<ALittleScriptOp8SuffixElement> ALittleScriptOp8SuffixExElement::GetOp8Suffix()
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

