#ifndef _ALITTLE_ALittleScriptPropertyValueElement_H_
#define _ALITTLE_ALittleScriptPropertyValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueFirstTypeElement;
class ALittleScriptPropertyValueSuffixElement;

class ALittleScriptPropertyValueElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueElement() { }

private:
    bool m_flag_PropertyValueFirstType = false;
    std::shared_ptr<ALittleScriptPropertyValueFirstTypeElement> m_cache_PropertyValueFirstType;
public:
    std::shared_ptr<ALittleScriptPropertyValueFirstTypeElement> GetPropertyValueFirstType()
    {
        if (m_flag_PropertyValueFirstType) return m_cache_PropertyValueFirstType;
        m_flag_PropertyValueFirstType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueFirstTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueFirstType = node;
                break;
            }
        }
        return m_cache_PropertyValueFirstType;
    }
private:
    bool m_flag_PropertyValueSuffix = false;
    std::vector<std::shared_ptr<ALittleScriptPropertyValueSuffixElement>> m_list_PropertyValueSuffix;
public:
    std::vector<std::shared_ptr<ALittleScriptPropertyValueSuffixElement>> GetPropertyValueSuffixList()
    {
        if (m_flag_PropertyValueSuffix) return m_list_PropertyValueSuffix;
        m_flag_PropertyValueSuffix = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(child);
            if (node != nullptr)
                m_list_PropertyValueSuffix.push_back(node);
        }
        return m_list_PropertyValueSuffix;
    }
};

#endif // _ALITTLE_ALittleScriptPropertyValueElement_H_
