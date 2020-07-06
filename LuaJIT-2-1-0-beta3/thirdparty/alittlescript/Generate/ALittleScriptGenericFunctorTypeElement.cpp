#include "ALittleScriptGenericFunctorTypeElement.h"

#include "ALittleScriptAllTypeConstElement.h"
#include "ALittleScriptGenericFunctorReturnTypeElement.h"
#include "ALittleScriptCoroutineModifierElement.h"
#include "ALittleScriptGenericFunctorParamTypeElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptAllTypeConstElement> ALittleScriptGenericFunctorTypeElement::GetAllTypeConst()
{
    if (m_flag_AllTypeConst) return m_cache_AllTypeConst;
    m_flag_AllTypeConst = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeConstElement>(child);
        if (node != nullptr)
        {
            m_cache_AllTypeConst = node;
            break;
        }
    }
    return m_cache_AllTypeConst;
}
std::shared_ptr<ALittleScriptGenericFunctorReturnTypeElement> ALittleScriptGenericFunctorTypeElement::GetGenericFunctorReturnType()
{
    if (m_flag_GenericFunctorReturnType) return m_cache_GenericFunctorReturnType;
    m_flag_GenericFunctorReturnType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorReturnTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericFunctorReturnType = node;
            break;
        }
    }
    return m_cache_GenericFunctorReturnType;
}
std::shared_ptr<ALittleScriptCoroutineModifierElement> ALittleScriptGenericFunctorTypeElement::GetCoroutineModifier()
{
    if (m_flag_CoroutineModifier) return m_cache_CoroutineModifier;
    m_flag_CoroutineModifier = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCoroutineModifierElement>(child);
        if (node != nullptr)
        {
            m_cache_CoroutineModifier = node;
            break;
        }
    }
    return m_cache_CoroutineModifier;
}
std::shared_ptr<ALittleScriptGenericFunctorParamTypeElement> ALittleScriptGenericFunctorTypeElement::GetGenericFunctorParamType()
{
    if (m_flag_GenericFunctorParamType) return m_cache_GenericFunctorParamType;
    m_flag_GenericFunctorParamType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorParamTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericFunctorParamType = node;
            break;
        }
    }
    return m_cache_GenericFunctorParamType;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptGenericFunctorTypeElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptGenericFunctorTypeElement::GetStringList()
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

