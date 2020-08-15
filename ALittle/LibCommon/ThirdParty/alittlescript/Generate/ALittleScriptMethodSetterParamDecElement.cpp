#include "ALittleScriptMethodSetterParamDecElement.h"

#include "ALittleScriptMethodParamOneDecElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptMethodParamOneDecElement> ALittleScriptMethodSetterParamDecElement::GetMethodParamOneDec()
{
    if (m_flag_MethodParamOneDec) return m_cache_MethodParamOneDec;
    m_flag_MethodParamOneDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodParamOneDec = node;
            break;
        }
    }
    return m_cache_MethodParamOneDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptMethodSetterParamDecElement::GetStringList()
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

