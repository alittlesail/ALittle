#include "ALittleScriptClassDecElement.h"

#include "ALittleScriptClassExtendsDecElement.h"
#include "ALittleScriptClassNameDecElement.h"
#include "ALittleScriptTemplateDecElement.h"
#include "ALittleScriptClassBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptClassExtendsDecElement> ALittleScriptClassDecElement::GetClassExtendsDec()
{
    if (m_flag_ClassExtendsDec) return m_cache_ClassExtendsDec;
    m_flag_ClassExtendsDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassExtendsDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassExtendsDec = node;
            break;
        }
    }
    return m_cache_ClassExtendsDec;
}
std::shared_ptr<ALittleScriptClassNameDecElement> ALittleScriptClassDecElement::GetClassNameDec()
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
std::shared_ptr<ALittleScriptTemplateDecElement> ALittleScriptClassDecElement::GetTemplateDec()
{
    if (m_flag_TemplateDec) return m_cache_TemplateDec;
    m_flag_TemplateDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTemplateDecElement>(child);
        if (node != nullptr)
        {
            m_cache_TemplateDec = node;
            break;
        }
    }
    return m_cache_TemplateDec;
}
std::shared_ptr<ALittleScriptClassBodyDecElement> ALittleScriptClassDecElement::GetClassBodyDec()
{
    if (m_flag_ClassBodyDec) return m_cache_ClassBodyDec;
    m_flag_ClassBodyDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassBodyDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassBodyDec = node;
            break;
        }
    }
    return m_cache_ClassBodyDec;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptClassDecElement::GetKey()
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

