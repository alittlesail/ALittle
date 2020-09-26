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
    const std::vector<std::shared_ptr<ALittleScriptModifierElement>>& GetModifierList();
private:
    bool m_flag_IfExpr = false;
    std::shared_ptr<ALittleScriptIfExprElement> m_cache_IfExpr;
public:
    std::shared_ptr<ALittleScriptIfExprElement> GetIfExpr();
private:
    bool m_flag_EmptyExpr = false;
    std::shared_ptr<ALittleScriptEmptyExprElement> m_cache_EmptyExpr;
public:
    std::shared_ptr<ALittleScriptEmptyExprElement> GetEmptyExpr();
private:
    bool m_flag_WhileExpr = false;
    std::shared_ptr<ALittleScriptWhileExprElement> m_cache_WhileExpr;
public:
    std::shared_ptr<ALittleScriptWhileExprElement> GetWhileExpr();
private:
    bool m_flag_ForExpr = false;
    std::shared_ptr<ALittleScriptForExprElement> m_cache_ForExpr;
public:
    std::shared_ptr<ALittleScriptForExprElement> GetForExpr();
private:
    bool m_flag_DoWhileExpr = false;
    std::shared_ptr<ALittleScriptDoWhileExprElement> m_cache_DoWhileExpr;
public:
    std::shared_ptr<ALittleScriptDoWhileExprElement> GetDoWhileExpr();
private:
    bool m_flag_ReturnExpr = false;
    std::shared_ptr<ALittleScriptReturnExprElement> m_cache_ReturnExpr;
public:
    std::shared_ptr<ALittleScriptReturnExprElement> GetReturnExpr();
private:
    bool m_flag_ThrowExpr = false;
    std::shared_ptr<ALittleScriptThrowExprElement> m_cache_ThrowExpr;
public:
    std::shared_ptr<ALittleScriptThrowExprElement> GetThrowExpr();
private:
    bool m_flag_FlowExpr = false;
    std::shared_ptr<ALittleScriptFlowExprElement> m_cache_FlowExpr;
public:
    std::shared_ptr<ALittleScriptFlowExprElement> GetFlowExpr();
private:
    bool m_flag_AssertExpr = false;
    std::shared_ptr<ALittleScriptAssertExprElement> m_cache_AssertExpr;
public:
    std::shared_ptr<ALittleScriptAssertExprElement> GetAssertExpr();
private:
    bool m_flag_WrapExpr = false;
    std::shared_ptr<ALittleScriptWrapExprElement> m_cache_WrapExpr;
public:
    std::shared_ptr<ALittleScriptWrapExprElement> GetWrapExpr();
private:
    bool m_flag_Op1Expr = false;
    std::shared_ptr<ALittleScriptOp1ExprElement> m_cache_Op1Expr;
public:
    std::shared_ptr<ALittleScriptOp1ExprElement> GetOp1Expr();
private:
    bool m_flag_VarAssignExpr = false;
    std::shared_ptr<ALittleScriptVarAssignExprElement> m_cache_VarAssignExpr;
public:
    std::shared_ptr<ALittleScriptVarAssignExprElement> GetVarAssignExpr();
private:
    bool m_flag_OpAssignExpr = false;
    std::shared_ptr<ALittleScriptOpAssignExprElement> m_cache_OpAssignExpr;
public:
    std::shared_ptr<ALittleScriptOpAssignExprElement> GetOpAssignExpr();
};

#endif // _ALITTLE_ALittleScriptAllExprElement_H_
