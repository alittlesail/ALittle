#include "ALittleScriptAllTypeElement.h"

#include "ALittleScriptAllTypeConstElement.h"
#include "ALittleScriptPrimitiveTypeElement.h"
#include "ALittleScriptCustomTypeElement.h"
#include "ALittleScriptGenericTypeElement.h"

std::shared_ptr<ALittleScriptAllTypeConstElement> ALittleScriptAllTypeElement::GetAllTypeConst()
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
std::shared_ptr<ALittleScriptPrimitiveTypeElement> ALittleScriptAllTypeElement::GetPrimitiveType()
{
    if (m_flag_PrimitiveType) return m_cache_PrimitiveType;
    m_flag_PrimitiveType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPrimitiveTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_PrimitiveType = node;
            break;
        }
    }
    return m_cache_PrimitiveType;
}
std::shared_ptr<ALittleScriptCustomTypeElement> ALittleScriptAllTypeElement::GetCustomType()
{
    if (m_flag_CustomType) return m_cache_CustomType;
    m_flag_CustomType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_CustomType = node;
            break;
        }
    }
    return m_cache_CustomType;
}
std::shared_ptr<ALittleScriptGenericTypeElement> ALittleScriptAllTypeElement::GetGenericType()
{
    if (m_flag_GenericType) return m_cache_GenericType;
    m_flag_GenericType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptGenericTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_GenericType = node;
            break;
        }
    }
    return m_cache_GenericType;
}

