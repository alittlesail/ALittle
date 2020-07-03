#ifndef _ALITTLE_ALittleScriptCommandModifierElement_H_
#define _ALITTLE_ALittleScriptCommandModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptCommandBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptCommandModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptCommandModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCommandModifierElement() { }

private:
    bool m_flag_CommandBodyDec = false;
    std::shared_ptr<ALittleScriptCommandBodyDecElement> m_cache_CommandBodyDec;
public:
    std::shared_ptr<ALittleScriptCommandBodyDecElement> GetCommandBodyDec()
    {
        if (m_flag_CommandBodyDec) return m_cache_CommandBodyDec;
        m_flag_CommandBodyDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCommandBodyDecElement>(child);
            if (node != nullptr)
            {
                m_cache_CommandBodyDec = node;
                break;
            }
        }
        return m_cache_CommandBodyDec;
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

#endif // _ALITTLE_ALittleScriptCommandModifierElement_H_
