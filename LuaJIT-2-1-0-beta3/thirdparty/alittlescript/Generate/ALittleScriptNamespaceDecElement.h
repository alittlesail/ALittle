#ifndef _ALITTLE_ALittleScriptNamespaceDecElement_H_
#define _ALITTLE_ALittleScriptNamespaceDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptModifierElement;
class ALittleScriptNamespaceElementDecElement;
class ALittleScriptNamespaceNameDecElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptNamespaceDecElement : public ABnfNodeElement
{
public:
    ALittleScriptNamespaceDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptNamespaceDecElement() { }

private:
    bool m_flag_Modifier = false;
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> m_list_Modifier;
public:
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> GetModifierList()
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
    bool m_flag_NamespaceElementDec = false;
    std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>> m_list_NamespaceElementDec;
public:
    std::vector<std::shared_ptr<ALittleScriptNamespaceElementDecElement>> GetNamespaceElementDecList()
    {
        if (m_flag_NamespaceElementDec) return m_list_NamespaceElementDec;
        m_flag_NamespaceElementDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(child);
            if (node != nullptr)
                m_list_NamespaceElementDec.push_back(node);
        }
        return m_list_NamespaceElementDec;
    }
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

#endif // _ALITTLE_ALittleScriptNamespaceDecElement_H_
