#ifndef _ALITTLE_ALittleScriptCustomTypeDotIdElement_H_
#define _ALITTLE_ALittleScriptCustomTypeDotIdElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptCustomTypeDotIdNameElement;
class ALittleScriptStringElement;

class ALittleScriptCustomTypeDotIdElement : public ABnfNodeElement
{
public:
    ALittleScriptCustomTypeDotIdElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCustomTypeDotIdElement() { }

private:
    bool m_flag_CustomTypeDotIdName = false;
    std::shared_ptr<ALittleScriptCustomTypeDotIdNameElement> m_cache_CustomTypeDotIdName;
public:
    std::shared_ptr<ALittleScriptCustomTypeDotIdNameElement> GetCustomTypeDotIdName()
    {
        if (m_flag_CustomTypeDotIdName) return m_cache_CustomTypeDotIdName;
        m_flag_CustomTypeDotIdName = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeDotIdNameElement>(child);
            if (node != nullptr)
            {
                m_cache_CustomTypeDotIdName = node;
                break;
            }
        }
        return m_cache_CustomTypeDotIdName;
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

#endif // _ALITTLE_ALittleScriptCustomTypeDotIdElement_H_
