#include "ALittleScriptOp6SuffixExElement.h"

#include "ALittleScriptOp6SuffixElement.h"
#include "ALittleScriptOp7SuffixElement.h"
#include "ALittleScriptOp8SuffixElement.h"

std::shared_ptr<ALittleScriptOp6SuffixElement> ALittleScriptOp6SuffixExElement::GetOp6Suffix()
{
    if (m_flag_Op6Suffix) return m_cache_Op6Suffix;
    m_flag_Op6Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp6SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op6Suffix = node;
            break;
        }
    }
    return m_cache_Op6Suffix;
}
std::shared_ptr<ALittleScriptOp7SuffixElement> ALittleScriptOp6SuffixExElement::GetOp7Suffix()
{
    if (m_flag_Op7Suffix) return m_cache_Op7Suffix;
    m_flag_Op7Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp7SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op7Suffix = node;
            break;
        }
    }
    return m_cache_Op7Suffix;
}
std::shared_ptr<ALittleScriptOp8SuffixElement> ALittleScriptOp6SuffixExElement::GetOp8Suffix()
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

