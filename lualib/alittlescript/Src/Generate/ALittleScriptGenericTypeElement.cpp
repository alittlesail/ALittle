#include "ALittleScriptGenericTypeElement.h"

#include "ALittleScriptGenericListTypeElement.h"
#include "ALittleScriptGenericMapTypeElement.h"
#include "ALittleScriptGenericFunctorTypeElement.h"

std::shared_ptr<ALittleScriptGenericListTypeElement> ALittleScriptGenericTypeElement::GetGenericListType()
{
    if (m_flag_GenericListType) return m_cache_GenericListType;
    m_flag_GenericListType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericListTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericListType = node;
            break;
        }
    }
    return m_cache_GenericListType;
}
std::shared_ptr<ALittleScriptGenericMapTypeElement> ALittleScriptGenericTypeElement::GetGenericMapType()
{
    if (m_flag_GenericMapType) return m_cache_GenericMapType;
    m_flag_GenericMapType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericMapTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericMapType = node;
            break;
        }
    }
    return m_cache_GenericMapType;
}
std::shared_ptr<ALittleScriptGenericFunctorTypeElement> ALittleScriptGenericTypeElement::GetGenericFunctorType()
{
    if (m_flag_GenericFunctorType) return m_cache_GenericFunctorType;
    m_flag_GenericFunctorType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericFunctorType = node;
            break;
        }
    }
    return m_cache_GenericFunctorType;
}

