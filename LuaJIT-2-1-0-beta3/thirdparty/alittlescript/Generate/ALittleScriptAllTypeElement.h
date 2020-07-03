#ifndef _ALITTLE_ALittleScriptAllTypeElement_H_
#define _ALITTLE_ALittleScriptAllTypeElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeConstElement;
class ALittleScriptPrimitiveTypeElement;
class ALittleScriptCustomTypeElement;
class ALittleScriptGenericTypeElement;

class ALittleScriptAllTypeElement : public ABnfNodeElement
{
public:
    ALittleScriptAllTypeElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptAllTypeElement() { }

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
    bool m_flag_PrimitiveType = false;
    std::shared_ptr<ALittleScriptPrimitiveTypeElement> m_cache_PrimitiveType;
public:
    std::shared_ptr<ALittleScriptPrimitiveTypeElement> GetPrimitiveType()
    {
        if (m_flag_PrimitiveType) return m_cache_PrimitiveType;
        m_flag_PrimitiveType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptPrimitiveTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_PrimitiveType = node;
                break;
            }
        }
        return m_cache_PrimitiveType;
    }
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
};

#endif // _ALITTLE_ALittleScriptAllTypeElement_H_
