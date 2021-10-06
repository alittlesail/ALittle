#include "ALittleScriptReflectValueElement.h"

#include "ALittleScriptReflectCustomTypeElement.h"
#include "ALittleScriptReflectValueStatElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptReflectCustomTypeElement> ALittleScriptReflectValueElement::GetReflectCustomType()
{
    if (m_flag_ReflectCustomType) return m_cache_ReflectCustomType;
    m_flag_ReflectCustomType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptReflectCustomTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_ReflectCustomType = node;
            break;
        }
    }
    return m_cache_ReflectCustomType;
}
std::shared_ptr<ALittleScriptReflectValueStatElement> ALittleScriptReflectValueElement::GetReflectValueStat()
{
    if (m_flag_ReflectValueStat) return m_cache_ReflectValueStat;
    m_flag_ReflectValueStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptReflectValueStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ReflectValueStat = node;
            break;
        }
    }
    return m_cache_ReflectValueStat;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptReflectValueElement::GetKey()
{
    if (m_flag_Key) return m_cache_Key;
    m_flag_Key = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptKeyElement>(child);
        if (node != nullptr)
        {
            m_cache_Key = node;
            break;
        }
    }
    return m_cache_Key;
}

