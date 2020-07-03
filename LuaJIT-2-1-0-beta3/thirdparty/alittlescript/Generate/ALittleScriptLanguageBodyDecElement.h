#ifndef _ALITTLE_ALittleScriptLanguageBodyDecElement_H_
#define _ALITTLE_ALittleScriptLanguageBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptLanguageNameDecElement;
class ALittleScriptStringElement;

class ALittleScriptLanguageBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptLanguageBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptLanguageBodyDecElement() { }

private:
    bool m_flag_LanguageNameDec = false;
    std::vector<std::shared_ptr<ALittleScriptLanguageNameDecElement>> m_list_LanguageNameDec;
public:
    const std::vector<std::shared_ptr<ALittleScriptLanguageNameDecElement>>& GetLanguageNameDecList()
    {
        if (m_flag_LanguageNameDec) return m_list_LanguageNameDec;
        m_flag_LanguageNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptLanguageNameDecElement>(child);
            if (node != nullptr)
                m_list_LanguageNameDec.push_back(node);
        }
        return m_list_LanguageNameDec;
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

#endif // _ALITTLE_ALittleScriptLanguageBodyDecElement_H_
