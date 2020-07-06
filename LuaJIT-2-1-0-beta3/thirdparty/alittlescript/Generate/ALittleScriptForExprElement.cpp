#include "ALittleScriptForExprElement.h"

#include "ALittleScriptForConditionElement.h"
#include "ALittleScriptForBodyElement.h"
#include "ALittleScriptAllExprElement.h"
#include "ALittleScriptKeyElement.h"

std::shared_ptr<ALittleScriptForConditionElement> ALittleScriptForExprElement::GetForCondition()
{
    if (m_flag_ForCondition) return m_cache_ForCondition;
    m_flag_ForCondition = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForConditionElement>(child);
        if (node != nullptr)
        {
            m_cache_ForCondition = node;
            break;
        }
    }
    return m_cache_ForCondition;
}
std::shared_ptr<ALittleScriptForBodyElement> ALittleScriptForExprElement::GetForBody()
{
    if (m_flag_ForBody) return m_cache_ForBody;
    m_flag_ForBody = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForBodyElement>(child);
        if (node != nullptr)
        {
            m_cache_ForBody = node;
            break;
        }
    }
    return m_cache_ForBody;
}
std::shared_ptr<ALittleScriptAllExprElement> ALittleScriptForExprElement::GetAllExpr()
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
std::shared_ptr<ALittleScriptKeyElement> ALittleScriptForExprElement::GetKey()
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

