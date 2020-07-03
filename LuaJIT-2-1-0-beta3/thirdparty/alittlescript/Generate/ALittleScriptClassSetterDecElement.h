#ifndef _ALITTLE_ALittleScriptClassSetterDecElement_H_
#define _ALITTLE_ALittleScriptClassSetterDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptMethodNameDecElement;
class ALittleScriptMethodSetterParamDecElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptClassSetterDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassSetterDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassSetterDecElement() { }

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
    bool m_flag_MethodSetterParamDec = false;
    std::shared_ptr<ALittleScriptMethodSetterParamDecElement> m_cache_MethodSetterParamDec;
public:
    std::shared_ptr<ALittleScriptMethodSetterParamDecElement> GetMethodSetterParamDec()
    {
        if (m_flag_MethodSetterParamDec) return m_cache_MethodSetterParamDec;
        m_flag_MethodSetterParamDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodSetterParamDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodSetterParamDec = node;
                break;
            }
        }
        return m_cache_MethodSetterParamDec;
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
};

#endif // _ALITTLE_ALittleScriptClassSetterDecElement_H_
