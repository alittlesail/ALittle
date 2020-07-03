#ifndef _ALITTLE_ALittleScriptOp6SuffixExElement_H_
#define _ALITTLE_ALittleScriptOp6SuffixExElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp6SuffixElement;
class ALittleScriptOp7SuffixElement;
class ALittleScriptOp8SuffixElement;

class ALittleScriptOp6SuffixExElement : public ABnfNodeElement
{
public:
    ALittleScriptOp6SuffixExElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp6SuffixExElement() { }

private:
    bool m_flag_Op6Suffix = false;
    std::shared_ptr<ALittleScriptOp6SuffixElement> m_cache_Op6Suffix;
public:
    std::shared_ptr<ALittleScriptOp6SuffixElement> GetOp6Suffix()
    {
        if (m_flag_Op6Suffix) return m_cache_Op6Suffix;
        m_flag_Op6Suffix = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp6SuffixElement>(child);
            if (node != nullptr)
            {
                m_cache_Op6Suffix = node;
                break;
            }
        }
        return m_cache_Op6Suffix;
    }
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

#endif // _ALITTLE_ALittleScriptOp6SuffixExElement_H_
