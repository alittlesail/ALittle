#include "ALittleScriptCustomTypeDotIdElement.h"

#include "ALittleScriptCustomTypeDotIdNameElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptCustomTypeDotIdNameElement> ALittleScriptCustomTypeDotIdElement::GetCustomTypeDotIdName()
{
    if (m_flag_CustomTypeDotIdName) return m_cache_CustomTypeDotIdName;
    m_flag_CustomTypeDotIdName = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeDotIdNameElement>(child);
        if (node != nullptr)
        {
            m_cache_CustomTypeDotIdName = node;
            break;
        }
    }
    return m_cache_CustomTypeDotIdName;
}
std::shared_ptr<ALittleScriptStringElement> ALittleScriptCustomTypeDotIdElement::GetString()
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

