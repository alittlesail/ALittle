#include "ALittleScriptTemplatePairDecElement.h"

#include "ALittleScriptTemplateNameDecElement.h"
#include "ALittleScriptTemplateExtendsDecElement.h"

std::shared_ptr<ALittleScriptTemplateNameDecElement> ALittleScriptTemplatePairDecElement::GetTemplateNameDec()
{
    if (m_flag_TemplateNameDec) return m_cache_TemplateNameDec;
    m_flag_TemplateNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTemplateNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_TemplateNameDec = node;
            break;
        }
    }
    return m_cache_TemplateNameDec;
}
std::shared_ptr<ALittleScriptTemplateExtendsDecElement> ALittleScriptTemplatePairDecElement::GetTemplateExtendsDec()
{
    if (m_flag_TemplateExtendsDec) return m_cache_TemplateExtendsDec;
    m_flag_TemplateExtendsDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptTemplateExtendsDecElement>(child);
        if (node != nullptr)
        {
            m_cache_TemplateExtendsDec = node;
            break;
        }
    }
    return m_cache_TemplateExtendsDec;
}

