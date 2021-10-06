#include "ALittleScriptOp11SuffixEeElement.h"

#include "ALittleScriptOp10SuffixElement.h"
#include "ALittleScriptOp3SuffixElement.h"
#include "ALittleScriptOp4SuffixElement.h"
#include "ALittleScriptOp5SuffixElement.h"
#include "ALittleScriptOp6SuffixElement.h"
#include "ALittleScriptOp7SuffixElement.h"
#include "ALittleScriptOp8SuffixElement.h"
#include "ALittleScriptOp9SuffixElement.h"

std::shared_ptr<ALittleScriptOp10SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp10Suffix()
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
std::shared_ptr<ALittleScriptOp3SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp3Suffix()
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
std::shared_ptr<ALittleScriptOp4SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp4Suffix()
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
std::shared_ptr<ALittleScriptOp5SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp5Suffix()
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
std::shared_ptr<ALittleScriptOp6SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp6Suffix()
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
std::shared_ptr<ALittleScriptOp7SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp7Suffix()
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
std::shared_ptr<ALittleScriptOp8SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp8Suffix()
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
std::shared_ptr<ALittleScriptOp9SuffixElement> ALittleScriptOp11SuffixEeElement::GetOp9Suffix()
{
    if (m_flag_Op9Suffix) return m_cache_Op9Suffix;
    m_flag_Op9Suffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp9SuffixElement>(child);
        if (node != nullptr)
        {
            m_cache_Op9Suffix = node;
            break;
        }
    }
    return m_cache_Op9Suffix;
}

