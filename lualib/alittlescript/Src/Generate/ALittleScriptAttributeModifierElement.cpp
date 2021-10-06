#include "ALittleScriptAttributeModifierElement.h"

#include "ALittleScriptNativeModifierElement.h"
#include "ALittleScriptCommandModifierElement.h"
#include "ALittleScriptLanguageModifierElement.h"
#include "ALittleScriptConstModifierElement.h"
#include "ALittleScriptNullableModifierElement.h"
#include "ALittleScriptProtocolModifierElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptNativeModifierElement> ALittleScriptAttributeModifierElement::GetNativeModifier()
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
std::shared_ptr<ALittleScriptCommandModifierElement> ALittleScriptAttributeModifierElement::GetCommandModifier()
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
std::shared_ptr<ALittleScriptLanguageModifierElement> ALittleScriptAttributeModifierElement::GetLanguageModifier()
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
std::shared_ptr<ALittleScriptConstModifierElement> ALittleScriptAttributeModifierElement::GetConstModifier()
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
std::shared_ptr<ALittleScriptNullableModifierElement> ALittleScriptAttributeModifierElement::GetNullableModifier()
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
std::shared_ptr<ALittleScriptProtocolModifierElement> ALittleScriptAttributeModifierElement::GetProtocolModifier()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptAttributeModifierElement::GetStringList()
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

