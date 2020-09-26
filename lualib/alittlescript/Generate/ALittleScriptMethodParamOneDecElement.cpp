#include "ALittleScriptMethodParamOneDecElement.h"

#include "ALittleScriptMethodParamTailDecElement.h"
#include "ALittleScriptModifierElement.h"
#include "ALittleScriptAllTypeElement.h"
#include "ALittleScriptMethodParamNameDecElement.h"

std::shared_ptr<ALittleScriptMethodParamTailDecElement> ALittleScriptMethodParamOneDecElement::GetMethodParamTailDec()
{
    if (m_flag_MethodParamTailDec) return m_cache_MethodParamTailDec;
    m_flag_MethodParamTailDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamTailDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodParamTailDec = node;
            break;
        }
    }
    return m_cache_MethodParamTailDec;
}
const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& ALittleScriptMethodParamOneDecElement::GetModifierList()
{
    if (m_flag_Modifier) return m_list_Modifier;
    m_flag_Modifier = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptModifierElement>(child);
        if (node != nullptr)
            m_list_Modifier.push_back(node);
    }
    return m_list_Modifier;
}
std::shared_ptr<ALittleScriptAllTypeElement> ALittleScriptMethodParamOneDecElement::GetAllType()
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
std::shared_ptr<ALittleScriptMethodParamNameDecElement> ALittleScriptMethodParamOneDecElement::GetMethodParamNameDec()
{
    if (m_flag_MethodParamNameDec) return m_cache_MethodParamNameDec;
    m_flag_MethodParamNameDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptMethodParamNameDecElement>(child);
        if (node != nullptr)
        {
            m_cache_MethodParamNameDec = node;
            break;
        }
    }
    return m_cache_MethodParamNameDec;
}

