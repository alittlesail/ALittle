#ifndef _ALITTLE_ALittleScriptClassDecElement_H_
#define _ALITTLE_ALittleScriptClassDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptClassExtendsDecElement;
class ALittleScriptClassNameDecElement;
class ALittleScriptTemplateDecElement;
class ALittleScriptClassBodyDecElement;
class ALittleScriptKeyElement;

class ALittleScriptClassDecElement : public ABnfNodeElement
{
public:
    ALittleScriptClassDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptClassDecElement() { }

private:
    bool m_flag_ClassExtendsDec = false;
    std::shared_ptr<ALittleScriptClassExtendsDecElement> m_cache_ClassExtendsDec;
public:
    std::shared_ptr<ALittleScriptClassExtendsDecElement> GetClassExtendsDec()
    {
        if (m_flag_ClassExtendsDec) return m_cache_ClassExtendsDec;
        m_flag_ClassExtendsDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassExtendsDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassExtendsDec = node;
                break;
            }
        }
        return m_cache_ClassExtendsDec;
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
    bool m_flag_ClassBodyDec = false;
    std::shared_ptr<ALittleScriptClassBodyDecElement> m_cache_ClassBodyDec;
public:
    std::shared_ptr<ALittleScriptClassBodyDecElement> GetClassBodyDec()
    {
        if (m_flag_ClassBodyDec) return m_cache_ClassBodyDec;
        m_flag_ClassBodyDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptClassBodyDecElement>(child);
            if (node != nullptr)
            {
                m_cache_ClassBodyDec = node;
                break;
            }
        }
        return m_cache_ClassBodyDec;
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

#endif // _ALITTLE_ALittleScriptClassDecElement_H_
