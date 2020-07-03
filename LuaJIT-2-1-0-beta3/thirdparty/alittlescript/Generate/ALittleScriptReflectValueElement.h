#ifndef _ALITTLE_ALittleScriptReflectValueElement_H_
#define _ALITTLE_ALittleScriptReflectValueElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptReflectCustomTypeElement;
class ALittleScriptReflectValueStatElement;
class ALittleScriptKeyElement;

class ALittleScriptReflectValueElement : public ABnfNodeElement
{
public:
    ALittleScriptReflectValueElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptReflectValueElement() { }

private:
    bool m_flag_ReflectCustomType = false;
    std::shared_ptr<ALittleScriptReflectCustomTypeElement> m_cache_ReflectCustomType;
public:
    std::shared_ptr<ALittleScriptReflectCustomTypeElement> GetReflectCustomType()
    {
        if (m_flag_ReflectCustomType) return m_cache_ReflectCustomType;
        m_flag_ReflectCustomType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptReflectCustomTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_ReflectCustomType = node;
                break;
            }
        }
        return m_cache_ReflectCustomType;
    }
private:
    bool m_flag_ReflectValueStat = false;
    std::shared_ptr<ALittleScriptReflectValueStatElement> m_cache_ReflectValueStat;
public:
    std::shared_ptr<ALittleScriptReflectValueStatElement> GetReflectValueStat()
    {
        if (m_flag_ReflectValueStat) return m_cache_ReflectValueStat;
        m_flag_ReflectValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptReflectValueStatElement>(child);
            if (node != nullptr)
            {
                m_cache_ReflectValueStat = node;
                break;
            }
        }
        return m_cache_ReflectValueStat;
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
};

#endif // _ALITTLE_ALittleScriptReflectValueElement_H_
