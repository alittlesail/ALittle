#include "ALittleScriptForConditionElement.h"

#include "ALittleScriptForPairDecElement.h"
#include "ALittleScriptForStepConditionElement.h"
#include "ALittleScriptForInConditionElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptForPairDecElement> ALittleScriptForConditionElement::GetForPairDec()
{
    if (m_flag_ForPairDec) return m_cache_ForPairDec;
    m_flag_ForPairDec = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForPairDecElement>(child);
        if (node != nullptr)
        {
            m_cache_ForPairDec = node;
            break;
        }
    }
    return m_cache_ForPairDec;
}
std::shared_ptr<ALittleScriptForStepConditionElement> ALittleScriptForConditionElement::GetForStepCondition()
{
    if (m_flag_ForStepCondition) return m_cache_ForStepCondition;
    m_flag_ForStepCondition = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForStepConditionElement>(child);
        if (node != nullptr)
        {
            m_cache_ForStepCondition = node;
            break;
        }
    }
    return m_cache_ForStepCondition;
}
std::shared_ptr<ALittleScriptForInConditionElement> ALittleScriptForConditionElement::GetForInCondition()
{
    if (m_flag_ForInCondition) return m_cache_ForInCondition;
    m_flag_ForInCondition = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForInConditionElement>(child);
        if (node != nullptr)
        {
            m_cache_ForInCondition = node;
            break;
        }
    }
    return m_cache_ForInCondition;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptForConditionElement::GetKey()
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
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptForConditionElement::GetStringList()
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

