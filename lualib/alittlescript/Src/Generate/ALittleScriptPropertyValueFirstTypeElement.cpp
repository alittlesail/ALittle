#include "ALittleScriptPropertyValueFirstTypeElement.h"

#include "ALittleScriptPropertyValueThisTypeElement.h"
#include "ALittleScriptPropertyValueCustomTypeElement.h"
#include "ALittleScriptPropertyValueCastTypeElement.h"

std::shared_ptr<ALittleScriptPropertyValueThisTypeElement> ALittleScriptPropertyValueFirstTypeElement::GetPropertyValueThisType()
{
    if (m_flag_PropertyValueThisType) return m_cache_PropertyValueThisType;
    m_flag_PropertyValueThisType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueThisTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueThisType = node;
            break;
        }
    }
    return m_cache_PropertyValueThisType;
}
std::shared_ptr<ALittleScriptPropertyValueCustomTypeElement> ALittleScriptPropertyValueFirstTypeElement::GetPropertyValueCustomType()
{
    if (m_flag_PropertyValueCustomType) return m_cache_PropertyValueCustomType;
    m_flag_PropertyValueCustomType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueCustomTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueCustomType = node;
            break;
        }
    }
    return m_cache_PropertyValueCustomType;
}
std::shared_ptr<ALittleScriptPropertyValueCastTypeElement> ALittleScriptPropertyValueFirstTypeElement::GetPropertyValueCastType()
{
    if (m_flag_PropertyValueCastType) return m_cache_PropertyValueCastType;
    m_flag_PropertyValueCastType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueCastTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueCastType = node;
            break;
        }
    }
    return m_cache_PropertyValueCastType;
}

