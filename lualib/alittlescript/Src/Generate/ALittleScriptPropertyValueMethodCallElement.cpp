#include "ALittleScriptPropertyValueMethodCallElement.h"

#include "ALittleScriptPropertyValueMethodTemplateElement.h"
#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptPropertyValueMethodTemplateElement> ALittleScriptPropertyValueMethodCallElement::GetPropertyValueMethodTemplate()
{
    if (m_flag_PropertyValueMethodTemplate) return m_cache_PropertyValueMethodTemplate;
    m_flag_PropertyValueMethodTemplate = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodTemplateElement>(child);
        if (node != nullptr)
        {
            m_cache_PropertyValueMethodTemplate = node;
            break;
        }
    }
    return m_cache_PropertyValueMethodTemplate;
}
const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& ALittleScriptPropertyValueMethodCallElement::GetValueStatList()
{
    if (m_flag_ValueStat) return m_list_ValueStat;
    m_flag_ValueStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
        if (node != nullptr)
            m_list_ValueStat.push_back(node);
    }
    return m_list_ValueStat;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptPropertyValueMethodCallElement::GetStringList()
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

