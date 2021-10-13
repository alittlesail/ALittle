#include "ALittleScriptClassStaticDecElement.h"

#include "ALittleScriptTemplateDecElement.h"
#include "ALittleScriptMethodNameDecElement.h"
#include "ALittleScriptMethodParamDecElement.h"
#include "ALittleScriptMethodReturnDecElement.h"
#include "ALittleScriptMethodBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptTemplateDecElement> ALittleScriptClassStaticDecElement::GetTemplateDec()
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
std::shared_ptr<ALittleScriptMethodNameDecElement> ALittleScriptClassStaticDecElement::GetMethodNameDec()
{
    if (m_flag_MethodNameDec) return m_cache_MethodNameDec;
    m_flag_MethodNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodNameDec = node;
            break;
        }
    }
    return m_cache_MethodNameDec;
}
std::shared_ptr<ALittleScriptMethodParamDecElement> ALittleScriptClassStaticDecElement::GetMethodParamDec()
{
    if (m_flag_MethodParamDec) return m_cache_MethodParamDec;
    m_flag_MethodParamDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodParamDec = node;
            break;
        }
    }
    return m_cache_MethodParamDec;
}
std::shared_ptr<ALittleScriptMethodReturnDecElement> ALittleScriptClassStaticDecElement::GetMethodReturnDec()
{
    if (m_flag_MethodReturnDec) return m_cache_MethodReturnDec;
    m_flag_MethodReturnDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodReturnDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodReturnDec = node;
            break;
        }
    }
    return m_cache_MethodReturnDec;
}
std::shared_ptr<ALittleScriptMethodBodyDecElement> ALittleScriptClassStaticDecElement::GetMethodBodyDec()
{
    if (m_flag_MethodBodyDec) return m_cache_MethodBodyDec;
    m_flag_MethodBodyDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodBodyDec = node;
            break;
        }
    }
    return m_cache_MethodBodyDec;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptClassStaticDecElement::GetKey()
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

