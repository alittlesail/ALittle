#include "ALittleScriptWhileBodyElement.h"

#include "ALittleScriptAllExprElement.h"
#include "ALittleScriptStringElement.h"

const std::vector<std::shared_ptr<ALittleScriptAllExprElement>>& ALittleScriptWhileBodyElement::GetAllExprList()
{
    if (m_flag_AllExpr) return m_list_AllExpr;
    m_flag_AllExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAllExprElement>(child);
        if (node != nullptr)
            m_list_AllExpr.push_back(node);
    }
    return m_list_AllExpr;
}
const std::vector<std::shared_ptr<ALittleScriptStringElement>>& ALittleScriptWhileBodyElement::GetStringList()
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

