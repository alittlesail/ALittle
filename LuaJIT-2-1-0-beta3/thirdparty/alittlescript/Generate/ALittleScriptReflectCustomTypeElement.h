#ifndef _ALITTLE_ALittleScriptReflectCustomTypeElement_H_
#define _ALITTLE_ALittleScriptReflectCustomTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptCustomTypeElement;
class ALittleScriptStringElement;

class ALittleScriptReflectCustomTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptReflectCustomTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptReflectCustomTypeElement() { }

private:
    bool m_flag_CustomType = false;
    std::shared_ptr<ALittleScriptCustomTypeElement> m_cache_CustomType;
public:
    std::shared_ptr<ALittleScriptCustomTypeElement> GetCustomType()
    {
        if (m_flag_CustomType) return m_cache_CustomType;
        m_flag_CustomType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_CustomType = node;
                break;
            }
        }
        return m_cache_CustomType;
    }
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList()
    {
        if (m_flag_String) return m_list_String;
        m_flag_String = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
            if (node != nullptr)
                m_list_String.push_back(node);
        }
        return m_list_String;
    }
};

#endif // _ALITTLE_ALittleScriptReflectCustomTypeElement_H_
