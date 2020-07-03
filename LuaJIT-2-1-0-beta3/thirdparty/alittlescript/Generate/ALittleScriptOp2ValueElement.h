#ifndef _ALITTLE_ALittleScriptOp2ValueElement_H_
#define _ALITTLE_ALittleScriptOp2ValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp2Element;
class ALittleScriptValueFactorStatElement;

class ALittleScriptOp2ValueElement : public ABnfNodeElement
{
public:
    ALittleScriptOp2ValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp2ValueElement() { }

private:
    bool m_flag_Op2 = false;
    std::shared_ptr<ALittleScriptOp2Element> m_cache_Op2;
public:
    std::shared_ptr<ALittleScriptOp2Element> GetOp2()
    {
        if (m_flag_Op2) return m_cache_Op2;
        m_flag_Op2 = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp2Element>(child);
            if (node != nullptr)
            {
                m_cache_Op2 = node;
                break;
            }
        }
        return m_cache_Op2;
    }
private:
    bool m_flag_ValueFactorStat = false;
    std::shared_ptr<ALittleScriptValueFactorStatElement> m_cache_ValueFactorStat;
public:
    std::shared_ptr<ALittleScriptValueFactorStatElement> GetValueFactorStat()
    {
        if (m_flag_ValueFactorStat) return m_cache_ValueFactorStat;
        m_flag_ValueFactorStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueFactorStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ValueFactorStat = node;
                break;
            }
        }
        return m_cache_ValueFactorStat;
    }
};

#endif // _ALITTLE_ALittleScriptOp2ValueElement_H_
