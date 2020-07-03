#ifndef _ALITTLE_ALittleScriptOp5StatElement_H_
#define _ALITTLE_ALittleScriptOp5StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp5SuffixElement;
class ALittleScriptOp5SuffixExElement;

class ALittleScriptOp5StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp5StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp5StatElement() { }

private:
    bool m_flag_Op5Suffix = false;
    std::shared_ptr<ALittleScriptOp5SuffixElement> m_cache_Op5Suffix;
public:
    std::shared_ptr<ALittleScriptOp5SuffixElement> GetOp5Suffix()
    {
        if (m_flag_Op5Suffix) return m_cache_Op5Suffix;
        m_flag_Op5Suffix = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp5SuffixElement>(child);
            if (node != nullptr)
            {
                m_cache_Op5Suffix = node;
                break;
            }
        }
        return m_cache_Op5Suffix;
    }
private:
    bool m_flag_Op5SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp5SuffixExElement>> m_list_Op5SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp5SuffixExElement>>& GetOp5SuffixExList()
    {
        if (m_flag_Op5SuffixEx) return m_list_Op5SuffixEx;
        m_flag_Op5SuffixEx = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp5SuffixExElement>(child);
            if (node != nullptr)
                m_list_Op5SuffixEx.push_back(node);
        }
        return m_list_Op5SuffixEx;
    }
};

#endif // _ALITTLE_ALittleScriptOp5StatElement_H_
