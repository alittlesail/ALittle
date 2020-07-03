#ifndef _ALITTLE_ALittleScriptOp7SuffixExElement_H_
#define _ALITTLE_ALittleScriptOp7SuffixExElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp7SuffixElement;
class ALittleScriptOp8SuffixElement;

class ALittleScriptOp7SuffixExElement : public ABnfNodeElement
{
public:
    ALittleScriptOp7SuffixExElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp7SuffixExElement() { }

private:
    bool m_flag_Op7Suffix = false;
    std::shared_ptr<ALittleScriptOp7SuffixElement> m_cache_Op7Suffix;
public:
    std::shared_ptr<ALittleScriptOp7SuffixElement> GetOp7Suffix()
    {
        if (m_flag_Op7Suffix) return m_cache_Op7Suffix;
        m_flag_Op7Suffix = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp7SuffixElement>(child);
            if (node != nullptr)
            {
                m_cache_Op7Suffix = node;
                break;
            }
        }
        return m_cache_Op7Suffix;
    }
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

#endif // _ALITTLE_ALittleScriptOp7SuffixExElement_H_
