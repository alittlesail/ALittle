#ifndef _ALITTLE_ALittleScriptGenericTypeElement_H_
#define _ALITTLE_ALittleScriptGenericTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptGenericListTypeElement;
class ALittleScriptGenericMapTypeElement;
class ALittleScriptGenericFunctorTypeElement;

class ALittleScriptGenericTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptGenericTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptGenericTypeElement() { }

private:
    bool m_flag_GenericListType = false;
    std::shared_ptr<ALittleScriptGenericListTypeElement> m_cache_GenericListType;
public:
    std::shared_ptr<ALittleScriptGenericListTypeElement> GetGenericListType()
    {
        if (m_flag_GenericListType) return m_cache_GenericListType;
        m_flag_GenericListType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericListTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_GenericListType = node;
                break;
            }
        }
        return m_cache_GenericListType;
    }
private:
    bool m_flag_GenericMapType = false;
    std::shared_ptr<ALittleScriptGenericMapTypeElement> m_cache_GenericMapType;
public:
    std::shared_ptr<ALittleScriptGenericMapTypeElement> GetGenericMapType()
    {
        if (m_flag_GenericMapType) return m_cache_GenericMapType;
        m_flag_GenericMapType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericMapTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_GenericMapType = node;
                break;
            }
        }
        return m_cache_GenericMapType;
    }
private:
    bool m_flag_GenericFunctorType = false;
    std::shared_ptr<ALittleScriptGenericFunctorTypeElement> m_cache_GenericFunctorType;
public:
    std::shared_ptr<ALittleScriptGenericFunctorTypeElement> GetGenericFunctorType()
    {
        if (m_flag_GenericFunctorType) return m_cache_GenericFunctorType;
        m_flag_GenericFunctorType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGenericFunctorTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_GenericFunctorType = node;
                break;
            }
        }
        return m_cache_GenericFunctorType;
    }
};

#endif // _ALITTLE_ALittleScriptGenericTypeElement_H_
