#ifndef _ALITTLE_ALittleScriptForPairDecElement_H_
#define _ALITTLE_ALittleScriptForPairDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptVarAssignNameDecElement;
class ALittleScriptAllTypeElement;
class ALittleScriptStringElement;

class ALittleScriptForPairDecElement : public ABnfNodeElement
{
public:
    ALittleScriptForPairDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptForPairDecElement() { }

private:
    bool m_flag_VarAssignNameDec = false;
    std::shared_ptr<ALittleScriptVarAssignNameDecElement> m_cache_VarAssignNameDec;
public:
    std::shared_ptr<ALittleScriptVarAssignNameDecElement> GetVarAssignNameDec()
    {
        if (m_flag_VarAssignNameDec) return m_cache_VarAssignNameDec;
        m_flag_VarAssignNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_VarAssignNameDec = node;
                break;
            }
        }
        return m_cache_VarAssignNameDec;
    }
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

#endif // _ALITTLE_ALittleScriptForPairDecElement_H_
