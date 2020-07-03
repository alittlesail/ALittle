#ifndef _ALITTLE_ALittleScriptStructOptionDecElement_H_
#define _ALITTLE_ALittleScriptStructOptionDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptStructOptionNameDecElement;
class ALittleScriptTextElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptStructOptionDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructOptionDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructOptionDecElement() { }

private:
    bool m_flag_StructOptionNameDec = false;
    std::shared_ptr<ALittleScriptStructOptionNameDecElement> m_cache_StructOptionNameDec;
public:
    std::shared_ptr<ALittleScriptStructOptionNameDecElement> GetStructOptionNameDec()
    {
        if (m_flag_StructOptionNameDec) return m_cache_StructOptionNameDec;
        m_flag_StructOptionNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructOptionNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_StructOptionNameDec = node;
                break;
            }
        }
        return m_cache_StructOptionNameDec;
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
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey()
    {
        if (m_flag_Key) return m_cache_Key;
        m_flag_Key = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptKeyElement>(child);
            if (node != nullptr)
            {
                m_cache_Key = node;
                break;
            }
        }
        return m_cache_Key;
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

#endif // _ALITTLE_ALittleScriptStructOptionDecElement_H_
