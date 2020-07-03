#ifndef _ALITTLE_ALittleScriptPropertyValueMethodTemplateElement_H_
#define _ALITTLE_ALittleScriptPropertyValueMethodTemplateElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptStringElement;

class ALittleScriptPropertyValueMethodTemplateElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueMethodTemplateElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueMethodTemplateElement() { }

private:
    bool m_flag_AllType = false;
    std::vector<std::shared_ptr<ALittleScriptAllTypeElement>> m_list_AllType;
public:
    const std::vector<std::shared_ptr<ALittleScriptAllTypeElement>>& GetAllTypeList()
    {
        if (m_flag_AllType) return m_list_AllType;
        m_flag_AllType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeElement>(child);
            if (node != nullptr)
                m_list_AllType.push_back(node);
        }
        return m_list_AllType;
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

#endif // _ALITTLE_ALittleScriptPropertyValueMethodTemplateElement_H_
