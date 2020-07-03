#ifndef _ALITTLE_ALittleScriptEnumBodyDecElement_H_
#define _ALITTLE_ALittleScriptEnumBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptEnumVarDecElement;
class ALittleScriptStringElement;

class ALittleScriptEnumBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptEnumBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptEnumBodyDecElement() { }

private:
    bool m_flag_EnumVarDec = false;
    std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>> m_list_EnumVarDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptEnumVarDecElement>>& GetEnumVarDecList()
    {
        if (m_flag_EnumVarDec) return m_list_EnumVarDec;
        m_flag_EnumVarDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptEnumVarDecElement>(child);
            if (node != nullptr)
                m_list_EnumVarDec.push_back(node);
        }
        return m_list_EnumVarDec;
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

#endif // _ALITTLE_ALittleScriptEnumBodyDecElement_H_
