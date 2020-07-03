#ifndef _ALITTLE_ALittleScriptStructBodyDecElement_H_
#define _ALITTLE_ALittleScriptStructBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptStructOptionDecElement;
class ALittleScriptStructVarDecElement;
class ALittleScriptStringElement;

class ALittleScriptStructBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructBodyDecElement() { }

private:
    bool m_flag_StructOptionDec = false;
    std::vector<std::shared_ptr<ALittleScriptStructOptionDecElement>> m_list_StructOptionDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptStructOptionDecElement>>& GetStructOptionDecList()
    {
        if (m_flag_StructOptionDec) return m_list_StructOptionDec;
        m_flag_StructOptionDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructOptionDecElement>(child);
            if (node != nullptr)
                m_list_StructOptionDec.push_back(node);
        }
        return m_list_StructOptionDec;
    }
private:
    bool m_flag_StructVarDec = false;
    std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>> m_list_StructVarDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptStructVarDecElement>>& GetStructVarDecList()
    {
        if (m_flag_StructVarDec) return m_list_StructVarDec;
        m_flag_StructVarDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructVarDecElement>(child);
            if (node != nullptr)
                m_list_StructVarDec.push_back(node);
        }
        return m_list_StructVarDec;
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

#endif // _ALITTLE_ALittleScriptStructBodyDecElement_H_
