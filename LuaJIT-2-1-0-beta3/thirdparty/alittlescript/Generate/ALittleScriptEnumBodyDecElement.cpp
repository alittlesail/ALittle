#include "ALittleScriptEnumBodyDecElement.h"

#include "ALittleScriptEnumVarDecElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& ALittleScriptEnumBodyDecElement::GetEnumVarDecList()
{
    if (m_flag_EnumVarDec) return m_list_EnumVarDec;
    m_flag_EnumVarDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptEnumVarDecElement>(child);
        if (node != nullptr)
            m_list_EnumVarDec.push_back(node);
    }
    return m_list_EnumVarDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptEnumBodyDecElement::GetStringList()
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

