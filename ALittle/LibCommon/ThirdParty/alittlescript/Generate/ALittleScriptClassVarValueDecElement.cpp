#include "ALittleScriptClassVarValueDecElement.h"

#include "ALittleScriptConstValueElement.h"
#include "ALittleScriptOpNewStatElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptConstValueElement> ALittleScriptClassVarValueDecElement::GetConstValue()
{
    if (m_flag_ConstValue) return m_cache_ConstValue;
    m_flag_ConstValue = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptConstValueElement>(child);
        if (node != nullptr)
        {
            m_cache_ConstValue = node;
            break;
        }
    }
    return m_cache_ConstValue;
}
std::shared_ptr<ALittleScriptOpNewStatElement> ALittleScriptClassVarValueDecElement::GetOpNewStat()
{
    if (m_flag_OpNewStat) return m_cache_OpNewStat;
    m_flag_OpNewStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOpNewStatElement>(child);
        if (node != nullptr)
        {
            m_cache_OpNewStat = node;
            break;
        }
    }
    return m_cache_OpNewStat;
}
std::shared_ptr<ALittleScriptStringElement> ALittleScriptClassVarValueDecElement::GetString()
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

