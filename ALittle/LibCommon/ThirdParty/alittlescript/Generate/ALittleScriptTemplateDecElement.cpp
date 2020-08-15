#include "ALittleScriptTemplateDecElement.h"

#include "ALittleScriptTemplatePairDecElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptTemplatePairDecElement>>& ALittleScriptTemplateDecElement::GetTemplatePairDecList()
{
    if (m_flag_TemplatePairDec) return m_list_TemplatePairDec;
    m_flag_TemplatePairDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTemplatePairDecElement>(child);
        if (node != nullptr)
            m_list_TemplatePairDec.push_back(node);
    }
    return m_list_TemplatePairDec;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptTemplateDecElement::GetStringList()
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

