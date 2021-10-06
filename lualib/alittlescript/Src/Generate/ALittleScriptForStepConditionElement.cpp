#include "ALittleScriptForStepConditionElement.h"

#include "ALittleScriptForStartStatElement.h"
#include "ALittleScriptForEndStatElement.h"
#include "ALittleScriptForStepStatElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptForStartStatElement> ALittleScriptForStepConditionElement::GetForStartStat()
{
    if (m_flag_ForStartStat) return m_cache_ForStartStat;
    m_flag_ForStartStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForStartStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ForStartStat = node;
            break;
        }
    }
    return m_cache_ForStartStat;
}
std::shared_ptr<ALittleScriptForEndStatElement> ALittleScriptForStepConditionElement::GetForEndStat()
{
    if (m_flag_ForEndStat) return m_cache_ForEndStat;
    m_flag_ForEndStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForEndStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ForEndStat = node;
            break;
        }
    }
    return m_cache_ForEndStat;
}
std::shared_ptr<ALittleScriptForStepStatElement> ALittleScriptForStepConditionElement::GetForStepStat()
{
    if (m_flag_ForStepStat) return m_cache_ForStepStat;
    m_flag_ForStepStat = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForStepStatElement>(child);
        if (node != nullptr)
        {
            m_cache_ForStepStat = node;
            break;
        }
    }
    return m_cache_ForStepStat;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptForStepConditionElement::GetStringList()
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

