#include "ALittleScriptStructBodyDecElement.h"

#include "ALittleScriptStructOptionDecElement.h"
#include "ALittleScriptStructVarDecElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptStructOptionDecElement>>& ALittleScriptStructBodyDecElement::GetStructOptionDecList()
{
    if (m_flag_StructOptionDec) return m_list_StructOptionDec;
    m_flag_StructOptionDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructOptionDecElement>(child);
        if (node != nullptr)
            m_list_StructOptionDec.push_back(node);
    }
    return m_list_StructOptionDec;
}
const std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>>& ALittleScriptStructBodyDecElement::GetStructVarDecList()
{
    if (m_flag_StructVarDec) return m_list_StructVarDec;
    m_flag_StructVarDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructVarDecElement>(child);
        if (node != nullptr)
            m_list_StructVarDec.push_back(node);
    }
    return m_list_StructVarDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptStructBodyDecElement::GetStringList()
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

