#ifndef _ALITTLE_ALittleScriptMethodParamDecElement_H_
#define _ALITTLE_ALittleScriptMethodParamDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodParamOneDecElement;
class ALittleScriptStringElement;

class ALittleScriptMethodParamDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodParamDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodParamDecElement() { }

private:
    bool m_flag_MethodParamOneDec = false;
    std::vector<std::shared_ptr<ALittleScriptMethodParamOneDecElement>> m_list_MethodParamOneDec;
public:
    std::vector<std::shared_ptr<ALittleScriptMethodParamOneDecElement>> GetMethodParamOneDecList()
    {
        if (m_flag_MethodParamOneDec) return m_list_MethodParamOneDec;
        m_flag_MethodParamOneDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamOneDecElement>(child);
            if (node != nullptr)
                m_list_MethodParamOneDec.push_back(node);
        }
        return m_list_MethodParamOneDec;
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

#endif // _ALITTLE_ALittleScriptMethodParamDecElement_H_
