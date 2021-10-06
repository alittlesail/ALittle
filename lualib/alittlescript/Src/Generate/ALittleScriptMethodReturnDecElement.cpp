#include "ALittleScriptMethodReturnDecElement.h"

#include "ALittleScriptMethodReturnOneDecElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptMethodReturnOneDecElement>>& ALittleScriptMethodReturnDecElement::GetMethodReturnOneDecList()
{
    if (m_flag_MethodReturnOneDec) return m_list_MethodReturnOneDec;
    m_flag_MethodReturnOneDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodReturnOneDecElement>(child);
        if (node != nullptr)
            m_list_MethodReturnOneDec.push_back(node);
    }
    return m_list_MethodReturnOneDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptMethodReturnDecElement::GetStringList()
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

