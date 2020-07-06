#include "ALittleScriptCommandModifierElement.h"

#include "ALittleScriptCommandBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptCommandBodyDecElement> ALittleScriptCommandModifierElement::GetCommandBodyDec()
{
    if (m_flag_CommandBodyDec) return m_cache_CommandBodyDec;
    m_flag_CommandBodyDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptCommandBodyDecElement>(child);
        if (node != nullptr)
        {
            m_cache_CommandBodyDec = node;
            break;
        }
    }
    return m_cache_CommandBodyDec;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptCommandModifierElement::GetKey()
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

