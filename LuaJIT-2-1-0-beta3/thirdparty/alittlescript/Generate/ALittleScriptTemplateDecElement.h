#ifndef _ALITTLE_ALittleScriptTemplateDecElement_H_
#define _ALITTLE_ALittleScriptTemplateDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptTemplatePairDecElement;
class ALittleScriptStringElement;

class ALittleScriptTemplateDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplateDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplateDecElement() { }

private:
    bool m_flag_TemplatePairDec = false;
    std::vector<std::shared_ptr<ALittleScriptTemplatePairDecElement>> m_list_TemplatePairDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptTemplatePairDecElement>>& GetTemplatePairDecList()
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
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList()
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
};

#endif // _ALITTLE_ALittleScriptTemplateDecElement_H_
