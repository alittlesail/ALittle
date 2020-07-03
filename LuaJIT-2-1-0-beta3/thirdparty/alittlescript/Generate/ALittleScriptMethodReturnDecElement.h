#ifndef _ALITTLE_ALittleScriptMethodReturnDecElement_H_
#define _ALITTLE_ALittleScriptMethodReturnDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodReturnOneDecElement;
class ALittleScriptStringElement;

class ALittleScriptMethodReturnDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodReturnDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodReturnDecElement() { }

private:
    bool m_flag_MethodReturnOneDec = false;
    std::vector<std::shared_ptr<ALittleScriptMethodReturnOneDecElement>> m_list_MethodReturnOneDec;
public:
    std::vector<std::shared_ptr<ALittleScriptMethodReturnOneDecElement>> GetMethodReturnOneDecList()
    {
        if (m_flag_MethodReturnOneDec) return m_list_MethodReturnOneDec;
        m_flag_MethodReturnOneDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodReturnOneDecElement>(child);
            if (node != nullptr)
                m_list_MethodReturnOneDec.push_back(node);
        }
        return m_list_MethodReturnOneDec;
    }
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    std::vector<std::shared_ptr<ALittleScriptStringElement>> GetStringList()
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

#endif // _ALITTLE_ALittleScriptMethodReturnDecElement_H_
