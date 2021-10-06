#include "ALittleScriptWhileExprElement.h"

#include "ALittleScriptWhileConditionElement.h"
#include "ALittleScriptAllExprElement.h"
#include "ALittleScriptWhileBodyElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptWhileConditionElement> ALittleScriptWhileExprElement::GetWhileCondition()
{
    if (m_flag_WhileCondition) return m_cache_WhileCondition;
    m_flag_WhileCondition = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptWhileConditionElement>(child);
        if (node != nullptr)
        {
            m_cache_WhileCondition = node;
            break;
        }
    }
    return m_cache_WhileCondition;
}
std::shared_ptr<ALittleScriptAllExprElement> ALittleScriptWhileExprElement::GetAllExpr()
{
    if (m_flag_AllExpr) return m_cache_AllExpr;
    m_flag_AllExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAllExprElement>(child);
        if (node != nullptr)
        {
            m_cache_AllExpr = node;
            break;
        }
    }
    return m_cache_AllExpr;
}
std::shared_ptr<ALittleScriptWhileBodyElement> ALittleScriptWhileExprElement::GetWhileBody()
{
    if (m_flag_WhileBody) return m_cache_WhileBody;
    m_flag_WhileBody = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptWhileBodyElement>(child);
        if (node != nullptr)
        {
            m_cache_WhileBody = node;
            break;
        }
    }
    return m_cache_WhileBody;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptWhileExprElement::GetKey()
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

