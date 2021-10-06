#include "ALittleScriptOp11SuffixExElement.h"

#include "ALittleScriptOp11SuffixElement.h"
#include "ALittleScriptOp12SuffixElement.h"

std::shared_ptr<ALittleScriptOp11SuffixElement> ALittleScriptOp11SuffixExElement::GetOp11Suffix()
{
    if (m_flag_Op11Suffix) return m_cache_Op11Suffix;
    m_flag_Op11Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp11SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op11Suffix = node;
            break;
        }
    }
    return m_cache_Op11Suffix;
}
std::shared_ptr<ALittleScriptOp12SuffixElement> ALittleScriptOp11SuffixExElement::GetOp12Suffix()
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

