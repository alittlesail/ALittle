#ifndef _ALITTLE_ALittleScriptStructVarDecElement_H_
#define _ALITTLE_ALittleScriptStructVarDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptStructVarNameDecElement;
class ALittleScriptStringElement;

class ALittleScriptStructVarDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructVarDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructVarDecElement() { }

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
    bool m_flag_StructVarNameDec = false;
    std::shared_ptr<ALittleScriptStructVarNameDecElement> m_cache_StructVarNameDec;
public:
    std::shared_ptr<ALittleScriptStructVarNameDecElement> GetStructVarNameDec()
    {
        if (m_flag_StructVarNameDec) return m_cache_StructVarNameDec;
        m_flag_StructVarNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructVarNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_StructVarNameDec = node;
                break;
            }
        }
        return m_cache_StructVarNameDec;
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

#endif // _ALITTLE_ALittleScriptStructVarDecElement_H_
