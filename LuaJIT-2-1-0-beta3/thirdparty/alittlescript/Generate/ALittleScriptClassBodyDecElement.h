#ifndef _ALITTLE_ALittleScriptClassBodyDecElement_H_
#define _ALITTLE_ALittleScriptClassBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptClassElementDecElement;
class ALittleScriptStringElement;

class ALittleScriptClassBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassBodyDecElement() { }

private:
    bool m_flag_ClassElementDec = false;
    std::vector<std::shared_ptr<ALittleScriptClassElementDecElement>> m_list_ClassElementDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptClassElementDecElement>>& GetClassElementDecList()
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

#endif // _ALITTLE_ALittleScriptClassBodyDecElement_H_
