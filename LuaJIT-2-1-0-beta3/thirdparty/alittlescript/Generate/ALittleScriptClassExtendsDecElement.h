#ifndef _ALITTLE_ALittleScriptClassExtendsDecElement_H_
#define _ALITTLE_ALittleScriptClassExtendsDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptNamespaceNameDecElement;
class ALittleScriptClassNameDecElement;
class ALittleScriptStringElement;

class ALittleScriptClassExtendsDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassExtendsDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassExtendsDecElement() { }

private:
    bool m_flag_NamespaceNameDec = false;
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> m_cache_NamespaceNameDec;
public:
    std::shared_ptr<ALittleScriptNamespaceNameDecElement> GetNamespaceNameDec()
    {
        if (m_flag_NamespaceNameDec) return m_cache_NamespaceNameDec;
        m_flag_NamespaceNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptNamespaceNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_NamespaceNameDec = node;
                break;
            }
        }
        return m_cache_NamespaceNameDec;
    }
private:
    bool m_flag_ClassNameDec = false;
    std::shared_ptr<ALittleScriptClassNameDecElement> m_cache_ClassNameDec;
public:
    std::shared_ptr<ALittleScriptClassNameDecElement> GetClassNameDec()
    {
        if (m_flag_ClassNameDec) return m_cache_ClassNameDec;
        m_flag_ClassNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassNameDec = node;
                break;
            }
        }
        return m_cache_ClassNameDec;
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

#endif // _ALITTLE_ALittleScriptClassExtendsDecElement_H_
