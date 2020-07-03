#ifndef _ALITTLE_ALittleScriptOpAssignExprElement_H_
#define _ALITTLE_ALittleScriptOpAssignExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptPropertyValueElement;
class ALittleScriptOpAssignElement;
class ALittleScriptValueStatElement;
class ALittleScriptStringElement;

class ALittleScriptOpAssignExprElement : public ABnfNodeElement
{
public:
    ALittleScriptOpAssignExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOpAssignExprElement() { }

private:
    bool m_flag_PropertyValue = false;
    std::vector<std::shared_ptr<ALittleScriptPropertyValueElement>> m_list_PropertyValue;
public:
    const std::vector<std::shared_ptr<ALittleScriptPropertyValueElement>>& GetPropertyValueList()
    {
        if (m_flag_PropertyValue) return m_list_PropertyValue;
        m_flag_PropertyValue = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(child);
            if (node != nullptr)
                m_list_PropertyValue.push_back(node);
        }
        return m_list_PropertyValue;
    }
private:
    bool m_flag_OpAssign = false;
    std::shared_ptr<ALittleScriptOpAssignElement> m_cache_OpAssign;
public:
    std::shared_ptr<ALittleScriptOpAssignElement> GetOpAssign()
    {
        if (m_flag_OpAssign) return m_cache_OpAssign;
        m_flag_OpAssign = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOpAssignElement>(child);
            if (node != nullptr)
            {
                m_cache_OpAssign = node;
                break;
            }
        }
        return m_cache_OpAssign;
    }
private:
    bool m_flag_ValueStat = false;
    std::shared_ptr<ALittleScriptValueStatElement> m_cache_ValueStat;
public:
    std::shared_ptr<ALittleScriptValueStatElement> GetValueStat()
    {
        if (m_flag_ValueStat) return m_cache_ValueStat;
        m_flag_ValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ValueStat = node;
                break;
            }
        }
        return m_cache_ValueStat;
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

#endif // _ALITTLE_ALittleScriptOpAssignExprElement_H_
