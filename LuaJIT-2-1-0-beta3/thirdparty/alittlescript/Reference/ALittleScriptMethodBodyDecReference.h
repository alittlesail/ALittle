
#ifndef _ALITTLE_ALITTLESCRIPTMETHODBODYDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODBODYDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodBodyDecElement.h"

class ALittleScriptMethodNameDecElement;

class ALittleScriptMethodBodyDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodBodyDecElement>
{
public:
    ALittleScriptMethodBodyDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptMethodBodyDecElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptMethodBodyDecReference(element); }
    // 检查表达式是否有return
    static ABnfGuessError CheckAllExpr(const std::vector<ABnfGuessPtr>& return_list, std::shared_ptr<ALittleScriptAllExprElement> all_expr, bool& result);

    // 检查表达式是否有return
    static ABnfGuessError CheckAllExprList(const std::vector<ABnfGuessPtr>& return_list, std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list, bool& result);

private:
    // 检查函数体
    static ABnfGuessError CheckMethodBody(const std::vector<ABnfGuessPtr>& return_list
        , std::shared_ptr<ALittleScriptMethodNameDecElement> method_name_dec
        , std::shared_ptr<ALittleScriptMethodBodyDecElement> method_body_dec);

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODBODYDECREFERENCE_H_