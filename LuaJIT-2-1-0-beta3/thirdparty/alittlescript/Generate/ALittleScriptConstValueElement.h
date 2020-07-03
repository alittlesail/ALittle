#ifndef _ALITTLE_ALittleScriptConstValueElement_H_
#define _ALITTLE_ALittleScriptConstValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptTextElement;
class ALittleScriptNumberElement;
class ALittleScriptKeyElement;

class ALittleScriptConstValueElement : public ABnfNodeElement
{
public:
    ALittleScriptConstValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptConstValueElement() { }

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
};

#endif // _ALITTLE_ALittleScriptConstValueElement_H_
