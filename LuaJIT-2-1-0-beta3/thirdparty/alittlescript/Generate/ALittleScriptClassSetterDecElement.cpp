#include "ALittleScriptClassSetterDecElement.h"

#include "ALittleScriptMethodNameDecElement.h"
#include "ALittleScriptMethodSetterParamDecElement.h"
#include "ALittleScriptMethodBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptMethodNameDecElement> ALittleScriptClassSetterDecElement::GetMethodNameDec()
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
std::shared_ptr<ALittleScriptMethodSetterParamDecElement> ALittleScriptClassSetterDecElement::GetMethodSetterParamDec()
{
    if (m_flag_MethodSetterParamDec) return m_cache_MethodSetterParamDec;
    m_flag_MethodSetterParamDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodSetterParamDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodSetterParamDec = node;
            break;
        }
    }
    return m_cache_MethodSetterParamDec;
}
std::shared_ptr<ALittleScriptMethodBodyDecElement> ALittleScriptClassSetterDecElement::GetMethodBodyDec()
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
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptClassSetterDecElement::GetKey()
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

