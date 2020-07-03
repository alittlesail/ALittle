#ifndef _ALITTLE_ALittleScriptForStepStatElement_H_
#define _ALITTLE_ALittleScriptForStepStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptValueStatElement;

class ALittleScriptForStepStatElement : public ABnfNodeElement
{
public:
    ALittleScriptForStepStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForStepStatElement() { }

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
};

#endif // _ALITTLE_ALittleScriptForStepStatElement_H_
