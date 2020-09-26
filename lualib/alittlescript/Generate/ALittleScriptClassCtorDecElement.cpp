#include "ALittleScriptClassCtorDecElement.h"

#include "ALittleScriptMethodParamDecElement.h"
#include "ALittleScriptMethodBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptMethodParamDecElement> ALittleScriptClassCtorDecElement::GetMethodParamDec()
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
std::shared_ptr<ALittleScriptMethodBodyDecElement> ALittleScriptClassCtorDecElement::GetMethodBodyDec()
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
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptClassCtorDecElement::GetKey()
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

