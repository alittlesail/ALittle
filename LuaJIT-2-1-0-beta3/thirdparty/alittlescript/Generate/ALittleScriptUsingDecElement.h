#ifndef _ALITTLE_ALittleScriptUsingDecElement_H_
#define _ALITTLE_ALittleScriptUsingDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptUsingNameDecElement;
class ALittleScriptAllTypeElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptUsingDecElement : public ABnfNodeElement
{
public:
    ALittleScriptUsingDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptUsingDecElement() { }

private:
    bool m_flag_UsingNameDec = false;
    std::shared_ptr<ALittleScriptUsingNameDecElement> m_cache_UsingNameDec;
public:
    std::shared_ptr<ALittleScriptUsingNameDecElement> GetUsingNameDec()
    {
        if (m_flag_UsingNameDec) return m_cache_UsingNameDec;
        m_flag_UsingNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptUsingNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_UsingNameDec = node;
                break;
            }
        }
        return m_cache_UsingNameDec;
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

#endif // _ALITTLE_ALittleScriptUsingDecElement_H_
