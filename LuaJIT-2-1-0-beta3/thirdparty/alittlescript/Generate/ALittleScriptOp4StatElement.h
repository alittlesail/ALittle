#ifndef _ALITTLE_ALittleScriptOp4StatElement_H_
#define _ALITTLE_ALittleScriptOp4StatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptOp4SuffixElement;
class ALittleScriptOp4SuffixExElement;

class ALittleScriptOp4StatElement : public ABnfNodeElement
{
public:
    ALittleScriptOp4StatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOp4StatElement() { }

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
    bool m_flag_Op4SuffixEx = false;
    std::vector<std::shared_ptr<ALittleScriptOp4SuffixExElement>> m_list_Op4SuffixEx;
public:
    const std::vector<std::shared_ptr<ALittleScriptOp4SuffixExElement>>& GetOp4SuffixExList()
    {
        if (m_flag_Op4SuffixEx) return m_list_Op4SuffixEx;
        m_flag_Op4SuffixEx = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOp4SuffixExElement>(child);
            if (node != nullptr)
                m_list_Op4SuffixEx.push_back(node);
        }
        return m_list_Op4SuffixEx;
    }
};

#endif // _ALITTLE_ALittleScriptOp4StatElement_H_
