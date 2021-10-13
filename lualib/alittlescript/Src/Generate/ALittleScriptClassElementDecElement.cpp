#include "ALittleScriptClassElementDecElement.h"

#include "ALittleScriptModifierElement.h"
#include "ALittleScriptClassSetterDecElement.h"
#include "ALittleScriptClassCtorDecElement.h"
#include "ALittleScriptClassStaticDecElement.h"
#include "ALittleScriptClassGetterDecElement.h"
#include "ALittleScriptClassVarDecElement.h"
#include "ALittleScriptClassMethodDecElement.h"

const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& ALittleScriptClassElementDecElement::GetModifierList()
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
std::shared_ptr<ALittleScriptClassSetterDecElement> ALittleScriptClassElementDecElement::GetClassSetterDec()
{
    if (m_flag_ClassSetterDec) return m_cache_ClassSetterDec;
    m_flag_ClassSetterDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassSetterDec = node;
            break;
        }
    }
    return m_cache_ClassSetterDec;
}
std::shared_ptr<ALittleScriptClassCtorDecElement> ALittleScriptClassElementDecElement::GetClassCtorDec()
{
    if (m_flag_ClassCtorDec) return m_cache_ClassCtorDec;
    m_flag_ClassCtorDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassCtorDec = node;
            break;
        }
    }
    return m_cache_ClassCtorDec;
}
std::shared_ptr<ALittleScriptClassStaticDecElement> ALittleScriptClassElementDecElement::GetClassStaticDec()
{
    if (m_flag_ClassStaticDec) return m_cache_ClassStaticDec;
    m_flag_ClassStaticDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassStaticDec = node;
            break;
        }
    }
    return m_cache_ClassStaticDec;
}
std::shared_ptr<ALittleScriptClassGetterDecElement> ALittleScriptClassElementDecElement::GetClassGetterDec()
{
    if (m_flag_ClassGetterDec) return m_cache_ClassGetterDec;
    m_flag_ClassGetterDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassGetterDec = node;
            break;
        }
    }
    return m_cache_ClassGetterDec;
}
std::shared_ptr<ALittleScriptClassVarDecElement> ALittleScriptClassElementDecElement::GetClassVarDec()
{
    if (m_flag_ClassVarDec) return m_cache_ClassVarDec;
    m_flag_ClassVarDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassVarDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassVarDec = node;
            break;
        }
    }
    return m_cache_ClassVarDec;
}
std::shared_ptr<ALittleScriptClassMethodDecElement> ALittleScriptClassElementDecElement::GetClassMethodDec()
{
    if (m_flag_ClassMethodDec) return m_cache_ClassMethodDec;
    m_flag_ClassMethodDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassMethodDec = node;
            break;
        }
    }
    return m_cache_ClassMethodDec;
}

