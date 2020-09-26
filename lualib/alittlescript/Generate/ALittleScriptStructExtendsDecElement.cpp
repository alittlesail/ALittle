#include "ALittleScriptStructExtendsDecElement.h"

#include "ALittleScriptNamespaceNameDecElement.h"
#include "ALittleScriptStructNameDecElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptNamespaceNameDecElement> ALittleScriptStructExtendsDecElement::GetNamespaceNameDec()
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
std::shared_ptr<ALittleScriptStructNameDecElement> ALittleScriptStructExtendsDecElement::GetStructNameDec()
{
    if (m_flag_StructNameDec) return m_cache_StructNameDec;
    m_flag_StructNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_StructNameDec = node;
            break;
        }
    }
    return m_cache_StructNameDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptStructExtendsDecElement::GetStringList()
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

