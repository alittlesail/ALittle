#ifndef _ALITTLE_ALittleScriptOp6SuffixEeElement_H_
#define _ALITTLE_ALittleScriptOp6SuffixEeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp3SuffixElement;
class ALittleScriptOp4SuffixElement;
class ALittleScriptOp5SuffixElement;

class ALittleScriptOp6SuffixEeElement : public ABnfNodeElement
{
public:
    ALittleScriptOp6SuffixEeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp6SuffixEeElement() { }

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
    bool m_flag_Op4Suffix = false;
    std::shared_ptr<ALittleScriptOp4SuffixElement> m_cache_Op4Suffix;
public:
    std::shared_ptr<ALittleScriptOp4SuffixElement> GetOp4Suffix()
    {
        if (m_flag_Op4Suffix) return m_cache_Op4Suffix;
        m_flag_Op4Suffix = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp4SuffixElement>(child);
            if (node != nullptr)
            {
                m_cache_Op4Suffix = node;
                break;
            }
        }
        return m_cache_Op4Suffix;
    }
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
};

#endif // _ALITTLE_ALittleScriptOp6SuffixEeElement_H_
