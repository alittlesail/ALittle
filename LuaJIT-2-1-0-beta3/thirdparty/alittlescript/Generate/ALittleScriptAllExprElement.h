#ifndef _ALITTLE_ALittleScriptAllExprElement_H_
#define _ALITTLE_ALittleScriptAllExprElement_H_

#include <memory>
#include <vector>
#include <string>
#include "../../alanguage/Model/ABnfNodeElement.h"

class ALittleScriptModifierElement;
class ALittleScriptIfExprElement;
class ALittleScriptEmptyExprElement;
class ALittleScriptWhileExprElement;
class ALittleScriptForExprElement;
class ALittleScriptDoWhileExprElement;
class ALittleScriptReturnExprElement;
class ALittleScriptThrowExprElement;
class ALittleScriptFlowExprElement;
class ALittleScriptAssertExprElement;
class ALittleScriptWrapExprElement;
class ALittleScriptOp1ExprElement;
class ALittleScriptVarAssignExprElement;
class ALittleScriptOpAssignExprElement;

class ALittleScriptAllExprElement : public ABnfNodeElement
{
public:
    ALittleScriptAllExprElement(ABnfFactory* factory, ABnfFile* file, int line, int col, int offset, const std::string& type)
        : ABnfNodeElement(factory, file, line, col, offset, type) { }
    virtual ~ALittleScriptAllExprElement() { }

private:
    bool m_flag_Modifier = false;
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> m_list_Modifier;
public:
    std::vector<std::shared_ptr<ALittleScriptModifierElement>> GetModifierList()
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
private:
    bool m_flag_IfExpr = false;
    std::shared_ptr<ALittleScriptIfExprElement> m_cache_IfExpr;
public:
    std::shared_ptr<ALittleScriptIfExprElement> GetIfExpr()
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
private:
    bool m_flag_EmptyExpr = false;
    std::shared_ptr<ALittleScriptEmptyExprElement> m_cache_EmptyExpr;
public:
    std::shared_ptr<ALittleScriptEmptyExprElement> GetEmptyExpr()
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
private:
    bool m_flag_WhileExpr = false;
    std::shared_ptr<ALittleScriptWhileExprElement> m_cache_WhileExpr;
public:
    std::shared_ptr<ALittleScriptWhileExprElement> GetWhileExpr()
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
private:
    bool m_flag_ForExpr = false;
    std::shared_ptr<ALittleScriptForExprElement> m_cache_ForExpr;
public:
    std::shared_ptr<ALittleScriptForExprElement> GetForExpr()
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
private:
    bool m_flag_DoWhileExpr = false;
    std::shared_ptr<ALittleScriptDoWhileExprElement> m_cache_DoWhileExpr;
public:
    std::shared_ptr<ALittleScriptDoWhileExprElement> GetDoWhileExpr()
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
private:
    bool m_flag_ReturnExpr = false;
    std::shared_ptr<ALittleScriptReturnExprElement> m_cache_ReturnExpr;
public:
    std::shared_ptr<ALittleScriptReturnExprElement> GetReturnExpr()
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
private:
    bool m_flag_ThrowExpr = false;
    std::shared_ptr<ALittleScriptThrowExprElement> m_cache_ThrowExpr;
public:
    std::shared_ptr<ALittleScriptThrowExprElement> GetThrowExpr()
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
private:
    bool m_flag_FlowExpr = false;
    std::shared_ptr<ALittleScriptFlowExprElement> m_cache_FlowExpr;
public:
    std::shared_ptr<ALittleScriptFlowExprElement> GetFlowExpr()
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
private:
    bool m_flag_AssertExpr = false;
    std::shared_ptr<ALittleScriptAssertExprElement> m_cache_AssertExpr;
public:
    std::shared_ptr<ALittleScriptAssertExprElement> GetAssertExpr()
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
private:
    bool m_flag_WrapExpr = false;
    std::shared_ptr<ALittleScriptWrapExprElement> m_cache_WrapExpr;
public:
    std::shared_ptr<ALittleScriptWrapExprElement> GetWrapExpr()
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
private:
    bool m_flag_Op1Expr = false;
    std::shared_ptr<ALittleScriptOp1ExprElement> m_cache_Op1Expr;
public:
    std::shared_ptr<ALittleScriptOp1ExprElement> GetOp1Expr()
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
private:
    bool m_flag_VarAssignExpr = false;
    std::shared_ptr<ALittleScriptVarAssignExprElement> m_cache_VarAssignExpr;
public:
    std::shared_ptr<ALittleScriptVarAssignExprElement> GetVarAssignExpr()
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
private:
    bool m_flag_OpAssignExpr = false;
    std::shared_ptr<ALittleScriptOpAssignExprElement> m_cache_OpAssignExpr;
public:
    std::shared_ptr<ALittleScriptOpAssignExprElement> GetOpAssignExpr()
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
};

#endif // _ALITTLE_ALittleScriptAllExprElement_H_
