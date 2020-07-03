#ifndef _ALITTLE_ALittleScriptClassMethodDecElement_H_
#define _ALITTLE_ALittleScriptClassMethodDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptTemplateDecElement;
class ALittleScriptMethodNameDecElement;
class ALittleScriptMethodParamDecElement;
class ALittleScriptMethodReturnDecElement;
class ALittleScriptMethodBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptClassMethodDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassMethodDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassMethodDecElement() { }

private:
    bool m_flag_TemplateDec = false;
    std::shared_ptr<ALittleScriptTemplateDecElement> m_cache_TemplateDec;
public:
    std::shared_ptr<ALittleScriptTemplateDecElement> GetTemplateDec()
    {
        if (m_flag_TemplateDec) return m_cache_TemplateDec;
        m_flag_TemplateDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptTemplateDecElement>(child);
            if (node != nullptr)
            {
                m_cache_TemplateDec = node;
                break;
            }
        }
        return m_cache_TemplateDec;
    }
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
    bool m_flag_MethodParamDec = false;
    std::shared_ptr<ALittleScriptMethodParamDecElement> m_cache_MethodParamDec;
public:
    std::shared_ptr<ALittleScriptMethodParamDecElement> GetMethodParamDec()
    {
        if (m_flag_MethodParamDec) return m_cache_MethodParamDec;
        m_flag_MethodParamDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodParamDec = node;
                break;
            }
        }
        return m_cache_MethodParamDec;
    }
private:
    bool m_flag_MethodReturnDec = false;
    std::shared_ptr<ALittleScriptMethodReturnDecElement> m_cache_MethodReturnDec;
public:
    std::shared_ptr<ALittleScriptMethodReturnDecElement> GetMethodReturnDec()
    {
        if (m_flag_MethodReturnDec) return m_cache_MethodReturnDec;
        m_flag_MethodReturnDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptMethodReturnDecElement>(child);
            if (node != nullptr)
            {
                m_cache_MethodReturnDec = node;
                break;
            }
        }
        return m_cache_MethodReturnDec;
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

#endif // _ALITTLE_ALittleScriptClassMethodDecElement_H_
