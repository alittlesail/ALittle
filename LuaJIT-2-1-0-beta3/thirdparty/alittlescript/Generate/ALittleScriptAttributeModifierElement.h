#ifndef _ALITTLE_ALittleScriptAttributeModifierElement_H_
#define _ALITTLE_ALittleScriptAttributeModifierElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptNativeModifierElement;
class ALittleScriptCommandModifierElement;
class ALittleScriptLanguageModifierElement;
class ALittleScriptConstModifierElement;
class ALittleScriptNullableModifierElement;
class ALittleScriptProtocolModifierElement;
class ALittleScriptStringElement;

class ALittleScriptAttributeModifierElement : public ABnfNodeElement
{
public:
    ALittleScriptAttributeModifierElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptAttributeModifierElement() { }

private:
    bool m_flag_NativeModifier = false;
    std::shared_ptr<ALittleScriptNativeModifierElement> m_cache_NativeModifier;
public:
    std::shared_ptr<ALittleScriptNativeModifierElement> GetNativeModifier()
    {
        if (m_flag_NativeModifier) return m_cache_NativeModifier;
        m_flag_NativeModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptNativeModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_NativeModifier = node;
                break;
            }
        }
        return m_cache_NativeModifier;
    }
private:
    bool m_flag_CommandModifier = false;
    std::shared_ptr<ALittleScriptCommandModifierElement> m_cache_CommandModifier;
public:
    std::shared_ptr<ALittleScriptCommandModifierElement> GetCommandModifier()
    {
        if (m_flag_CommandModifier) return m_cache_CommandModifier;
        m_flag_CommandModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptCommandModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_CommandModifier = node;
                break;
            }
        }
        return m_cache_CommandModifier;
    }
private:
    bool m_flag_LanguageModifier = false;
    std::shared_ptr<ALittleScriptLanguageModifierElement> m_cache_LanguageModifier;
public:
    std::shared_ptr<ALittleScriptLanguageModifierElement> GetLanguageModifier()
    {
        if (m_flag_LanguageModifier) return m_cache_LanguageModifier;
        m_flag_LanguageModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptLanguageModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_LanguageModifier = node;
                break;
            }
        }
        return m_cache_LanguageModifier;
    }
private:
    bool m_flag_ConstModifier = false;
    std::shared_ptr<ALittleScriptConstModifierElement> m_cache_ConstModifier;
public:
    std::shared_ptr<ALittleScriptConstModifierElement> GetConstModifier()
    {
        if (m_flag_ConstModifier) return m_cache_ConstModifier;
        m_flag_ConstModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptConstModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_ConstModifier = node;
                break;
            }
        }
        return m_cache_ConstModifier;
    }
private:
    bool m_flag_NullableModifier = false;
    std::shared_ptr<ALittleScriptNullableModifierElement> m_cache_NullableModifier;
public:
    std::shared_ptr<ALittleScriptNullableModifierElement> GetNullableModifier()
    {
        if (m_flag_NullableModifier) return m_cache_NullableModifier;
        m_flag_NullableModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptNullableModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_NullableModifier = node;
                break;
            }
        }
        return m_cache_NullableModifier;
    }
private:
    bool m_flag_ProtocolModifier = false;
    std::shared_ptr<ALittleScriptProtocolModifierElement> m_cache_ProtocolModifier;
public:
    std::shared_ptr<ALittleScriptProtocolModifierElement> GetProtocolModifier()
    {
        if (m_flag_ProtocolModifier) return m_cache_ProtocolModifier;
        m_flag_ProtocolModifier = true;
        for (auto& child : m_childs)
        {
            auto node = std::dynamic_pointer_cast<ALittleScriptProtocolModifierElement>(child);
            if (node != nullptr)
            {
                m_cache_ProtocolModifier = node;
                break;
            }
        }
        return m_cache_ProtocolModifier;
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

#endif // _ALITTLE_ALittleScriptAttributeModifierElement_H_
