#ifndef _ALITTLE_ALittleScriptPropertyValueMethodCallElement_H_
#define _ALITTLE_ALittleScriptPropertyValueMethodCallElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueMethodTemplateElement;
class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptPropertyValueMethodCallElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueMethodCallElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueMethodCallElement() { }

private:
    bool m_flag_PropertyValueMethodTemplate = false;
    std::shared_ptr<ALittleScriptPropertyValueMethodTemplateElement> m_cache_PropertyValueMethodTemplate;
public:
    std::shared_ptr<ALittleScriptPropertyValueMethodTemplateElement> GetPropertyValueMethodTemplate()
    {
        if (m_flag_PropertyValueMethodTemplate) return m_cache_PropertyValueMethodTemplate;
        m_flag_PropertyValueMethodTemplate = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodTemplateElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueMethodTemplate = node;
                break;
            }
        }
        return m_cache_PropertyValueMethodTemplate;
    }
private:
    bool m_flag_ValueStat = false;
    std::vector<std::shared_ptr<ALittleScriptValueStatElement>> m_list_ValueStat;
public:
    const std::vector<std::shared_ptr<ALittleScriptValueStatElement>>& GetValueStatList()
    {
        if (m_flag_ValueStat) return m_list_ValueStat;
        m_flag_ValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
            if (node != nullptr)
                m_list_ValueStat.push_back(node);
        }
        return m_list_ValueStat;
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

#endif // _ALITTLE_ALittleScriptPropertyValueMethodCallElement_H_
