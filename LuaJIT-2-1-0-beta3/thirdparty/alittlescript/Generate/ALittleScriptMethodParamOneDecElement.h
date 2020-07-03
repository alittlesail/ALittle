#ifndef _ALITTLE_ALittleScriptMethodParamOneDecElement_H_
#define _ALITTLE_ALittleScriptMethodParamOneDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodParamTailDecElement;
class ALittleScriptModifierElement;
class ALittleScriptAllTypeElement;
class ALittleScriptMethodParamNameDecElement;

class ALittleScriptMethodParamOneDecElement : public ABnfNodeElement
{
public:
    ALittleScriptMethodParamOneDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptMethodParamOneDecElement() { }

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
    bool m_flag_Modifier = false;
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> m_list_Modifier;
public:
    const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& GetModifierList()
    {
        if (m_flag_Modifier) return m_list_Modifier;
        m_flag_Modifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptModifierElement>(child);
            if (node != nullptr)
                m_list_Modifier.push_back(node);
        }
        return m_list_Modifier;
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
    bool m_flag_MethodParamNameDec = false;
    std::shared_ptr<ALittleScriptMethodParamNameDecElement> m_cache_MethodParamNameDec;
public:
    std::shared_ptr<ALittleScriptMethodParamNameDecElement> GetMethodParamNameDec()
    {
        if (m_flag_MethodParamNameDec) return m_cache_MethodParamNameDec;
        m_flag_MethodParamNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodParamNameDec = node;
                break;
            }
        }
        return m_cache_MethodParamNameDec;
    }
};

#endif // _ALITTLE_ALittleScriptMethodParamOneDecElement_H_
