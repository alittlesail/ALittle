#ifndef _ALITTLE_ALittleScriptStructDecElement_H_
#define _ALITTLE_ALittleScriptStructDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptStructNameDecElement;
class ALittleScriptStructExtendsDecElement;
class ALittleScriptStructBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptStructDecElement : public ABnfNodeElement
{
public:
    ALittleScriptStructDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptStructDecElement() { }

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
    bool m_flag_StructExtendsDec = false;
    std::shared_ptr<ALittleScriptStructExtendsDecElement> m_cache_StructExtendsDec;
public:
    std::shared_ptr<ALittleScriptStructExtendsDecElement> GetStructExtendsDec()
    {
        if (m_flag_StructExtendsDec) return m_cache_StructExtendsDec;
        m_flag_StructExtendsDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructExtendsDecElement>(child);
            if (node != nullptr)
            {
                m_cache_StructExtendsDec = node;
                break;
            }
        }
        return m_cache_StructExtendsDec;
    }
private:
    bool m_flag_StructBodyDec = false;
    std::shared_ptr<ALittleScriptStructBodyDecElement> m_cache_StructBodyDec;
public:
    std::shared_ptr<ALittleScriptStructBodyDecElement> GetStructBodyDec()
    {
        if (m_flag_StructBodyDec) return m_cache_StructBodyDec;
        m_flag_StructBodyDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptStructBodyDecElement>(child);
            if (node != nullptr)
            {
                m_cache_StructBodyDec = node;
                break;
            }
        }
        return m_cache_StructBodyDec;
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

#endif // _ALITTLE_ALittleScriptStructDecElement_H_
