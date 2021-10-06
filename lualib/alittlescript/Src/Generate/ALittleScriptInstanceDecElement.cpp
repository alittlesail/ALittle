#include "ALittleScriptInstanceDecElement.h"

#include "ALittleScriptVarAssignExprElement.h"

std::shared_ptr<ALittleScriptVarAssignExprElement> ALittleScriptInstanceDecElement::GetVarAssignExpr()
{
    if (m_flag_VarAssignExpr) return m_cache_VarAssignExpr;
    m_flag_VarAssignExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptVarAssignExprElement>(child);
        if (node != nullptr)
        {
            m_cache_VarAssignExpr = node;
            break;
        }
    }
    return m_cache_VarAssignExpr;
}

