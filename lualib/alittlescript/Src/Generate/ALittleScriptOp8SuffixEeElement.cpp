#include "ALittleScriptOp8SuffixEeElement.h"

#include "ALittleScriptOp3SuffixElement.h"
#include "ALittleScriptOp4SuffixElement.h"
#include "ALittleScriptOp5SuffixElement.h"
#include "ALittleScriptOp6SuffixElement.h"
#include "ALittleScriptOp7SuffixElement.h"

std::shared_ptr<ALittleScriptOp3SuffixElement> ALittleScriptOp8SuffixEeElement::GetOp3Suffix()
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
std::shared_ptr<ALittleScriptOp4SuffixElement> ALittleScriptOp8SuffixEeElement::GetOp4Suffix()
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
std::shared_ptr<ALittleScriptOp5SuffixElement> ALittleScriptOp8SuffixEeElement::GetOp5Suffix()
{
    if (m_flag_Op5Suffix) return m_cache_Op5Suffix;
    m_flag_Op5Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp5SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op5Suffix = node;
            break;
        }
    }
    return m_cache_Op5Suffix;
}
std::shared_ptr<ALittleScriptOp6SuffixElement> ALittleScriptOp8SuffixEeElement::GetOp6Suffix()
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
std::shared_ptr<ALittleScriptOp7SuffixElement> ALittleScriptOp8SuffixEeElement::GetOp7Suffix()
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

