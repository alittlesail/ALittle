#include "ALittleScriptDoWhileExprElement.h"

#include "ALittleScriptDoWhileBodyElement.h"
#include "ALittleScriptDoWhileConditionElement.h"
#include "ALittleScriptKeyElement.h"
#include "ALittleScriptStringElement.h"

std::shared_ptr<ALittleScriptDoWhileBodyElement> ALittleScriptDoWhileExprElement::GetDoWhileBody()
{
    if (m_flag_DoWhileBody) return m_cache_DoWhileBody;
    m_flag_DoWhileBody = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptDoWhileBodyElement>(child);
        if (node != nullptr)
        {
            m_cache_DoWhileBody = node;
            break;
        }
    }
    return m_cache_DoWhileBody;
}
std::shared_ptr<ALittleScriptDoWhileConditionElement> ALittleScriptDoWhileExprElement::GetDoWhileCondition()
{
    if (m_flag_DoWhileCondition) return m_cache_DoWhileCondition;
    m_flag_DoWhileCondition = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptDoWhileConditionElement>(child);
        if (node != nullptr)
        {
            m_cache_DoWhileCondition = node;
            break;
        }
    }
    return m_cache_DoWhileCondition;
}
const std::vector<std::shared_ptr<ALittleScriptKeyElement>>& ALittleScriptDoWhileExprElement::GetKeyList()
{
    if (m_flag_Key) return m_list_Key;
    m_flag_Key = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptKeyElement>(child);
        if (node != nullptr)
            m_list_Key.push_back(node);
    }
    return m_list_Key;
}
std::shared_ptr<ALittleScriptStringElement> ALittleScriptDoWhileExprElement::GetString()
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

