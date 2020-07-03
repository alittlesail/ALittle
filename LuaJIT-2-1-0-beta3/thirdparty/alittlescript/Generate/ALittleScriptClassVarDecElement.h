#ifndef _ALITTLE_ALittleScriptClassVarDecElement_H_
#define _ALITTLE_ALittleScriptClassVarDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptClassVarNameDecElement;
class ALittleScriptClassVarValueDecElement;
class ALittleScriptStringElement;

class ALittleScriptClassVarDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassVarDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassVarDecElement() { }

private:
    bool m_flag_AllType = false;
    std::shared_ptr<ALittleScriptAllTypeElement> m_cache_AllType;
public:
    std::shared_ptr<ALittleScriptAllTypeElement> GetAllType()
    {
        if (m_flag_AllType) return m_cache_AllType;
        m_flag_AllType = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptAllTypeElement>(child);
            if (node != nullptr)
            {
                m_cache_AllType = node;
                break;
            }
        }
        return m_cache_AllType;
    }
private:
    bool m_flag_ClassVarNameDec = false;
    std::shared_ptr<ALittleScriptClassVarNameDecElement> m_cache_ClassVarNameDec;
public:
    std::shared_ptr<ALittleScriptClassVarNameDecElement> GetClassVarNameDec()
    {
        if (m_flag_ClassVarNameDec) return m_cache_ClassVarNameDec;
        m_flag_ClassVarNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassVarNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassVarNameDec = node;
                break;
            }
        }
        return m_cache_ClassVarNameDec;
    }
private:
    bool m_flag_ClassVarValueDec = false;
    std::shared_ptr<ALittleScriptClassVarValueDecElement> m_cache_ClassVarValueDec;
public:
    std::shared_ptr<ALittleScriptClassVarValueDecElement> GetClassVarValueDec()
    {
        if (m_flag_ClassVarValueDec) return m_cache_ClassVarValueDec;
        m_flag_ClassVarValueDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassVarValueDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassVarValueDec = node;
                break;
            }
        }
        return m_cache_ClassVarValueDec;
    }
private:
    bool m_flag_String = false;
    std::shared_ptr<ALittleScriptStringElement> m_cache_String;
public:
    std::shared_ptr<ALittleScriptStringElement> GetString()
    {
        if (m_flag_String) return m_cache_String;
        m_flag_String = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStringElement>(child);
            if (node != nullptr)
            {
                m_cache_String = node;
                break;
            }
        }
        return m_cache_String;
    }
};

#endif // _ALITTLE_ALittleScriptClassVarDecElement_H_
