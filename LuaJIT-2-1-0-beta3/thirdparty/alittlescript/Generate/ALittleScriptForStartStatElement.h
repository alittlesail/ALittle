#ifndef _ALITTLE_ALittleScriptForStartStatElement_H_
#define _ALITTLE_ALittleScriptForStartStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptForStartStatElement : public ABnfNodeElement
{
public:
    ALittleScriptForStartStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForStartStatElement() { }

private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat()
    {
        if (m_flag_ValueStat) return m_cache_ValueStat;
        m_flag_ValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ValueStat = node;
                break;
            }
        }
        return m_cache_ValueStat;
    }
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString()
    {
        if (m_flag_String) return m_cache_String;
        m_flag_String = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
            if (node != nullptr)
            {
                m_cache_String = node;
                break;
            }
        }
        return m_cache_String;
    }
};

#endif // _ALITTLE_ALittleScriptForStartStatElement_H_
