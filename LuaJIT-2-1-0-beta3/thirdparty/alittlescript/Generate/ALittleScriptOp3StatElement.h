#ifndef _ALITTLE_ALittleScriptOp3StatElement_H_
#define _ALITTLE_ALittleScriptOp3StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp3SuffixElement;
class ALittleScriptOp3SuffixExElement;

class ALittleScriptOp3StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp3StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp3StatElement() { }

private:
    bool m_flag_Op3Suffix = false;
    std::shared_ptr<ALittleScriptOp3SuffixElement> m_cache_Op3Suffix;
public:
    std::shared_ptr<ALittleScriptOp3SuffixElement> GetOp3Suffix()
    {
        if (m_flag_Op3Suffix) return m_cache_Op3Suffix;
        m_flag_Op3Suffix = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp3SuffixElement>(child);
            if (node != nullptr)
            {
                m_cache_Op3Suffix = node;
                break;
            }
        }
        return m_cache_Op3Suffix;
    }
private:
    bool m_flag_Op3SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp3SuffixExElement>> m_list_Op3SuffixEx;
public:
    std::vector<std::shared_ptr<ALittleScriptOp3SuffixExElement>> GetOp3SuffixExList()
    {
        if (m_flag_Op3SuffixEx) return m_list_Op3SuffixEx;
        m_flag_Op3SuffixEx = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp3SuffixExElement>(child);
            if (node != nullptr)
                m_list_Op3SuffixEx.push_back(node);
        }
        return m_list_Op3SuffixEx;
    }
};

#endif // _ALITTLE_ALittleScriptOp3StatElement_H_
