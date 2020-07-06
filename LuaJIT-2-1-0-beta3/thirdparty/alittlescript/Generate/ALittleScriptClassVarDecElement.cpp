#include "ALittleScriptClassVarDecElement.h"

#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptClassVarNameDecElement.h"
#include "ALittleScriptClassVarValueDecElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptClassVarDecElement::GetAllType()
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
std::shared_ptr<ALittleScriptClassVarNameDecElement> ALittleScriptClassVarDecElement::GetClassVarNameDec()
{
    if (m_flag_ClassVarNameDec) return m_cache_ClassVarNameDec;
    m_flag_ClassVarNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassVarNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassVarNameDec = node;
            break;
        }
    }
    return m_cache_ClassVarNameDec;
}
std::shared_ptr<ALittleScriptClassVarValueDecElement> ALittleScriptClassVarDecElement::GetClassVarValueDec()
{
    if (m_flag_ClassVarValueDec) return m_cache_ClassVarValueDec;
    m_flag_ClassVarValueDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptClassVarValueDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ClassVarValueDec = node;
            break;
        }
    }
    return m_cache_ClassVarValueDec;
}
std::shared_ptr<ALittleScriptStringElement> ALittleScriptClassVarDecElement::GetString()
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

