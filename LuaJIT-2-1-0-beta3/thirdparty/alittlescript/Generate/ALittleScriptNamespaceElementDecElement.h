#ifndef _ALITTLE_ALittleScriptNamespaceElementDecElement_H_
#define _ALITTLE_ALittleScriptNamespaceElementDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptModifierElement;
class ALittleScriptEnumDecElement;
class ALittleScriptStructDecElement;
class ALittleScriptOpAssignExprElement;
class ALittleScriptGlobalMethodDecElement;
class ALittleScriptClassDecElement;
class ALittleScriptUsingDecElement;
class ALittleScriptInstanceDecElement;

class ALittleScriptNamespaceElementDecElement : public ABnfNodeElement
{
public:
    ALittleScriptNamespaceElementDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptNamespaceElementDecElement() { }

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
    bool m_flag_EnumDec = false;
    std::shared_ptr<ALittleScriptEnumDecElement> m_cache_EnumDec;
public:
    std::shared_ptr<ALittleScriptEnumDecElement> GetEnumDec()
    {
        if (m_flag_EnumDec) return m_cache_EnumDec;
        m_flag_EnumDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptEnumDecElement>(child);
            if (node != nullptr)
            {
                m_cache_EnumDec = node;
                break;
            }
        }
        return m_cache_EnumDec;
    }
private:
    bool m_flag_StructDec = false;
    std::shared_ptr<ALittleScriptStructDecElement> m_cache_StructDec;
public:
    std::shared_ptr<ALittleScriptStructDecElement> GetStructDec()
    {
        if (m_flag_StructDec) return m_cache_StructDec;
        m_flag_StructDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructDecElement>(child);
            if (node != nullptr)
            {
                m_cache_StructDec = node;
                break;
            }
        }
        return m_cache_StructDec;
    }
private:
    bool m_flag_OpAssignExpr = false;
    std::shared_ptr<ALittleScriptOpAssignExprElement> m_cache_OpAssignExpr;
public:
    std::shared_ptr<ALittleScriptOpAssignExprElement> GetOpAssignExpr()
    {
        if (m_flag_OpAssignExpr) return m_cache_OpAssignExpr;
        m_flag_OpAssignExpr = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptOpAssignExprElement>(child);
            if (node != nullptr)
            {
                m_cache_OpAssignExpr = node;
                break;
            }
        }
        return m_cache_OpAssignExpr;
    }
private:
    bool m_flag_GlobalMethodDec = false;
    std::shared_ptr<ALittleScriptGlobalMethodDecElement> m_cache_GlobalMethodDec;
public:
    std::shared_ptr<ALittleScriptGlobalMethodDecElement> GetGlobalMethodDec()
    {
        if (m_flag_GlobalMethodDec) return m_cache_GlobalMethodDec;
        m_flag_GlobalMethodDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(child);
            if (node != nullptr)
            {
                m_cache_GlobalMethodDec = node;
                break;
            }
        }
        return m_cache_GlobalMethodDec;
    }
private:
    bool m_flag_ClassDec = false;
    std::shared_ptr<ALittleScriptClassDecElement> m_cache_ClassDec;
public:
    std::shared_ptr<ALittleScriptClassDecElement> GetClassDec()
    {
        if (m_flag_ClassDec) return m_cache_ClassDec;
        m_flag_ClassDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassDec = node;
                break;
            }
        }
        return m_cache_ClassDec;
    }
private:
    bool m_flag_UsingDec = false;
    std::shared_ptr<ALittleScriptUsingDecElement> m_cache_UsingDec;
public:
    std::shared_ptr<ALittleScriptUsingDecElement> GetUsingDec()
    {
        if (m_flag_UsingDec) return m_cache_UsingDec;
        m_flag_UsingDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptUsingDecElement>(child);
            if (node != nullptr)
            {
                m_cache_UsingDec = node;
                break;
            }
        }
        return m_cache_UsingDec;
    }
private:
    bool m_flag_InstanceDec = false;
    std::shared_ptr<ALittleScriptInstanceDecElement> m_cache_InstanceDec;
public:
    std::shared_ptr<ALittleScriptInstanceDecElement> GetInstanceDec()
    {
        if (m_flag_InstanceDec) return m_cache_InstanceDec;
        m_flag_InstanceDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptInstanceDecElement>(child);
            if (node != nullptr)
            {
                m_cache_InstanceDec = node;
                break;
            }
        }
        return m_cache_InstanceDec;
    }
};

#endif // _ALITTLE_ALittleScriptNamespaceElementDecElement_H_
