#include "ALittleScriptClassBodyDecElement.h"

#include "ALittleScriptClassElementDecElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptClassElementDecElement>>& ALittleScriptClassBodyDecElement::GetClassElementDecList()
{
    if (m_flag_ClassElementDec) return m_list_ClassElementDec;
    m_flag_ClassElementDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(child);
        if (node != nullptr)
            m_list_ClassElementDec.push_back(node);
    }
    return m_list_ClassElementDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptClassBodyDecElement::GetStringList()
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

