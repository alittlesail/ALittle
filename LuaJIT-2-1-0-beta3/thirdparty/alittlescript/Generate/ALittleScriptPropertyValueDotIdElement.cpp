#include "ALittleScriptPropertyValueDotIdElement.h"

#include "ALittleScriptPropertyValueDotIdNameElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptPropertyValueDotIdNameElement> ALittleScriptPropertyValueDotIdElement::GetPropertyValueDotIdName()
{
    if (m_flag_PropertyValueDotIdName) return m_cache_PropertyValueDotIdName;
    m_flag_PropertyValueDotIdName = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueDotIdNameElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueDotIdName = node;
            break;
        }
    }
    return m_cache_PropertyValueDotIdName;
}
std::shared_ptr<ALittleScriptStringElement> ALittleScriptPropertyValueDotIdElement::GetString()
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

