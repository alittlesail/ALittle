#include "ALittleScriptCustomTypeTemplateElement.h"

#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptAllTypeElement>>& ALittleScriptCustomTypeTemplateElement::GetAllTypeList()
{
    if (m_flag_AllType) return m_list_AllType;
    m_flag_AllType = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeElement>(child);
        if (node != nullptr)
            m_list_AllType.push_back(node);
    }
    return m_list_AllType;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptCustomTypeTemplateElement::GetStringList()
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

