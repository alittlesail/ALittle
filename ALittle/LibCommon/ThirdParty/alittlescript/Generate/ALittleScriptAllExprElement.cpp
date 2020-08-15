#include "ALittleScriptAllExprElement.h"

#include "ALittleScriptModifierElement.h"
#include "ALittleScriptIfExprElement.h"
#include "ALittleScriptEmptyExprElement.h"
#include "ALittleScriptWhileExprElement.h"
#include "ALittleScriptForExprElement.h"
#include "ALittleScriptDoWhileExprElement.h"
#include "ALittleScriptReturnExprElement.h"
#include "ALittleScriptThrowExprElement.h"
#include "ALittleScriptFlowExprElement.h"
#include "ALittleScriptAssertExprElement.h"
#include "ALittleScriptWrapExprElement.h"
#include "ALittleScriptOp1ExprElement.h"
#include "ALittleScriptVarAssignExprElement.h"
#include "ALittleScriptOpAssignExprElement.h"

const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& ALittleScriptAllExprElement::GetModifierList()
{
    if (m_flag_Modifier) return m_list_Modifier;
    m_flag_Modifier = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptModifierElement>(child);
        if (node != nullptr)
            m_list_Modifier.push_back(node);
    }
    return m_list_Modifier;
}
std::shared_ptr<ALittleScriptIfExprElement> ALittleScriptAllExprElement::GetIfExpr()
{
    if (m_flag_IfExpr) return m_cache_IfExpr;
    m_flag_IfExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptIfExprElement>(child);
        if (node != nullptr)
        {
            m_cache_IfExpr = node;
            break;
        }
    }
    return m_cache_IfExpr;
}
std::shared_ptr<ALittleScriptEmptyExprElement> ALittleScriptAllExprElement::GetEmptyExpr()
{
    if (m_flag_EmptyExpr) return m_cache_EmptyExpr;
    m_flag_EmptyExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptEmptyExprElement>(child);
        if (node != nullptr)
        {
            m_cache_EmptyExpr = node;
            break;
        }
    }
    return m_cache_EmptyExpr;
}
std::shared_ptr<ALittleScriptWhileExprElement> ALittleScriptAllExprElement::GetWhileExpr()
{
    if (m_flag_WhileExpr) return m_cache_WhileExpr;
    m_flag_WhileExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(child);
        if (node != nullptr)
        {
            m_cache_WhileExpr = node;
            break;
        }
    }
    return m_cache_WhileExpr;
}
std::shared_ptr<ALittleScriptForExprElement> ALittleScriptAllExprElement::GetForExpr()
{
    if (m_flag_ForExpr) return m_cache_ForExpr;
    m_flag_ForExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptForExprElement>(child);
        if (node != nullptr)
        {
            m_cache_ForExpr = node;
            break;
        }
    }
    return m_cache_ForExpr;
}
std::shared_ptr<ALittleScriptDoWhileExprElement> ALittleScriptAllExprElement::GetDoWhileExpr()
{
    if (m_flag_DoWhileExpr) return m_cache_DoWhileExpr;
    m_flag_DoWhileExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptDoWhileExprElement>(child);
        if (node != nullptr)
        {
            m_cache_DoWhileExpr = node;
            break;
        }
    }
    return m_cache_DoWhileExpr;
}
std::shared_ptr<ALittleScriptReturnExprElement> ALittleScriptAllExprElement::GetReturnExpr()
{
    if (m_flag_ReturnExpr) return m_cache_ReturnExpr;
    m_flag_ReturnExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptReturnExprElement>(child);
        if (node != nullptr)
        {
            m_cache_ReturnExpr = node;
            break;
        }
    }
    return m_cache_ReturnExpr;
}
std::shared_ptr<ALittleScriptThrowExprElement> ALittleScriptAllExprElement::GetThrowExpr()
{
    if (m_flag_ThrowExpr) return m_cache_ThrowExpr;
    m_flag_ThrowExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptThrowExprElement>(child);
        if (node != nullptr)
        {
            m_cache_ThrowExpr = node;
            break;
        }
    }
    return m_cache_ThrowExpr;
}
std::shared_ptr<ALittleScriptFlowExprElement> ALittleScriptAllExprElement::GetFlowExpr()
{
    if (m_flag_FlowExpr) return m_cache_FlowExpr;
    m_flag_FlowExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptFlowExprElement>(child);
        if (node != nullptr)
        {
            m_cache_FlowExpr = node;
            break;
        }
    }
    return m_cache_FlowExpr;
}
std::shared_ptr<ALittleScriptAssertExprElement> ALittleScriptAllExprElement::GetAssertExpr()
{
    if (m_flag_AssertExpr) return m_cache_AssertExpr;
    m_flag_AssertExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptAssertExprElement>(child);
        if (node != nullptr)
        {
            m_cache_AssertExpr = node;
            break;
        }
    }
    return m_cache_AssertExpr;
}
std::shared_ptr<ALittleScriptWrapExprElement> ALittleScriptAllExprElement::GetWrapExpr()
{
    if (m_flag_WrapExpr) return m_cache_WrapExpr;
    m_flag_WrapExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptWrapExprElement>(child);
        if (node != nullptr)
        {
            m_cache_WrapExpr = node;
            break;
        }
    }
    return m_cache_WrapExpr;
}
std::shared_ptr<ALittleScriptOp1ExprElement> ALittleScriptAllExprElement::GetOp1Expr()
{
    if (m_flag_Op1Expr) return m_cache_Op1Expr;
    m_flag_Op1Expr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOp1ExprElement>(child);
        if (node != nullptr)
        {
            m_cache_Op1Expr = node;
            break;
        }
    }
    return m_cache_Op1Expr;
}
std::shared_ptr<ALittleScriptVarAssignExprElement> ALittleScriptAllExprElement::GetVarAssignExpr()
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
std::shared_ptr<ALittleScriptOpAssignExprElement> ALittleScriptAllExprElement::GetOpAssignExpr()
{
    if (m_flag_OpAssignExpr) return m_cache_OpAssignExpr;
    m_flag_OpAssignExpr = true;
    for (auto& child : m_childs)
    {
        auto node = std::dynamic_pointer_cast<ALittleScriptOpAssignExprElement>(child);
        if (node != nullptr)
        {
            m_cache_OpAssignExpr = node;
            break;
        }
    }
    return m_cache_OpAssignExpr;
}

