#include "ALittleScriptEnumVarDecElement.h"

#include "ALittleScriptEnumVarNameDecElement.h"
#include "ALittleScriptNumberElement.h"
#include "ALittleScriptTextElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptEnumVarNameDecElement> ALittleScriptEnumVarDecElement::GetEnumVarNameDec()
{
    if (m_flag_EnumVarNameDec) return m_cache_EnumVarNameDec;
    m_flag_EnumVarNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptEnumVarNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_EnumVarNameDec = node;
            break;
        }
    }
    return m_cache_EnumVarNameDec;
}
std::shared_ptr<ALittleScriptNumberElement> ALittleScriptEnumVarDecElement::GetNumber()
{
    if (m_flag_Number) return m_cache_Number;
    m_flag_Number = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptNumberElement>(child);
        if (node != nullptr)
        {
            m_cache_Number = node;
            break;
        }
    }
    return m_cache_Number;
}
std::shared_ptr<ALittleScriptTextElement> ALittleScriptEnumVarDecElement::GetText()
{
    if (m_flag_Text) return m_cache_Text;
    m_flag_Text = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTextElement>(child);
        if (node != nullptr)
        {
            m_cache_Text = node;
            break;
        }
    }
    return m_cache_Text;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptEnumVarDecElement::GetStringList()
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

