#ifndef _ALITTLE_ALittleScriptOp8SuffixElement_H_
#define _ALITTLE_ALittleScriptOp8SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp8Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp8SuffixEeElement;

class ALittleScriptOp8SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp8SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp8SuffixElement() { }

private:
    bool m_flag_Op8 = false;
    std::shared_ptr<ALittleScriptOp8Element> m_cache_Op8;
public:
    std::shared_ptr<ALittleScriptOp8Element> GetOp8()
    {
        if (m_flag_Op8) return m_cache_Op8;
        m_flag_Op8 = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp8Element>(child);
            if (node != nullptr)
            {
                m_cache_Op8 = node;
                break;
            }
        }
        return m_cache_Op8;
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
    bool m_flag_Op8SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp8SuffixEeElement>> m_list_Op8SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp8SuffixEeElement>>& GetOp8SuffixEeList()
    {
        if (m_flag_Op8SuffixEe) return m_list_Op8SuffixEe;
        m_flag_Op8SuffixEe = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp8SuffixEeElement>(child);
            if (node != nullptr)
                m_list_Op8SuffixEe.push_back(node);
        }
        return m_list_Op8SuffixEe;
    }
};

#endif // _ALITTLE_ALittleScriptOp8SuffixElement_H_
