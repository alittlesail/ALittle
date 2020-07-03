#ifndef _ALITTLE_ALittleScriptOp6SuffixElement_H_
#define _ALITTLE_ALittleScriptOp6SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp6Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp6SuffixEeElement;
class ALittleScriptOp2ValueElement;

class ALittleScriptOp6SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp6SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp6SuffixElement() { }

private:
    bool m_flag_Op6 = false;
    std::shared_ptr<ALittleScriptOp6Element> m_cache_Op6;
public:
    std::shared_ptr<ALittleScriptOp6Element> GetOp6()
    {
        if (m_flag_Op6) return m_cache_Op6;
        m_flag_Op6 = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp6Element>(child);
            if (node != nullptr)
            {
                m_cache_Op6 = node;
                break;
            }
        }
        return m_cache_Op6;
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
private:
    bool m_flag_Op6SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp6SuffixEeElement>> m_list_Op6SuffixEe;
public:
    std::vector<std::shared_ptr<ALittleScriptOp6SuffixEeElement>> GetOp6SuffixEeList()
    {
        if (m_flag_Op6SuffixEe) return m_list_Op6SuffixEe;
        m_flag_Op6SuffixEe = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp6SuffixEeElement>(child);
            if (node != nullptr)
                m_list_Op6SuffixEe.push_back(node);
        }
        return m_list_Op6SuffixEe;
    }
private:
    bool m_flag_Op2Value = false;
    std::shared_ptr<ALittleScriptOp2ValueElement> m_cache_Op2Value;
public:
    std::shared_ptr<ALittleScriptOp2ValueElement> GetOp2Value()
    {
        if (m_flag_Op2Value) return m_cache_Op2Value;
        m_flag_Op2Value = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp2ValueElement>(child);
            if (node != nullptr)
            {
                m_cache_Op2Value = node;
                break;
            }
        }
        return m_cache_Op2Value;
    }
};

#endif // _ALITTLE_ALittleScriptOp6SuffixElement_H_
