#include "ALittleScriptLanguageModifierElement.h"

#include "ALittleScriptLanguageBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptLanguageBodyDecElement> ALittleScriptLanguageModifierElement::GetLanguageBodyDec()
{
    if (m_flag_LanguageBodyDec) return m_cache_LanguageBodyDec;
    m_flag_LanguageBodyDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptLanguageBodyDecElement>(child);
        if (node != nullptr)
        {
            m_cache_LanguageBodyDec = node;
            break;
        }
    }
    return m_cache_LanguageBodyDec;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptLanguageModifierElement::GetKey()
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

