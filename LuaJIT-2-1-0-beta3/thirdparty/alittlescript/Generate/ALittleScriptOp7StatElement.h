#ifndef _ALITTLE_ALittleScriptOp7StatElement_H_
#define _ALITTLE_ALittleScriptOp7StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp7SuffixElement;
class ALittleScriptOp7SuffixExElement;

class ALittleScriptOp7StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp7StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp7StatElement() { }

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
    bool m_flag_Op7SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp7SuffixExElement>> m_list_Op7SuffixEx;
public:
    std::vector<std::shared_ptr<ALittleScriptOp7SuffixExElement>> GetOp7SuffixExList()
    {
        if (m_flag_Op7SuffixEx) return m_list_Op7SuffixEx;
        m_flag_Op7SuffixEx = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp7SuffixExElement>(child);
            if (node != nullptr)
                m_list_Op7SuffixEx.push_back(node);
        }
        return m_list_Op7SuffixEx;
    }
};

#endif // _ALITTLE_ALittleScriptOp7StatElement_H_
