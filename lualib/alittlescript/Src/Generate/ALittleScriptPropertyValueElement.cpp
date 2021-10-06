#include "ALittleScriptPropertyValueElement.h"

#include "ALittleScriptPropertyValueFirstTypeElement.h"
#include "ALittleScriptPropertyValueSuffixElement.h"

std::shared_ptr<ALittleScriptPropertyValueFirstTypeElement> ALittleScriptPropertyValueElement::GetPropertyValueFirstType()
{
    if (m_flag_PropertyValueFirstType) return m_cache_PropertyValueFirstType;
    m_flag_PropertyValueFirstType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueFirstTypeElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueFirstType = node;
            break;
        }
    }
    return m_cache_PropertyValueFirstType;
}
const std::vector<std::shared_ptr<ALittleScriptPropertyValueSuffixElement>>& ALittleScriptPropertyValueElement::GetPropertyValueSuffixList()
{
    if (m_flag_PropertyValueSuffix) return m_list_PropertyValueSuffix;
    m_flag_PropertyValueSuffix = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(child);
        if (node != nullptr)
            m_list_PropertyValueSuffix.push_back(node);
    }
    return m_list_PropertyValueSuffix;
}

