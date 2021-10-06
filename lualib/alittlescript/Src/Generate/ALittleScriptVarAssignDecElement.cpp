#include "ALittleScriptVarAssignDecElement.h"

#include "ALittleScriptVarAssignNameDecElement.h"
#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptVarAssignNameDecElement> ALittleScriptVarAssignDecElement::GetVarAssignNameDec()
{
    if (m_flag_VarAssignNameDec) return m_cache_VarAssignNameDec;
    m_flag_VarAssignNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_VarAssignNameDec = node;
            break;
        }
    }
    return m_cache_VarAssignNameDec;
}
std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptVarAssignDecElement::GetAllType()
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
std::shared_ptr<ALittleScriptStringElement> ALittleScriptVarAssignDecElement::GetString()
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

