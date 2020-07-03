#ifndef _ALITTLE_ALittleScriptClassElementDecElement_H_
#define _ALITTLE_ALittleScriptClassElementDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptModifierElement;
class ALittleScriptClassSetterDecElement;
class ALittleScriptClassCtorDecElement;
class ALittleScriptClassStaticDecElement;
class ALittleScriptClassGetterDecElement;
class ALittleScriptClassVarDecElement;
class ALittleScriptClassMethodDecElement;

class ALittleScriptClassElementDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassElementDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassElementDecElement() { }

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
    bool m_flag_ClassSetterDec = false;
    std::shared_ptr<ALittleScriptClassSetterDecElement> m_cache_ClassSetterDec;
public:
    std::shared_ptr<ALittleScriptClassSetterDecElement> GetClassSetterDec()
    {
        if (m_flag_ClassSetterDec) return m_cache_ClassSetterDec;
        m_flag_ClassSetterDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassSetterDec = node;
                break;
            }
        }
        return m_cache_ClassSetterDec;
    }
private:
    bool m_flag_ClassCtorDec = false;
    std::shared_ptr<ALittleScriptClassCtorDecElement> m_cache_ClassCtorDec;
public:
    std::shared_ptr<ALittleScriptClassCtorDecElement> GetClassCtorDec()
    {
        if (m_flag_ClassCtorDec) return m_cache_ClassCtorDec;
        m_flag_ClassCtorDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassCtorDec = node;
                break;
            }
        }
        return m_cache_ClassCtorDec;
    }
private:
    bool m_flag_ClassStaticDec = false;
    std::shared_ptr<ALittleScriptClassStaticDecElement> m_cache_ClassStaticDec;
public:
    std::shared_ptr<ALittleScriptClassStaticDecElement> GetClassStaticDec()
    {
        if (m_flag_ClassStaticDec) return m_cache_ClassStaticDec;
        m_flag_ClassStaticDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassStaticDec = node;
                break;
            }
        }
        return m_cache_ClassStaticDec;
    }
private:
    bool m_flag_ClassGetterDec = false;
    std::shared_ptr<ALittleScriptClassGetterDecElement> m_cache_ClassGetterDec;
public:
    std::shared_ptr<ALittleScriptClassGetterDecElement> GetClassGetterDec()
    {
        if (m_flag_ClassGetterDec) return m_cache_ClassGetterDec;
        m_flag_ClassGetterDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassGetterDec = node;
                break;
            }
        }
        return m_cache_ClassGetterDec;
    }
private:
    bool m_flag_ClassVarDec = false;
    std::shared_ptr<ALittleScriptClassVarDecElement> m_cache_ClassVarDec;
public:
    std::shared_ptr<ALittleScriptClassVarDecElement> GetClassVarDec()
    {
        if (m_flag_ClassVarDec) return m_cache_ClassVarDec;
        m_flag_ClassVarDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassVarDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassVarDec = node;
                break;
            }
        }
        return m_cache_ClassVarDec;
    }
private:
    bool m_flag_ClassMethodDec = false;
    std::shared_ptr<ALittleScriptClassMethodDecElement> m_cache_ClassMethodDec;
public:
    std::shared_ptr<ALittleScriptClassMethodDecElement> GetClassMethodDec()
    {
        if (m_flag_ClassMethodDec) return m_cache_ClassMethodDec;
        m_flag_ClassMethodDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassMethodDec = node;
                break;
            }
        }
        return m_cache_ClassMethodDec;
    }
};

#endif // _ALITTLE_ALittleScriptClassElementDecElement_H_
