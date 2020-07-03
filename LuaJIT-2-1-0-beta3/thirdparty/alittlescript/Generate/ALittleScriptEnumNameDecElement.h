#ifndef _ALITTLE_ALittleScriptEnumNameDecElement_H_
#define _ALITTLE_ALittleScriptEnumNameDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptIdElement;

class ALittleScriptEnumNameDecElement : public ABnfNodeElement
{
public:
    ALittleScriptEnumNameDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptEnumNameDecElement() { }

private:
    bool m_flag_Id = false;
    std::shared_ptr<ALittleScriptIdElement> m_cache_Id;
public:
    std::shared_ptr<ALittleScriptIdElement> GetId()
    {
        if (m_flag_Id) return m_cache_Id;
        m_flag_Id = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptIdElement>(child);
            if (node != nullptr)
            {
                m_cache_Id = node;
                break;
            }
        }
        return m_cache_Id;
    }
};

#endif // _ALITTLE_ALittleScriptEnumNameDecElement_H_
