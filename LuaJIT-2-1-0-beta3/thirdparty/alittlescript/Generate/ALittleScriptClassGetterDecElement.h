#ifndef _ALITTLE_ALittleScriptClassGetterDecElement_H_
#define _ALITTLE_ALittleScriptClassGetterDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodNameDecElement;
class ALittleScriptMethodGetterParamDecElement;
class ALittleScriptAllTypeElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;
class ALittleScriptStringElement;

class ALittleScriptClassGetterDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassGetterDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassGetterDecElement() { }

private:
    bool m_flag_MethodNameDec = false;
    std::shared_ptr<ALittleScriptMethodNameDecElement> m_cache_MethodNameDec;
public:
    std::shared_ptr<ALittleScriptMethodNameDecElement> GetMethodNameDec()
    {
        if (m_flag_MethodNameDec) return m_cache_MethodNameDec;
        m_flag_MethodNameDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodNameDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodNameDec = node;
                break;
            }
        }
        return m_cache_MethodNameDec;
    }
private:
    bool m_flag_MethodGetterParamDec = false;
    std::shared_ptr<ALittleScriptMethodGetterParamDecElement> m_cache_MethodGetterParamDec;
public:
    std::shared_ptr<ALittleScriptMethodGetterParamDecElement> GetMethodGetterParamDec()
    {
        if (m_flag_MethodGetterParamDec) return m_cache_MethodGetterParamDec;
        m_flag_MethodGetterParamDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodGetterParamDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodGetterParamDec = node;
                break;
            }
        }
        return m_cache_MethodGetterParamDec;
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
    bool m_flag_MethodBodyDec = false;
    std::shared_ptr<ALittleScriptMethodBodyDecElement> m_cache_MethodBodyDec;
public:
    std::shared_ptr<ALittleScriptMethodBodyDecElement> GetMethodBodyDec()
    {
        if (m_flag_MethodBodyDec) return m_cache_MethodBodyDec;
        m_flag_MethodBodyDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodBodyDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodBodyDec = node;
                break;
            }
        }
        return m_cache_MethodBodyDec;
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

#endif // _ALITTLE_ALittleScriptClassGetterDecElement_H_
