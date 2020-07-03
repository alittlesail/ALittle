#ifndef _ALITTLE_ALittleScriptOp5SuffixElement_H_
#define _ALITTLE_ALittleScriptOp5SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp5Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp5SuffixEeElement;

class ALittleScriptOp5SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp5SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp5SuffixElement() { }

private:
    bool m_flag_Op5 = false;
    std::shared_ptr<ALittleScriptOp5Element> m_cache_Op5;
public:
    std::shared_ptr<ALittleScriptOp5Element> GetOp5()
    {
        if (m_flag_Op5) return m_cache_Op5;
        m_flag_Op5 = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp5Element>(child);
            if (node != nullptr)
            {
                m_cache_Op5 = node;
                break;
            }
        }
        return m_cache_Op5;
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
private:
    bool m_flag_Op5SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp5SuffixEeElement>> m_list_Op5SuffixEe;
public:
    std::vector<std::shared_ptr<ALittleScriptOp5SuffixEeElement>> GetOp5SuffixEeList()
    {
        if (m_flag_Op5SuffixEe) return m_list_Op5SuffixEe;
        m_flag_Op5SuffixEe = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp5SuffixEeElement>(child);
            if (node != nullptr)
                m_list_Op5SuffixEe.push_back(node);
        }
        return m_list_Op5SuffixEe;
    }
};

#endif // _ALITTLE_ALittleScriptOp5SuffixElement_H_
