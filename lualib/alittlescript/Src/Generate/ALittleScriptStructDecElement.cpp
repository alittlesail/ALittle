#include "ALittleScriptStructDecElement.h"

#include "ALittleScriptStructNameDecElement.h"
#include "ALittleScriptStructExtendsDecElement.h"
#include "ALittleScriptStructBodyDecElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptStructNameDecElement> ALittleScriptStructDecElement::GetStructNameDec()
{
    if (m_flag_StructNameDec) return m_cache_StructNameDec;
    m_flag_StructNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_StructNameDec = node;
            break;
        }
    }
    return m_cache_StructNameDec;
}
std::shared_ptr<ALittleScriptStructExtendsDecElement> ALittleScriptStructDecElement::GetStructExtendsDec()
{
    if (m_flag_StructExtendsDec) return m_cache_StructExtendsDec;
    m_flag_StructExtendsDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructExtendsDecElement>(child);
        if (node != nullptr)
        {
            m_cache_StructExtendsDec = node;
            break;
        }
    }
    return m_cache_StructExtendsDec;
}
std::shared_ptr<ALittleScriptStructBodyDecElement> ALittleScriptStructDecElement::GetStructBodyDec()
{
    if (m_flag_StructBodyDec) return m_cache_StructBodyDec;
    m_flag_StructBodyDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructBodyDecElement>(child);
        if (node != nullptr)
        {
            m_cache_StructBodyDec = node;
            break;
        }
    }
    return m_cache_StructBodyDec;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptStructDecElement::GetKey()
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

