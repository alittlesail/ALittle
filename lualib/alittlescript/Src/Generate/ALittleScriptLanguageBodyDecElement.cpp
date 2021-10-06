#include "ALittleScriptLanguageBodyDecElement.h"

#include "ALittleScriptLanguageNameDecElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptLanguageNameDecElement>>& ALittleScriptLanguageBodyDecElement::GetLanguageNameDecList()
{
    if (m_flag_LanguageNameDec) return m_list_LanguageNameDec;
    m_flag_LanguageNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptLanguageNameDecElement>(child);
        if (node != nullptr)
            m_list_LanguageNameDec.push_back(node);
    }
    return m_list_LanguageNameDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptLanguageBodyDecElement::GetStringList()
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

