#ifndef _ALITTLE_ALittleScriptOp8SuffixExElement_H_
#define _ALITTLE_ALittleScriptOp8SuffixExElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp8SuffixElement;

class ALittleScriptOp8SuffixExElement : public ABnfNodeElement
{
public:
    ALittleScriptOp8SuffixExElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp8SuffixExElement() { }

private:
    bool m_flag_Op8Suffix = false;
    std::shared_ptr<ALittleScriptOp8SuffixElement> m_cache_Op8Suffix;
public:
    std::shared_ptr<ALittleScriptOp8SuffixElement> GetOp8Suffix()
    {
        if (m_flag_Op8Suffix) return m_cache_Op8Suffix;
        m_flag_Op8Suffix = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp8SuffixElement>(child);
            if (node != nullptr)
            {
                m_cache_Op8Suffix = node;
                break;
            }
        }
        return m_cache_Op8Suffix;
    }
};

#endif // _ALITTLE_ALittleScriptOp8SuffixExElement_H_
