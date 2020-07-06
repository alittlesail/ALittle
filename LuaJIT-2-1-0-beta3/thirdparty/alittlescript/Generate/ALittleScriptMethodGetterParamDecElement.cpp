#include "ALittleScriptMethodGetterParamDecElement.h"

#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptMethodGetterParamDecElement::GetStringList()
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

