#ifndef _ALITTLE_ALittleScriptRootElement_H_
#define _ALITTLE_ALittleScriptRootElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptNamespaceDecElement;

class ALittleScriptRootElement : public ABnfNodeElement
{
public:
    ALittleScriptRootElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptRootElement() { }

private:
    bool m_flag_NamespaceDec = false;
    std::shared_ptr<ALittleScriptNamespaceDecElement> m_cache_NamespaceDec;
public:
    std::shared_ptr<ALittleScriptNamespaceDecElement> GetNamespaceDec()
    {
        if (m_flag_NamespaceDec) return m_cache_NamespaceDec;
        m_flag_NamespaceDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(child);
            if (node != nullptr)
            {
                m_cache_NamespaceDec = node;
                break;
            }
        }
        return m_cache_NamespaceDec;
    }
};

#endif // _ALITTLE_ALittleScriptRootElement_H_
