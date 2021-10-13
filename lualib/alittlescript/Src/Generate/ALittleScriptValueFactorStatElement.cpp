#include "ALittleScriptValueFactorStatElement.h"

#include "ALittleScriptWrapValueStatElement.h"
#include "ALittleScriptMethodParamTailDecElement.h"
#include "ALittleScriptConstValueElement.h"
#include "ALittleScriptReflectValueElement.h"
#include "ALittleScriptPathsValueElement.h"
#include "ALittleScriptPropertyValueElement.h"
#include "ALittleScriptCoroutineStatElement.h"

std::shared_ptr<ALittleScriptWrapValueStatElement> ALittleScriptValueFactorStatElement::GetWrapValueStat()
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
std::shared_ptr<ALittleScriptMethodParamTailDecElement> ALittleScriptValueFactorStatElement::GetMethodParamTailDec()
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
std::shared_ptr<ALittleScriptConstValueElement> ALittleScriptValueFactorStatElement::GetConstValue()
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
std::shared_ptr<ALittleScriptReflectValueElement> ALittleScriptValueFactorStatElement::GetReflectValue()
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
std::shared_ptr<ALittleScriptPathsValueElement> ALittleScriptValueFactorStatElement::GetPathsValue()
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
std::shared_ptr<ALittleScriptPropertyValueElement> ALittleScriptValueFactorStatElement::GetPropertyValue()
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
std::shared_ptr<ALittleScriptCoroutineStatElement> ALittleScriptValueFactorStatElement::GetCoroutineStat()
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

