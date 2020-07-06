#include "ALittleScriptPropertyValueSuffixElement.h"

#include "ALittleScriptPropertyValueDotIdElement.h"
#include "ALittleScriptPropertyValueMethodCallElement.h"
#include "ALittleScriptPropertyValueBracketValueElement.h"

std::shared_ptr<ALittleScriptPropertyValueDotIdElement> ALittleScriptPropertyValueSuffixElement::GetPropertyValueDotId()
{
    if (m_flag_PropertyValueDotId) return m_cache_PropertyValueDotId;
    m_flag_PropertyValueDotId = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueDotIdElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueDotId = node;
            break;
        }
    }
    return m_cache_PropertyValueDotId;
}
std::shared_ptr<ALittleScriptPropertyValueMethodCallElement> ALittleScriptPropertyValueSuffixElement::GetPropertyValueMethodCall()
{
    if (m_flag_PropertyValueMethodCall) return m_cache_PropertyValueMethodCall;
    m_flag_PropertyValueMethodCall = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueMethodCall = node;
            break;
        }
    }
    return m_cache_PropertyValueMethodCall;
}
std::shared_ptr<ALittleScriptPropertyValueBracketValueElement> ALittleScriptPropertyValueSuffixElement::GetPropertyValueBracketValue()
{
    if (m_flag_PropertyValueBracketValue) return m_cache_PropertyValueBracketValue;
    m_flag_PropertyValueBracketValue = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueBracketValueElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueBracketValue = node;
            break;
        }
    }
    return m_cache_PropertyValueBracketValue;
}

