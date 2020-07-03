#ifndef _ALITTLE_ALittleScriptTemplatePairDecElement_H_
#define _ALITTLE_ALittleScriptTemplatePairDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptTemplateNameDecElement;
class ALittleScriptTemplateExtendsDecElement;

class ALittleScriptTemplatePairDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplatePairDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplatePairDecElement() { }

private:
    bool m_flag_TemplateNameDec = false;
    std::shared_ptr<ALittleScriptTemplateNameDecElement> m_cache_TemplateNameDec;
public:
    std::shared_ptr<ALittleScriptTemplateNameDecElement> GetTemplateNameDec()
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
private:
    bool m_flag_TemplateExtendsDec = false;
    std::shared_ptr<ALittleScriptTemplateExtendsDecElement> m_cache_TemplateExtendsDec;
public:
    std::shared_ptr<ALittleScriptTemplateExtendsDecElement> GetTemplateExtendsDec()
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
};

#endif // _ALITTLE_ALittleScriptTemplatePairDecElement_H_
