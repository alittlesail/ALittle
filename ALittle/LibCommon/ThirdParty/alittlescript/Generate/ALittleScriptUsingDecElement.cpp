#include "ALittleScriptUsingDecElement.h"

#include "ALittleScriptUsingNameDecElement.h"
#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptUsingNameDecElement> ALittleScriptUsingDecElement::GetUsingNameDec()
{
    if (m_flag_UsingNameDec) return m_cache_UsingNameDec;
    m_flag_UsingNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptUsingNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_UsingNameDec = node;
            break;
        }
    }
    return m_cache_UsingNameDec;
}
std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptUsingDecElement::GetAllType()
{
    if (m_flag_AllType) return m_cache_AllType;
    m_flag_AllType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_AllType = node;
            break;
        }
    }
    return m_cache_AllType;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptUsingDecElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptUsingDecElement::GetStringList()
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

