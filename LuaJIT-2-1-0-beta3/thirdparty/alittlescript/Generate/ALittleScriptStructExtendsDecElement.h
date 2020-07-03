#ifndef _ALITTLE_ALittleScriptStructExtendsDecElement_H_
#define _ALITTLE_ALittleScriptStructExtendsDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptNamespaceNameDecElement;
class ALittleScriptStructNameDecElement;
class ALittleScriptStringElement;

class ALittleScriptStructExtendsDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructExtendsDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructExtendsDecElement() { }

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
    bool m_flag_StructNameDec = false;
    std::shared_ptr<ALittleScriptStructNameDecElement> m_cache_StructNameDec;
public:
    std::shared_ptr<ALittleScriptStructNameDecElement> GetStructNameDec()
    {
        if (m_flag_StructNameDec) return m_cache_StructNameDec;
        m_flag_StructNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_StructNameDec = node;
                break;
            }
        }
        return m_cache_StructNameDec;
    }
private:
    bool m_flag_String = false;
    std::vector<std::shared_ptr<ALittleScriptStringElement>> m_list_String;
public:
    const std::vector<std::shared_ptr<ALittleScriptStringElement>>& GetStringList()
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

#endif // _ALITTLE_ALittleScriptStructExtendsDecElement_H_
