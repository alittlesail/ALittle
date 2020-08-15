#include "ALittleScriptVarAssignExprElement.h"

#include "ALittleScriptVarAssignDecElement.h"
#include "ALittleScriptValueStatElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptVarAssignDecElement>>& ALittleScriptVarAssignExprElement::GetVarAssignDecList()
{
    if (m_flag_VarAssignDec) return m_list_VarAssignDec;
    m_flag_VarAssignDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptVarAssignDecElement>(child);
        if (node != nullptr)
            m_list_VarAssignDec.push_back(node);
    }
    return m_list_VarAssignDec;
}
std::shared_ptr<ALittleScriptValueStatElement> ALittleScriptVarAssignExprElement::GetValueStat()
{
    if (m_flag_ValueStat) return m_cache_ValueStat;
    m_flag_ValueStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptValueStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ValueStat = node;
            break;
        }
    }
    return m_cache_ValueStat;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptVarAssignExprElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptVarAssignExprElement::GetStringList()
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

