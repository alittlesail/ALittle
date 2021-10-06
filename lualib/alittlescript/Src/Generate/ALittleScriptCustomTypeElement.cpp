#include "ALittleScriptCustomTypeElement.h"

#include "ALittleScriptCustomTypeNameElement.h"
#include "ALittleScriptCustomTypeDotIdElement.h"
#include "ALittleScriptCustomTypeTemplateElement.h"

std::shared_ptr<ALittleScriptCustomTypeNameElement> ALittleScriptCustomTypeElement::GetCustomTypeName()
{
    if (m_flag_CustomTypeName) return m_cache_CustomTypeName;
    m_flag_CustomTypeName = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeNameElement>(child);
        if (node != nullptr)
        {
            m_cache_CustomTypeName = node;
            break;
        }
    }
    return m_cache_CustomTypeName;
}
std::shared_ptr<ALittleScriptCustomTypeDotIdElement> ALittleScriptCustomTypeElement::GetCustomTypeDotId()
{
    if (m_flag_CustomTypeDotId) return m_cache_CustomTypeDotId;
    m_flag_CustomTypeDotId = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeDotIdElement>(child);
        if (node != nullptr)
        {
            m_cache_CustomTypeDotId = node;
            break;
        }
    }
    return m_cache_CustomTypeDotId;
}
std::shared_ptr<ALittleScriptCustomTypeTemplateElement> ALittleScriptCustomTypeElement::GetCustomTypeTemplate()
{
    if (m_flag_CustomTypeTemplate) return m_cache_CustomTypeTemplate;
    m_flag_CustomTypeTemplate = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeTemplateElement>(child);
        if (node != nullptr)
        {
            m_cache_CustomTypeTemplate = node;
            break;
        }
    }
    return m_cache_CustomTypeTemplate;
}

