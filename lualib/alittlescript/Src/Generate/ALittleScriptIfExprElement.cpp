#include "ALittleScriptIfExprElement.h"

#include "ALittleScriptIfConditionElement.h"
#include "ALittleScriptAllExprElement.h"
#include "ALittleScriptIfBodyElement.h"
#include "ALittleScriptElseIfExprElement.h"
#include "ALittleScriptElseExprElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptIfConditionElement> ALittleScriptIfExprElement::GetIfCondition()
{
    if (m_flag_IfCondition) return m_cache_IfCondition;
    m_flag_IfCondition = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptIfConditionElement>(child);
        if (node != nullptr)
        {
            m_cache_IfCondition = node;
            break;
        }
    }
    return m_cache_IfCondition;
}
std::shared_ptr<ALittleScriptAllExprElement> ALittleScriptIfExprElement::GetAllExpr()
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
std::shared_ptr<ALittleScriptIfBodyElement> ALittleScriptIfExprElement::GetIfBody()
{
    if (m_flag_IfBody) return m_cache_IfBody;
    m_flag_IfBody = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptIfBodyElement>(child);
        if (node != nullptr)
        {
            m_cache_IfBody = node;
            break;
        }
    }
    return m_cache_IfBody;
}
const std::vector<std::shared_ptr<ALittleScriptElseIfExprElement>>& ALittleScriptIfExprElement::GetElseIfExprList()
{
    if (m_flag_ElseIfExpr) return m_list_ElseIfExpr;
    m_flag_ElseIfExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptElseIfExprElement>(child);
        if (node != nullptr)
            m_list_ElseIfExpr.push_back(node);
    }
    return m_list_ElseIfExpr;
}
std::shared_ptr<ALittleScriptElseExprElement> ALittleScriptIfExprElement::GetElseExpr()
{
    if (m_flag_ElseExpr) return m_cache_ElseExpr;
    m_flag_ElseExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptElseExprElement>(child);
        if (node != nullptr)
        {
            m_cache_ElseExpr = node;
            break;
        }
    }
    return m_cache_ElseExpr;
}
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptIfExprElement::GetKey()
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

