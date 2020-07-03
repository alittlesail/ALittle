#ifndef _ALITTLE_ALittleScriptPropertyValueDotIdElement_H_
#define _ALITTLE_ALittleScriptPropertyValueDotIdElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueDotIdNameElement;
class ALittleScriptStringElement;

class ALittleScriptPropertyValueDotIdElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueDotIdElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueDotIdElement() { }

private:
    bool m_flag_PropertyValueDotIdName = false;
    std::shared_ptr<ALittleScriptPropertyValueDotIdNameElement> m_cache_PropertyValueDotIdName;
public:
    std::shared_ptr<ALittleScriptPropertyValueDotIdNameElement> GetPropertyValueDotIdName()
    {
        if (m_flag_PropertyValueDotIdName) return m_cache_PropertyValueDotIdName;
        m_flag_PropertyValueDotIdName = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueDotIdNameElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueDotIdName = node;
                break;
            }
        }
        return m_cache_PropertyValueDotIdName;
    }
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString()
    {
        if (m_flag_String) return m_cache_String;
        m_flag_String = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
            if (node != nullptr)
            {
                m_cache_String = node;
                break;
            }
        }
        return m_cache_String;
    }
};

#endif // _ALITTLE_ALittleScriptPropertyValueDotIdElement_H_
