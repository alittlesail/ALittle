#ifndef _ALITTLE_ALittleScriptOpNewStatElement_H_
#define _ALITTLE_ALittleScriptOpNewStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptCustomTypeElement;
class ALittleScriptGenericTypeElement;
class ALittleScriptValueStatElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptOpNewStatElement : public ABnfNodeElement
{
public:
    ALittleScriptOpNewStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptOpNewStatElement() { }

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
    bool m_flag_GenericType = false;
    std::shared_ptr<ALittleScriptGenericTypeElement> m_cache_GenericType;
public:
    std::shared_ptr<ALittleScriptGenericTypeElement> GetGenericType()
    {
        if (m_flag_GenericType) return m_cache_GenericType;
        m_flag_GenericType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_GenericType = node;
                break;
            }
        }
        return m_cache_GenericType;
    }
private:
    bool m_flag_ValueStat = false;
    std::vector<std::shared_ptr<ALittleScriptValueStatElement>> m_list_ValueStat;
public:
    std::vector<std::shared_ptr<ALittleScriptValueStatElement>> GetValueStatList()
    {
        if (m_flag_ValueStat) return m_list_ValueStat;
        m_flag_ValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
            if (node != nullptr)
                m_list_ValueStat.push_back(node);
        }
        return m_list_ValueStat;
    }
private:
    bool m_flag_Key = false;
    std::shared_ptr<ALittleScriptKeyElement> m_cache_Key;
public:
    std::shared_ptr<ALittleScriptKeyElement> GetKey()
    {
        if (m_flag_Key) return m_cache_Key;
        m_flag_Key = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptKeyElement>(child);
            if (node != nullptr)
            {
                m_cache_Key = node;
                break;
            }
        }
        return m_cache_Key;
    }
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    std::vector<std::shared_ptr<ALittleScriptStringElement>> GetStringList()
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

#endif // _ALITTLE_ALittleScriptOpNewStatElement_H_
