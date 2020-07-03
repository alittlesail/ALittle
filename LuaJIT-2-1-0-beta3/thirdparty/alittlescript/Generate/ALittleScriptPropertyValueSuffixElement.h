#ifndef _ALITTLE_ALittleScriptPropertyValueSuffixElement_H_
#define _ALITTLE_ALittleScriptPropertyValueSuffixElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueDotIdElement;
class ALittleScriptPropertyValueMethodCallElement;
class ALittleScriptPropertyValueBracketValueElement;

class ALittleScriptPropertyValueSuffixElement : public ABnfNodeElement
{
public:
    ALittleScriptPropertyValueSuffixElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptPropertyValueSuffixElement() { }

private:
    bool m_flag_PropertyValueDotId = false;
    std::shared_ptr<ALittleScriptPropertyValueDotIdElement> m_cache_PropertyValueDotId;
public:
    std::shared_ptr<ALittleScriptPropertyValueDotIdElement> GetPropertyValueDotId()
    {
        if (m_flag_PropertyValueDotId) return m_cache_PropertyValueDotId;
        m_flag_PropertyValueDotId = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueDotIdElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueDotId = node;
                break;
            }
        }
        return m_cache_PropertyValueDotId;
    }
private:
    bool m_flag_PropertyValueMethodCall = false;
    std::shared_ptr<ALittleScriptPropertyValueMethodCallElement> m_cache_PropertyValueMethodCall;
public:
    std::shared_ptr<ALittleScriptPropertyValueMethodCallElement> GetPropertyValueMethodCall()
    {
        if (m_flag_PropertyValueMethodCall) return m_cache_PropertyValueMethodCall;
        m_flag_PropertyValueMethodCall = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueMethodCallElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueMethodCall = node;
                break;
            }
        }
        return m_cache_PropertyValueMethodCall;
    }
private:
    bool m_flag_PropertyValueBracketValue = false;
    std::shared_ptr<ALittleScriptPropertyValueBracketValueElement> m_cache_PropertyValueBracketValue;
public:
    std::shared_ptr<ALittleScriptPropertyValueBracketValueElement> GetPropertyValueBracketValue()
    {
        if (m_flag_PropertyValueBracketValue) return m_cache_PropertyValueBracketValue;
        m_flag_PropertyValueBracketValue = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueBracketValueElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValueBracketValue = node;
                break;
            }
        }
        return m_cache_PropertyValueBracketValue;
    }
};

#endif // _ALITTLE_ALittleScriptPropertyValueSuffixElement_H_
