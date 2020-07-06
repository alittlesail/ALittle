#include "ALittleScriptModifierElement.h"

#include "ALittleScriptAttributeModifierElement.h"
#include "ALittleScriptAccessModifierElement.h"
#include "ALittleScriptCoroutineModifierElement.h"
#include "ALittleScriptRegisterModifierElement.h"

std::shared_ptr<ALittleScriptAttributeModifierElement> ALittleScriptModifierElement::GetAttributeModifier()
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
std::shared_ptr<ALittleScriptAccessModifierElement> ALittleScriptModifierElement::GetAccessModifier()
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
std::shared_ptr<ALittleScriptCoroutineModifierElement> ALittleScriptModifierElement::GetCoroutineModifier()
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
std::shared_ptr<ALittleScriptRegisterModifierElement> ALittleScriptModifierElement::GetRegisterModifier()
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

