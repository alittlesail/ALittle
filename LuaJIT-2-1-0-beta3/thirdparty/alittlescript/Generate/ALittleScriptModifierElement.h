#ifndef _ALITTLE_ALittleScriptModifierElement_H_
#define _ALITTLE_ALittleScriptModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptAttributeModifierElement;
class ALittleScriptAccessModifierElement;
class ALittleScriptCoroutineModifierElement;
class ALittleScriptRegisterModifierElement;

class ALittleScriptModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptModifierElement() { }

private:
    bool m_flag_AttributeModifier = false;
    std::shared_ptr<ALittleScriptAttributeModifierElement> m_cache_AttributeModifier;
public:
    std::shared_ptr<ALittleScriptAttributeModifierElement> GetAttributeModifier()
    {
        if (m_flag_AttributeModifier) return m_cache_AttributeModifier;
        m_flag_AttributeModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptAttributeModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_AttributeModifier = node;
                break;
            }
        }
        return m_cache_AttributeModifier;
    }
private:
    bool m_flag_AccessModifier = false;
    std::shared_ptr<ALittleScriptAccessModifierElement> m_cache_AccessModifier;
public:
    std::shared_ptr<ALittleScriptAccessModifierElement> GetAccessModifier()
    {
        if (m_flag_AccessModifier) return m_cache_AccessModifier;
        m_flag_AccessModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptAccessModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_AccessModifier = node;
                break;
            }
        }
        return m_cache_AccessModifier;
    }
private:
    bool m_flag_CoroutineModifier = false;
    std::shared_ptr<ALittleScriptCoroutineModifierElement> m_cache_CoroutineModifier;
public:
    std::shared_ptr<ALittleScriptCoroutineModifierElement> GetCoroutineModifier()
    {
        if (m_flag_CoroutineModifier) return m_cache_CoroutineModifier;
        m_flag_CoroutineModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCoroutineModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_CoroutineModifier = node;
                break;
            }
        }
        return m_cache_CoroutineModifier;
    }
private:
    bool m_flag_RegisterModifier = false;
    std::shared_ptr<ALittleScriptRegisterModifierElement> m_cache_RegisterModifier;
public:
    std::shared_ptr<ALittleScriptRegisterModifierElement> GetRegisterModifier()
    {
        if (m_flag_RegisterModifier) return m_cache_RegisterModifier;
        m_flag_RegisterModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptRegisterModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_RegisterModifier = node;
                break;
            }
        }
        return m_cache_RegisterModifier;
    }
};

#endif // _ALITTLE_ALittleScriptModifierElement_H_
