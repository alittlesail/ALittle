#include "ALittleScriptOp5SuffixEeElement.h"

#include "ALittleScriptOp3SuffixElement.h"
#include "ALittleScriptOp4SuffixElement.h"

std::shared_ptr<ALittleScriptOp3SuffixElement> ALittleScriptOp5SuffixEeElement::GetOp3Suffix()
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
std::shared_ptr<ALittleScriptOp4SuffixElement> ALittleScriptOp5SuffixEeElement::GetOp4Suffix()
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

