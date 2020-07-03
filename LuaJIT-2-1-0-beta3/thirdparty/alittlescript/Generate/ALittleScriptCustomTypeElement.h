#ifndef _ALITTLE_ALittleScriptCustomTypeElement_H_
#define _ALITTLE_ALittleScriptCustomTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptCustomTypeNameElement;
class ALittleScriptCustomTypeDotIdElement;
class ALittleScriptCustomTypeTemplateElement;

class ALittleScriptCustomTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptCustomTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptCustomTypeElement() { }

private:
    bool m_flag_CustomTypeName = false;
    std::shared_ptr<ALittleScriptCustomTypeNameElement> m_cache_CustomTypeName;
public:
    std::shared_ptr<ALittleScriptCustomTypeNameElement> GetCustomTypeName()
    {
        if (m_flag_CustomTypeName) return m_cache_CustomTypeName;
        m_flag_CustomTypeName = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeNameElement>(child);
            if (node != nullptr)
            {
                m_cache_CustomTypeName = node;
                break;
            }
        }
        return m_cache_CustomTypeName;
    }
private:
    bool m_flag_CustomTypeDotId = false;
    std::shared_ptr<ALittleScriptCustomTypeDotIdElement> m_cache_CustomTypeDotId;
public:
    std::shared_ptr<ALittleScriptCustomTypeDotIdElement> GetCustomTypeDotId()
    {
        if (m_flag_CustomTypeDotId) return m_cache_CustomTypeDotId;
        m_flag_CustomTypeDotId = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeDotIdElement>(child);
            if (node != nullptr)
            {
                m_cache_CustomTypeDotId = node;
                break;
            }
        }
        return m_cache_CustomTypeDotId;
    }
private:
    bool m_flag_CustomTypeTemplate = false;
    std::shared_ptr<ALittleScriptCustomTypeTemplateElement> m_cache_CustomTypeTemplate;
public:
    std::shared_ptr<ALittleScriptCustomTypeTemplateElement> GetCustomTypeTemplate()
    {
        if (m_flag_CustomTypeTemplate) return m_cache_CustomTypeTemplate;
        m_flag_CustomTypeTemplate = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCustomTypeTemplateElement>(child);
            if (node != nullptr)
            {
                m_cache_CustomTypeTemplate = node;
                break;
            }
        }
        return m_cache_CustomTypeTemplate;
    }
};

#endif // _ALITTLE_ALittleScriptCustomTypeElement_H_
