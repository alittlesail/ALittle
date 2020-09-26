#include "ALittleScriptReflectCustomTypeElement.h"

#include "ALittleScriptCustomTypeElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptCustomTypeElement> ALittleScriptReflectCustomTypeElement::GetCustomType()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptReflectCustomTypeElement::GetStringList()
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

