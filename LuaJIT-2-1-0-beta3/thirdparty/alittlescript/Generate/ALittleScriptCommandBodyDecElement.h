#ifndef _ALITTLE_ALittleScriptCommandBodyDecElement_H_
#define _ALITTLE_ALittleScriptCommandBodyDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptTextElement;
class ALittleScriptStringElement;

class ALittleScriptCommandBodyDecElement : public ABnfNodeElement
{
public:
    ALittleScriptCommandBodyDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCommandBodyDecElement() { }

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

#endif // _ALITTLE_ALittleScriptCommandBodyDecElement_H_
