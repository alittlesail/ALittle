#ifndef _ALITTLE_ALittleScriptLanguageModifierElement_H_
#define _ALITTLE_ALittleScriptLanguageModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptLanguageBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptLanguageModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptLanguageModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptLanguageModifierElement() { }

private:
    bool m_flag_LanguageBodyDec = false;
    std::shared_ptr<ALittleScriptLanguageBodyDecElement> m_cache_LanguageBodyDec;
public:
    std::shared_ptr<ALittleScriptLanguageBodyDecElement> GetLanguageBodyDec()
    {
        if (m_flag_LanguageBodyDec) return m_cache_LanguageBodyDec;
        m_flag_LanguageBodyDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptLanguageBodyDecElement>(child);
            if (node != nullptr)
            {
                m_cache_LanguageBodyDec = node;
                break;
            }
        }
        return m_cache_LanguageBodyDec;
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

#endif // _ALITTLE_ALittleScriptLanguageModifierElement_H_
