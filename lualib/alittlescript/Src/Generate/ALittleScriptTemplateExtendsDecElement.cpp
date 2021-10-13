#include "ALittleScriptTemplateExtendsDecElement.h"

#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptTemplateExtendsClassDecElement.h"
#include "ALittleScriptTemplateExtendsStructDecElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptTemplateExtendsDecElement::GetAllType()
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
std::shared_ptr<ALittleScriptTemplateExtendsClassDecElement> ALittleScriptTemplateExtendsDecElement::GetTemplateExtendsClassDec()
{
    if (m_flag_TemplateExtendsClassDec) return m_cache_TemplateExtendsClassDec;
    m_flag_TemplateExtendsClassDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTemplateExtendsClassDecElement>(child);
        if (node != nullptr)
        {
            m_cache_TemplateExtendsClassDec = node;
            break;
        }
    }
    return m_cache_TemplateExtendsClassDec;
}
std::shared_ptr<ALittleScriptTemplateExtendsStructDecElement> ALittleScriptTemplateExtendsDecElement::GetTemplateExtendsStructDec()
{
    if (m_flag_TemplateExtendsStructDec) return m_cache_TemplateExtendsStructDec;
    m_flag_TemplateExtendsStructDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTemplateExtendsStructDecElement>(child);
        if (node != nullptr)
        {
            m_cache_TemplateExtendsStructDec = node;
            break;
        }
    }
    return m_cache_TemplateExtendsStructDec;
}
std::shared_ptr<ALittleScriptStringElement> ALittleScriptTemplateExtendsDecElement::GetString()
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

