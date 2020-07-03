#ifndef _ALITTLE_ALittleScriptOp7SuffixElement_H_
#define _ALITTLE_ALittleScriptOp7SuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp7Element;
class ALittleScriptValueFactorStatElement;
class ALittleScriptOp2ValueElement;
class ALittleScriptOp7SuffixEeElement;

class ALittleScriptOp7SuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptOp7SuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp7SuffixElement() { }

private:
    bool m_flag_Op7 = false;
    std::shared_ptr<ALittleScriptOp7Element> m_cache_Op7;
public:
    std::shared_ptr<ALittleScriptOp7Element> GetOp7()
    {
        if (m_flag_Op7) return m_cache_Op7;
        m_flag_Op7 = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp7Element>(child);
            if (node != nullptr)
            {
                m_cache_Op7 = node;
                break;
            }
        }
        return m_cache_Op7;
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
    bool m_flag_Op7SuffixEe = false;
    std::vector<std::shared_ptr<ALittleScriptOp7SuffixEeElement>> m_list_Op7SuffixEe;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp7SuffixEeElement>>& GetOp7SuffixEeList()
    {
        if (m_flag_Op7SuffixEe) return m_list_Op7SuffixEe;
        m_flag_Op7SuffixEe = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp7SuffixEeElement>(child);
            if (node != nullptr)
                m_list_Op7SuffixEe.push_back(node);
        }
        return m_list_Op7SuffixEe;
    }
};

#endif // _ALITTLE_ALittleScriptOp7SuffixElement_H_
