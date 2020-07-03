#ifndef _ALITTLE_ALittleScriptGenericFunctorTypeElement_H_
#define _ALITTLE_ALittleScriptGenericFunctorTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeConstElement;
class ALittleScriptGenericFunctorReturnTypeElement;
class ALittleScriptCoroutineModifierElement;
class ALittleScriptGenericFunctorParamTypeElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptGenericFunctorTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericFunctorTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericFunctorTypeElement() { }

private:
    bool m_flag_AllTypeConst = false;
    std::shared_ptr<ALittleScriptAllTypeConstElement> m_cache_AllTypeConst;
public:
    std::shared_ptr<ALittleScriptAllTypeConstElement> GetAllTypeConst()
    {
        if (m_flag_AllTypeConst) return m_cache_AllTypeConst;
        m_flag_AllTypeConst = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeConstElement>(child);
            if (node != nullptr)
            {
                m_cache_AllTypeConst = node;
                break;
            }
        }
        return m_cache_AllTypeConst;
    }
private:
    bool m_flag_GenericFunctorReturnType = false;
    std::shared_ptr<ALittleScriptGenericFunctorReturnTypeElement> m_cache_GenericFunctorReturnType;
public:
    std::shared_ptr<ALittleScriptGenericFunctorReturnTypeElement> GetGenericFunctorReturnType()
    {
        if (m_flag_GenericFunctorReturnType) return m_cache_GenericFunctorReturnType;
        m_flag_GenericFunctorReturnType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorReturnTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_GenericFunctorReturnType = node;
                break;
            }
        }
        return m_cache_GenericFunctorReturnType;
    }
private:
    bool m_flag_CoroutineModifier = false;
    std::shared_ptr<ALittleScriptCoroutineModifierElement> m_cache_CoroutineModifier;
public:
    std::shared_ptr<ALittleScriptCoroutineModifierElement> GetCoroutineModifier()
    {
        if (m_flag_CoroutineModifier) return m_cache_CoroutineModifier;
        m_flag_CoroutineModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCoroutineModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_CoroutineModifier = node;
                break;
            }
        }
        return m_cache_CoroutineModifier;
    }
private:
    bool m_flag_GenericFunctorParamType = false;
    std::shared_ptr<ALittleScriptGenericFunctorParamTypeElement> m_cache_GenericFunctorParamType;
public:
    std::shared_ptr<ALittleScriptGenericFunctorParamTypeElement> GetGenericFunctorParamType()
    {
        if (m_flag_GenericFunctorParamType) return m_cache_GenericFunctorParamType;
        m_flag_GenericFunctorParamType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorParamTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_GenericFunctorParamType = node;
                break;
            }
        }
        return m_cache_GenericFunctorParamType;
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

#endif // _ALITTLE_ALittleScriptGenericFunctorTypeElement_H_
