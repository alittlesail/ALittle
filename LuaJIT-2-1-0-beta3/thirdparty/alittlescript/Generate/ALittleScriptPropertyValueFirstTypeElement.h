#ifndef _ALITTLE_ALittleScriptPropertyValueFirstTypeElement_H_
#define _ALITTLE_ALittleScriptPropertyValueFirstTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueThisTypeElement;
class ALittleScriptPropertyValueCustomTypeElement;
class ALittleScriptPropertyValueCastTypeElement;

class ALittleScriptPropertyValueFirstTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueFirstTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueFirstTypeElement() { }

private:
    bool m_flag_PropertyValueThisType = false;
    std::shared_ptr<ALittleScriptPropertyValueThisTypeElement> m_cache_PropertyValueThisType;
public:
    std::shared_ptr<ALittleScriptPropertyValueThisTypeElement> GetPropertyValueThisType()
    {
        if (m_flag_PropertyValueThisType) return m_cache_PropertyValueThisType;
        m_flag_PropertyValueThisType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueThisTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueThisType = node;
                break;
            }
        }
        return m_cache_PropertyValueThisType;
    }
private:
    bool m_flag_PropertyValueCustomType = false;
    std::shared_ptr<ALittleScriptPropertyValueCustomTypeElement> m_cache_PropertyValueCustomType;
public:
    std::shared_ptr<ALittleScriptPropertyValueCustomTypeElement> GetPropertyValueCustomType()
    {
        if (m_flag_PropertyValueCustomType) return m_cache_PropertyValueCustomType;
        m_flag_PropertyValueCustomType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueCustomTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueCustomType = node;
                break;
            }
        }
        return m_cache_PropertyValueCustomType;
    }
private:
    bool m_flag_PropertyValueCastType = false;
    std::shared_ptr<ALittleScriptPropertyValueCastTypeElement> m_cache_PropertyValueCastType;
public:
    std::shared_ptr<ALittleScriptPropertyValueCastTypeElement> GetPropertyValueCastType()
    {
        if (m_flag_PropertyValueCastType) return m_cache_PropertyValueCastType;
        m_flag_PropertyValueCastType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueCastTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueCastType = node;
                break;
            }
        }
        return m_cache_PropertyValueCastType;
    }
};

#endif // _ALITTLE_ALittleScriptPropertyValueFirstTypeElement_H_
