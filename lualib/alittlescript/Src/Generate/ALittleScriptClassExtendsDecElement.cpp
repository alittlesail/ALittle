#include "ALittleScriptClassExtendsDecElement.h"

#include "ALittleScriptNamespaceNameDecElement.h"
#include "ALittleScriptClassNameDecElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptNamespaceNameDecElement> ALittleScriptClassExtendsDecElement::GetNamespaceNameDec()
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
std::shared_ptr<ALittleScriptClassNameDecElement> ALittleScriptClassExtendsDecElement::GetClassNameDec()
{
    if (m_flag_ClassNameDec) return m_cache_ClassNameDec;
    m_flag_ClassNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassNameDec = node;
            break;
        }
    }
    return m_cache_ClassNameDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptClassExtendsDecElement::GetStringList()
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

