#ifndef _ALITTLE_ALittleScriptOp2StatElement_H_
#define _ALITTLE_ALittleScriptOp2StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp2ValueElement;
class ALittleScriptOp2SuffixExElement;

class ALittleScriptOp2StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp2StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp2StatElement() { }

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
    bool m_flag_Op2SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp2SuffixExElement>> m_list_Op2SuffixEx;
public:
    std::vector<std::shared_ptr<ALittleScriptOp2SuffixExElement>> GetOp2SuffixExList()
    {
        if (m_flag_Op2SuffixEx) return m_list_Op2SuffixEx;
        m_flag_Op2SuffixEx = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp2SuffixExElement>(child);
            if (node != nullptr)
                m_list_Op2SuffixEx.push_back(node);
        }
        return m_list_Op2SuffixEx;
    }
};

#endif // _ALITTLE_ALittleScriptOp2StatElement_H_
