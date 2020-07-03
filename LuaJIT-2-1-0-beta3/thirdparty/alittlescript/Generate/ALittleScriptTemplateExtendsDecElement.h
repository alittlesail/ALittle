#ifndef _ALITTLE_ALittleScriptTemplateExtendsDecElement_H_
#define _ALITTLE_ALittleScriptTemplateExtendsDecElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAllTypeElement;
class ALittleScriptTemplateExtendsClassDecElement;
class ALittleScriptTemplateExtendsStructDecElement;
class ALittleScriptStringElement;

class ALittleScriptTemplateExtendsDecElement : public ABnfNodeElement
{
public:
    ALittleScriptTemplateExtendsDecElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptTemplateExtendsDecElement() { }

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
    bool m_flag_TemplateExtendsClassDec = false;
    std::shared_ptr<ALittleScriptTemplateExtendsClassDecElement> m_cache_TemplateExtendsClassDec;
public:
    std::shared_ptr<ALittleScriptTemplateExtendsClassDecElement> GetTemplateExtendsClassDec()
    {
        if (m_flag_TemplateExtendsClassDec) return m_cache_TemplateExtendsClassDec;
        m_flag_TemplateExtendsClassDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptTemplateExtendsClassDecElement>(child);
            if (node != nullptr)
            {
                m_cache_TemplateExtendsClassDec = node;
                break;
            }
        }
        return m_cache_TemplateExtendsClassDec;
    }
private:
    bool m_flag_TemplateExtendsStructDec = false;
    std::shared_ptr<ALittleScriptTemplateExtendsStructDecElement> m_cache_TemplateExtendsStructDec;
public:
    std::shared_ptr<ALittleScriptTemplateExtendsStructDecElement> GetTemplateExtendsStructDec()
    {
        if (m_flag_TemplateExtendsStructDec) return m_cache_TemplateExtendsStructDec;
        m_flag_TemplateExtendsStructDec = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptTemplateExtendsStructDecElement>(child);
            if (node != nullptr)
            {
                m_cache_TemplateExtendsStructDec = node;
                break;
            }
        }
        return m_cache_TemplateExtendsStructDec;
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

#endif // _ALITTLE_ALittleScriptTemplateExtendsDecElement_H_
