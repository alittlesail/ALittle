#include "ALittleScriptElseIfExprElement.h"

#include "ALittleScriptElseIfConditionElement.h"
#include "ALittleScriptElseIfBodyElement.h"
#include "ALittleScriptAllExprElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptElseIfConditionElement> ALittleScriptElseIfExprElement::GetElseIfCondition()
{
    if (m_flag_ElseIfCondition) return m_cache_ElseIfCondition;
    m_flag_ElseIfCondition = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptElseIfConditionElement>(child);
        if (node != nullptr)
        {
            m_cache_ElseIfCondition = node;
            break;
        }
    }
    return m_cache_ElseIfCondition;
}
std::shared_ptr<ALittleScriptElseIfBodyElement> ALittleScriptElseIfExprElement::GetElseIfBody()
{
    if (m_flag_ElseIfBody) return m_cache_ElseIfBody;
    m_flag_ElseIfBody = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptElseIfBodyElement>(child);
        if (node != nullptr)
        {
            m_cache_ElseIfBody = node;
            break;
        }
    }
    return m_cache_ElseIfBody;
}
std::shared_ptr<ALittleScriptAllExprElement> ALittleScriptElseIfExprElement::GetAllExpr()
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
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptElseIfExprElement::GetKey()
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

