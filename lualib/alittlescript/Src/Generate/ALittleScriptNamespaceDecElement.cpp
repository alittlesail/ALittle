#include "ALittleScriptNamespaceDecElement.h"

#include "ALittleScriptModifierElement.h"
#include "ALittleScriptNamespaceElementDecElement.h"
#include "ALittleScriptNamespaceNameDecElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& ALittleScriptNamespaceDecElement::GetModifierList()
{
    if (m_flag_Modifier) return m_list_Modifier;
    m_flag_Modifier = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptModifierElement>(child);
        if (node != nullptr)
            m_list_Modifier.push_back(node);
    }
    return m_list_Modifier;
}
const std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>>& ALittleScriptNamespaceDecElement::GetNamespaceElementDecList()
{
    if (m_flag_NamespaceElementDec) return m_list_NamespaceElementDec;
    m_flag_NamespaceElementDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(child);
        if (node != nullptr)
            m_list_NamespaceElementDec.push_back(node);
    }
    return m_list_NamespaceElementDec;
}
std::shared_ptr<ALittleScriptNamespaceNameDecElement> ALittleScriptNamespaceDecElement::GetNamespaceNameDec()
{
    if (m_flag_NamespaceNameDec) return m_cache_NamespaceNameDec;
    m_flag_NamespaceNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptNamespaceNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_NamespaceNameDec = node;
            break;
        }
    }
    return m_cache_NamespaceNameDec;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptNamespaceDecElement::GetKey()
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
std::shared_ptr<ALittleScriptStringElement> ALittleScriptNamespaceDecElement::GetString()
{
    if (m_flag_String) return m_cache_String;
    m_flag_String = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
        if (node != nullptr)
        {
            m_cache_String = node;
            break;
        }
    }
    return m_cache_String;
}

