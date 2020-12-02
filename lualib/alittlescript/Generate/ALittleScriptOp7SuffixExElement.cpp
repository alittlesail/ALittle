#include "ALittleScriptOp7SuffixExElement.h"

#include "ALittleScriptOp7SuffixElement.h"
#include "ALittleScriptOp8SuffixElement.h"
#include "ALittleScriptOp12SuffixElement.h"
#include "ALittleScriptOp9SuffixElement.h"
#include "ALittleScriptOp10SuffixElement.h"
#include "ALittleScriptOp11SuffixElement.h"

std::shared_ptr<ALittleScriptOp7SuffixElement> ALittleScriptOp7SuffixExElement::GetOp7Suffix()
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
std::shared_ptr<ALittleScriptOp8SuffixElement> ALittleScriptOp7SuffixExElement::GetOp8Suffix()
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
std::shared_ptr<ALittleScriptOp12SuffixElement> ALittleScriptOp7SuffixExElement::GetOp12Suffix()
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
std::shared_ptr<ALittleScriptOp9SuffixElement> ALittleScriptOp7SuffixExElement::GetOp9Suffix()
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
std::shared_ptr<ALittleScriptOp10SuffixElement> ALittleScriptOp7SuffixExElement::GetOp10Suffix()
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
std::shared_ptr<ALittleScriptOp11SuffixElement> ALittleScriptOp7SuffixExElement::GetOp11Suffix()
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

