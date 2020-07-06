#include "ALittleScriptOpNewStatElement.h"

#include "ALittleScriptCustomTypeElement.h"
#include "ALittleScriptGenericTypeElement.h"
#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptCustomTypeElement> ALittleScriptOpNewStatElement::GetCustomType()
{
    if (m_flag_CustomType) return m_cache_CustomType;
    m_flag_CustomType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_CustomType = node;
            break;
        }
    }
    return m_cache_CustomType;
}
std::shared_ptr<ALittleScriptGenericTypeElement> ALittleScriptOpNewStatElement::GetGenericType()
{
    if (m_flag_GenericType) return m_cache_GenericType;
    m_flag_GenericType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericType = node;
            break;
        }
    }
    return m_cache_GenericType;
}
const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& ALittleScriptOpNewStatElement::GetValueStatList()
{
    if (m_flag_ValueStat) return m_list_ValueStat;
    m_flag_ValueStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
        if (node != nullptr)
            m_list_ValueStat.push_back(node);
    }
    return m_list_ValueStat;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptOpNewStatElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptOpNewStatElement::GetStringList()
{
    if (m_flag_String) return m_list_String;
    m_flag_String = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
        if (node != nullptr)
            m_list_String.push_back(node);
    }
    return m_list_String;
}

