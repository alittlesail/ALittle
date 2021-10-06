#include "ALittleScriptEnumDecElement.h"

#include "ALittleScriptEnumNameDecElement.h"
#include "ALittleScriptEnumBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptEnumNameDecElement> ALittleScriptEnumDecElement::GetEnumNameDec()
{
    if (m_flag_EnumNameDec) return m_cache_EnumNameDec;
    m_flag_EnumNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptEnumNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_EnumNameDec = node;
            break;
        }
    }
    return m_cache_EnumNameDec;
}
std::shared_ptr<ALittleScriptEnumBodyDecElement> ALittleScriptEnumDecElement::GetEnumBodyDec()
{
    if (m_flag_EnumBodyDec) return m_cache_EnumBodyDec;
    m_flag_EnumBodyDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptEnumBodyDecElement>(child);
        if (node != nullptr)
        {
            m_cache_EnumBodyDec = node;
            break;
        }
    }
    return m_cache_EnumBodyDec;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptEnumDecElement::GetKey()
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

