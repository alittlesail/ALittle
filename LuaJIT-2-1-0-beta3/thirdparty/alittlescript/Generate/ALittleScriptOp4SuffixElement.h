#ifndef _ALITTLE_ALittleScriptOp4SuffixElement_H_
#define _ALITTLE_ALittleScriptOp4SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp4Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp4SuffixEeElement;

class ALittleScriptOp4SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp4SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp4SuffixElement() { }

private:
    bool m_flag_Op4 = false;
    std::shared_ptr<ALittleScriptOp4Element> m_cache_Op4;
public:
    std::shared_ptr<ALittleScriptOp4Element> GetOp4()
    {
        if (m_flag_Op4) return m_cache_Op4;
        m_flag_Op4 = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp4Element>(child);
            if (node != nullptr)
            {
                m_cache_Op4 = node;
                break;
            }
        }
        return m_cache_Op4;
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
    bool m_flag_Op4SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp4SuffixEeElement>> m_list_Op4SuffixEe;
public:
    std::vector<std::shared_ptr<ALittleScriptOp4SuffixEeElement>> GetOp4SuffixEeList()
    {
        if (m_flag_Op4SuffixEe) return m_list_Op4SuffixEe;
        m_flag_Op4SuffixEe = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp4SuffixEeElement>(child);
            if (node != nullptr)
                m_list_Op4SuffixEe.push_back(node);
        }
        return m_list_Op4SuffixEe;
    }
};

#endif // _ALITTLE_ALittleScriptOp4SuffixElement_H_
