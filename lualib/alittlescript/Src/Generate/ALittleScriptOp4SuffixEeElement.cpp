#include "ALittleScriptOp4SuffixEeElement.h"

#include "ALittleScriptOp3SuffixElement.h"

std::shared_ptr<ALittleScriptOp3SuffixElement> ALittleScriptOp4SuffixEeElement::GetOp3Suffix()
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

