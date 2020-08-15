#include "ALittleScriptValueOpStatElement.h"

#include "ALittleScriptValueFactorStatElement.h"
#include "ALittleScriptOp5StatElement.h"
#include "ALittleScriptOp3StatElement.h"
#include "ALittleScriptOp4StatElement.h"
#include "ALittleScriptOp6StatElement.h"
#include "ALittleScriptOp7StatElement.h"
#include "ALittleScriptOp8StatElement.h"

std::shared_ptr<ALittleScriptValueFactorStatElement> ALittleScriptValueOpStatElement::GetValueFactorStat()
{
    if (m_flag_ValueFactorStat) return m_cache_ValueFactorStat;
    m_flag_ValueFactorStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueFactorStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ValueFactorStat = node;
            break;
        }
    }
    return m_cache_ValueFactorStat;
}
std::shared_ptr<ALittleScriptOp5StatElement> ALittleScriptValueOpStatElement::GetOp5Stat()
{
    if (m_flag_Op5Stat) return m_cache_Op5Stat;
    m_flag_Op5Stat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp5StatElement>(child);
        if (node != nullptr)
        {
            m_cache_Op5Stat = node;
            break;
        }
    }
    return m_cache_Op5Stat;
}
std::shared_ptr<ALittleScriptOp3StatElement> ALittleScriptValueOpStatElement::GetOp3Stat()
{
    if (m_flag_Op3Stat) return m_cache_Op3Stat;
    m_flag_Op3Stat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp3StatElement>(child);
        if (node != nullptr)
        {
            m_cache_Op3Stat = node;
            break;
        }
    }
    return m_cache_Op3Stat;
}
std::shared_ptr<ALittleScriptOp4StatElement> ALittleScriptValueOpStatElement::GetOp4Stat()
{
    if (m_flag_Op4Stat) return m_cache_Op4Stat;
    m_flag_Op4Stat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp4StatElement>(child);
        if (node != nullptr)
        {
            m_cache_Op4Stat = node;
            break;
        }
    }
    return m_cache_Op4Stat;
}
std::shared_ptr<ALittleScriptOp6StatElement> ALittleScriptValueOpStatElement::GetOp6Stat()
{
    if (m_flag_Op6Stat) return m_cache_Op6Stat;
    m_flag_Op6Stat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp6StatElement>(child);
        if (node != nullptr)
        {
            m_cache_Op6Stat = node;
            break;
        }
    }
    return m_cache_Op6Stat;
}
std::shared_ptr<ALittleScriptOp7StatElement> ALittleScriptValueOpStatElement::GetOp7Stat()
{
    if (m_flag_Op7Stat) return m_cache_Op7Stat;
    m_flag_Op7Stat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp7StatElement>(child);
        if (node != nullptr)
        {
            m_cache_Op7Stat = node;
            break;
        }
    }
    return m_cache_Op7Stat;
}
std::shared_ptr<ALittleScriptOp8StatElement> ALittleScriptValueOpStatElement::GetOp8Stat()
{
    if (m_flag_Op8Stat) return m_cache_Op8Stat;
    m_flag_Op8Stat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp8StatElement>(child);
        if (node != nullptr)
        {
            m_cache_Op8Stat = node;
            break;
        }
    }
    return m_cache_Op8Stat;
}

