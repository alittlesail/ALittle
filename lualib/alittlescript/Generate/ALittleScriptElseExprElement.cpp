#include "ALittleScriptElseExprElement.h"

#include "ALittleScriptElseBodyElement.h"
#include "ALittleScriptAllExprElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptElseBodyElement> ALittleScriptElseExprElement::GetElseBody()
{
    if (m_flag_ElseBody) return m_cache_ElseBody;
    m_flag_ElseBody = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptElseBodyElement>(child);
        if (node != nullptr)
        {
            m_cache_ElseBody = node;
            break;
        }
    }
    return m_cache_ElseBody;
}
std::shared_ptr<ALittleScriptAllExprElement> ALittleScriptElseExprElement::GetAllExpr()
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
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptElseExprElement::GetKey()
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

