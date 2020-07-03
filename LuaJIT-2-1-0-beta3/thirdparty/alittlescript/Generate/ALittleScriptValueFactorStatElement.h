#ifndef _ALITTLE_ALittleScriptValueFactorStatElement_H_
#define _ALITTLE_ALittleScriptValueFactorStatElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptWrapValueStatElement;
class ALittleScriptMethodParamTailDecElement;
class ALittleScriptConstValueElement;
class ALittleScriptReflectValueElement;
class ALittleScriptPathsValueElement;
class ALittleScriptPropertyValueElement;
class ALittleScriptCoroutineStatElement;

class ALittleScriptValueFactorStatElement : public ABnfNodeElement
{
public:
    ALittleScriptValueFactorStatElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptValueFactorStatElement() { }

private:
    bool m_flag_WrapValueStat = false;
    std::shared_ptr<ALittleScriptWrapValueStatElement> m_cache_WrapValueStat;
public:
    std::shared_ptr<ALittleScriptWrapValueStatElement> GetWrapValueStat()
    {
        if (m_flag_WrapValueStat) return m_cache_WrapValueStat;
        m_flag_WrapValueStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptWrapValueStatElement>(child);
            if (node != nullptr)
            {
                m_cache_WrapValueStat = node;
                break;
            }
        }
        return m_cache_WrapValueStat;
    }
private:
    bool m_flag_MethodParamTailDec = false;
    std::shared_ptr<ALittleScriptMethodParamTailDecElement> m_cache_MethodParamTailDec;
public:
    std::shared_ptr<ALittleScriptMethodParamTailDecElement> GetMethodParamTailDec()
    {
        if (m_flag_MethodParamTailDec) return m_cache_MethodParamTailDec;
        m_flag_MethodParamTailDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamTailDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodParamTailDec = node;
                break;
            }
        }
        return m_cache_MethodParamTailDec;
    }
private:
    bool m_flag_ConstValue = false;
    std::shared_ptr<ALittleScriptConstValueElement> m_cache_ConstValue;
public:
    std::shared_ptr<ALittleScriptConstValueElement> GetConstValue()
    {
        if (m_flag_ConstValue) return m_cache_ConstValue;
        m_flag_ConstValue = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptConstValueElement>(child);
            if (node != nullptr)
            {
                m_cache_ConstValue = node;
                break;
            }
        }
        return m_cache_ConstValue;
    }
private:
    bool m_flag_ReflectValue = false;
    std::shared_ptr<ALittleScriptReflectValueElement> m_cache_ReflectValue;
public:
    std::shared_ptr<ALittleScriptReflectValueElement> GetReflectValue()
    {
        if (m_flag_ReflectValue) return m_cache_ReflectValue;
        m_flag_ReflectValue = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptReflectValueElement>(child);
            if (node != nullptr)
            {
                m_cache_ReflectValue = node;
                break;
            }
        }
        return m_cache_ReflectValue;
    }
private:
    bool m_flag_PathsValue = false;
    std::shared_ptr<ALittleScriptPathsValueElement> m_cache_PathsValue;
public:
    std::shared_ptr<ALittleScriptPathsValueElement> GetPathsValue()
    {
        if (m_flag_PathsValue) return m_cache_PathsValue;
        m_flag_PathsValue = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPathsValueElement>(child);
            if (node != nullptr)
            {
                m_cache_PathsValue = node;
                break;
            }
        }
        return m_cache_PathsValue;
    }
private:
    bool m_flag_PropertyValue = false;
    std::shared_ptr<ALittleScriptPropertyValueElement> m_cache_PropertyValue;
public:
    std::shared_ptr<ALittleScriptPropertyValueElement> GetPropertyValue()
    {
        if (m_flag_PropertyValue) return m_cache_PropertyValue;
        m_flag_PropertyValue = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(child);
            if (node != nullptr)
            {
                m_cache_PropertyValue = node;
                break;
            }
        }
        return m_cache_PropertyValue;
    }
private:
    bool m_flag_CoroutineStat = false;
    std::shared_ptr<ALittleScriptCoroutineStatElement> m_cache_CoroutineStat;
public:
    std::shared_ptr<ALittleScriptCoroutineStatElement> GetCoroutineStat()
    {
        if (m_flag_CoroutineStat) return m_cache_CoroutineStat;
        m_flag_CoroutineStat = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCoroutineStatElement>(child);
            if (node != nullptr)
            {
                m_cache_CoroutineStat = node;
                break;
            }
        }
        return m_cache_CoroutineStat;
    }
};

#endif // _ALITTLE_ALittleScriptValueFactorStatElement_H_
