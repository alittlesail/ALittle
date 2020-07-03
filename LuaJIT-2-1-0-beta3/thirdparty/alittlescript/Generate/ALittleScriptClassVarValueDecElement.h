#ifndef _ALITTLE_ALittleScriptClassVarValueDecElement_H_
#define _ALITTLE_ALittleScriptClassVarValueDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptConstValueElement;
class ALittleScriptOpNewStatElement;
class ALittleScriptStringElement;

class ALittleScriptClassVarValueDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassVarValueDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassVarValueDecElement() { }

private:
    bool m_flag_ConstValue = false;
    std::shared_ptr<ALittleScriptConstValueElement> m_cache_ConstValue;
public:
    std::shared_ptr<ALittleScriptConstValueElement> GetConstValue()
    {
        if (m_flag_ConstValue) return m_cache_ConstValue;
        m_flag_ConstValue = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptConstValueElement>(child);
            if (node != nullptr)
            {
                m_cache_ConstValue = node;
                break;
            }
        }
        return m_cache_ConstValue;
    }
private:
    bool m_flag_OpNewStat = false;
    std::shared_ptr<ALittleScriptOpNewStatElement> m_cache_OpNewStat;
public:
    std::shared_ptr<ALittleScriptOpNewStatElement> GetOpNewStat()
    {
        if (m_flag_OpNewStat) return m_cache_OpNewStat;
        m_flag_OpNewStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(child);
            if (node != nullptr)
            {
                m_cache_OpNewStat = node;
                break;
            }
        }
        return m_cache_OpNewStat;
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

#endif // _ALITTLE_ALittleScriptClassVarValueDecElement_H_
