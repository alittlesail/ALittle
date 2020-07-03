#ifndef _ALITTLE_ALittleScriptEnumDecElement_H_
#define _ALITTLE_ALittleScriptEnumDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptEnumNameDecElement;
class ALittleScriptEnumBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptEnumDecElement : public ABnfNodeElement
{
public:
    ALittleScriptEnumDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptEnumDecElement() { }

private:
    bool m_flag_EnumNameDec = false;
    std::shared_ptr<ALittleScriptEnumNameDecElement> m_cache_EnumNameDec;
public:
    std::shared_ptr<ALittleScriptEnumNameDecElement> GetEnumNameDec()
    {
        if (m_flag_EnumNameDec) return m_cache_EnumNameDec;
        m_flag_EnumNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_EnumNameDec = node;
                break;
            }
        }
        return m_cache_EnumNameDec;
    }
private:
    bool m_flag_EnumBodyDec = false;
    std::shared_ptr<ALittleScriptEnumBodyDecElement> m_cache_EnumBodyDec;
public:
    std::shared_ptr<ALittleScriptEnumBodyDecElement> GetEnumBodyDec()
    {
        if (m_flag_EnumBodyDec) return m_cache_EnumBodyDec;
        m_flag_EnumBodyDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptEnumBodyDecElement>(child);
            if (node != nullptr)
            {
                m_cache_EnumBodyDec = node;
                break;
            }
        }
        return m_cache_EnumBodyDec;
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
};

#endif // _ALITTLE_ALittleScriptEnumDecElement_H_
