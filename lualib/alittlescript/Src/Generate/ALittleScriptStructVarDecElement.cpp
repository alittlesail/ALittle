#include "ALittleScriptStructVarDecElement.h"

#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptStructVarNameDecElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptStructVarDecElement::GetAllType()
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
std::shared_ptr<ALittleScriptStructVarNameDecElement> ALittleScriptStructVarDecElement::GetStructVarNameDec()
{
    if (m_flag_StructVarNameDec) return m_cache_StructVarNameDec;
    m_flag_StructVarNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptStructVarNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_StructVarNameDec = node;
            break;
        }
    }
    return m_cache_StructVarNameDec;
}
std::shared_ptr<ALittleScriptStringElement> ALittleScriptStructVarDecElement::GetString()
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

