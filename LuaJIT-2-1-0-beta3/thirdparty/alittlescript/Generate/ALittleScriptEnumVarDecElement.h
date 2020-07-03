#ifndef _ALITTLE_ALittleScriptEnumVarDecElement_H_
#define _ALITTLE_ALittleScriptEnumVarDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptEnumVarNameDecElement;
class ALittleScriptNumberElement;
class ALittleScriptTextElement;
class ALittleScriptStringElement;

class ALittleScriptEnumVarDecElement : public ABnfNodeElement
{
public:
    ALittleScriptEnumVarDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptEnumVarDecElement() { }

private:
    bool m_flag_EnumVarNameDec = false;
    std::shared_ptr<ALittleScriptEnumVarNameDecElement> m_cache_EnumVarNameDec;
public:
    std::shared_ptr<ALittleScriptEnumVarNameDecElement> GetEnumVarNameDec()
    {
        if (m_flag_EnumVarNameDec) return m_cache_EnumVarNameDec;
        m_flag_EnumVarNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptEnumVarNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_EnumVarNameDec = node;
                break;
            }
        }
        return m_cache_EnumVarNameDec;
    }
private:
    bool m_flag_Number = false;
    std::shared_ptr<ALittleScriptNumberElement> m_cache_Number;
public:
    std::shared_ptr<ALittleScriptNumberElement> GetNumber()
    {
        if (m_flag_Number) return m_cache_Number;
        m_flag_Number = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptNumberElement>(child);
            if (node != nullptr)
            {
                m_cache_Number = node;
                break;
            }
        }
        return m_cache_Number;
    }
private:
    bool m_flag_Text = false;
    std::shared_ptr<ALittleScriptTextElement> m_cache_Text;
public:
    std::shared_ptr<ALittleScriptTextElement> GetText()
    {
        if (m_flag_Text) return m_cache_Text;
        m_flag_Text = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptTextElement>(child);
            if (node != nullptr)
            {
                m_cache_Text = node;
                break;
            }
        }
        return m_cache_Text;
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

#endif // _ALITTLE_ALittleScriptEnumVarDecElement_H_
