#include "ALittleScriptClassGetterDecElement.h"

#include "ALittleScriptMethodNameDecElement.h"
#include "ALittleScriptMethodGetterParamDecElement.h"
#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptMethodBodyDecElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptMethodNameDecElement> ALittleScriptClassGetterDecElement::GetMethodNameDec()
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
std::shared_ptr<ALittleScriptMethodGetterParamDecElement> ALittleScriptClassGetterDecElement::GetMethodGetterParamDec()
{
    if (m_flag_MethodGetterParamDec) return m_cache_MethodGetterParamDec;
    m_flag_MethodGetterParamDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodGetterParamDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodGetterParamDec = node;
            break;
        }
    }
    return m_cache_MethodGetterParamDec;
}
std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptClassGetterDecElement::GetAllType()
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
std::shared_ptr<ALittleScriptMethodBodyDecElement> ALittleScriptClassGetterDecElement::GetMethodBodyDec()
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
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptClassGetterDecElement::GetKey()
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
std::shared_ptr<ALittleScriptStringElement> ALittleScriptClassGetterDecElement::GetString()
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

