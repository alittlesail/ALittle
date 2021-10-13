#include "ALittleScriptMethodParamDecElement.h"

#include "ALittleScriptMethodParamOneDecElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptMethodParamOneDecElement>>& ALittleScriptMethodParamDecElement::GetMethodParamOneDecList()
{
    if (m_flag_MethodParamOneDec) return m_list_MethodParamOneDec;
    m_flag_MethodParamOneDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(child);
        if (node != nullptr)
            m_list_MethodParamOneDec.push_back(node);
    }
    return m_list_MethodParamOneDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptMethodParamDecElement::GetStringList()
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

