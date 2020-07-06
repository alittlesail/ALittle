#include "ALittleScriptNamespaceElementDecElement.h"

#include "ALittleScriptModifierElement.h"
#include "ALittleScriptEnumDecElement.h"
#include "ALittleScriptStructDecElement.h"
#include "ALittleScriptOpAssignExprElement.h"
#include "ALittleScriptGlobalMethodDecElement.h"
#include "ALittleScriptClassDecElement.h"
#include "ALittleScriptUsingDecElement.h"
#include "ALittleScriptInstanceDecElement.h"

const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& ALittleScriptNamespaceElementDecElement::GetModifierList()
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
std::shared_ptr<ALittleScriptEnumDecElement> ALittleScriptNamespaceElementDecElement::GetEnumDec()
{
    if (m_flag_EnumDec) return m_cache_EnumDec;
    m_flag_EnumDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(child);
        if (node != nullptr)
        {
            m_cache_EnumDec = node;
            break;
        }
    }
    return m_cache_EnumDec;
}
std::shared_ptr<ALittleScriptStructDecElement> ALittleScriptNamespaceElementDecElement::GetStructDec()
{
    if (m_flag_StructDec) return m_cache_StructDec;
    m_flag_StructDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructDecElement>(child);
        if (node != nullptr)
        {
            m_cache_StructDec = node;
            break;
        }
    }
    return m_cache_StructDec;
}
std::shared_ptr<ALittleScriptOpAssignExprElement> ALittleScriptNamespaceElementDecElement::GetOpAssignExpr()
{
    if (m_flag_OpAssignExpr) return m_cache_OpAssignExpr;
    m_flag_OpAssignExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOpAssignExprElement>(child);
        if (node != nullptr)
        {
            m_cache_OpAssignExpr = node;
            break;
        }
    }
    return m_cache_OpAssignExpr;
}
std::shared_ptr<ALittleScriptGlobalMethodDecElement> ALittleScriptNamespaceElementDecElement::GetGlobalMethodDec()
{
    if (m_flag_GlobalMethodDec) return m_cache_GlobalMethodDec;
    m_flag_GlobalMethodDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(child);
        if (node != nullptr)
        {
            m_cache_GlobalMethodDec = node;
            break;
        }
    }
    return m_cache_GlobalMethodDec;
}
std::shared_ptr<ALittleScriptClassDecElement> ALittleScriptNamespaceElementDecElement::GetClassDec()
{
    if (m_flag_ClassDec) return m_cache_ClassDec;
    m_flag_ClassDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassDec = node;
            break;
        }
    }
    return m_cache_ClassDec;
}
std::shared_ptr<ALittleScriptUsingDecElement> ALittleScriptNamespaceElementDecElement::GetUsingDec()
{
    if (m_flag_UsingDec) return m_cache_UsingDec;
    m_flag_UsingDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptUsingDecElement>(child);
        if (node != nullptr)
        {
            m_cache_UsingDec = node;
            break;
        }
    }
    return m_cache_UsingDec;
}
std::shared_ptr<ALittleScriptInstanceDecElement> ALittleScriptNamespaceElementDecElement::GetInstanceDec()
{
    if (m_flag_InstanceDec) return m_cache_InstanceDec;
    m_flag_InstanceDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptInstanceDecElement>(child);
        if (node != nullptr)
        {
            m_cache_InstanceDec = node;
            break;
        }
    }
    return m_cache_InstanceDec;
}

