#include "ALittleScriptMethodBodyDecReference.h"

#include "../Generate/ALittleScriptAllExprElement.h"
#include "../Generate/ALittleScriptIfExprElement.h"
#include "../Generate/ALittleScriptElseIfExprElement.h"
#include "../Generate/ALittleScriptElseIfBodyElement.h"
#include "../Generate/ALittleScriptElseExprElement.h"
#include "../Generate/ALittleScriptElseBodyElement.h"
#include "../Generate/ALittleScriptIfBodyElement.h"
#include "../Generate/ALittleScriptDoWhileExprElement.h"
#include "../Generate/ALittleScriptDoWhileBodyElement.h"
#include "../Generate/ALittleScriptWrapExprElement.h"
#include "../Generate/ALittleScriptMethodNameDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptMethodReturnDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptMethodReturnOneDecElement.h"
#include "../Generate/ALittleScriptMethodReturnTailDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"

#include "../Index/ALittleScriptUtility.h"

inline ABnfGuessError ALittleScriptMethodBodyDecReference::CheckAllExpr(const std::vector<ABnfGuessPtr>& return_list, std::shared_ptr<ALittleScriptAllExprElement> all_expr, bool& result)
{
    result = false;
    if (all_expr->GetIfExpr() != nullptr)
    {
        auto if_expr = all_expr->GetIfExpr();
        auto sub_all_expr = if_expr->GetAllExpr();
        auto if_body = if_expr->GetIfBody();
        if (sub_all_expr != nullptr)
        {
            bool sub_result = false;
            auto error = CheckAllExpr(return_list, sub_all_expr, sub_result);
            if (error) return error;
            if (!sub_result) return nullptr;
        }
        else if (if_body != nullptr)
        {
            bool sub_result = false;
            auto error = CheckAllExprList(return_list, if_body->GetAllExprList(), sub_result);
            if (error) return error;
            if (!sub_result) return nullptr;
        }
        else
        {
            return nullptr;
        }

        const auto& else_if_expr_list = if_expr->GetElseIfExprList();
        for (auto& else_if_expr : else_if_expr_list)
        {
            sub_all_expr = else_if_expr->GetAllExpr();
            auto else_if_body = else_if_expr->GetElseIfBody();
            if (sub_all_expr != nullptr)
            {
                bool sub_result = false;
                auto error = CheckAllExpr(return_list, sub_all_expr, sub_result);
                if (error) return error;
                if (!sub_result) return nullptr;
            }
            else if (else_if_body != nullptr)
            {
                bool sub_result = false;
                auto error = CheckAllExprList(return_list, else_if_body->GetAllExprList(), sub_result);
                if (error) return error;
                if (!sub_result) return nullptr;
            }
            else
            {
                return nullptr;
            }
        }

        auto else_expr = if_expr->GetElseExpr();
        if (else_expr == nullptr) return nullptr;

        sub_all_expr = else_expr->GetAllExpr();
        auto else_body = else_expr->GetElseBody();
        if (sub_all_expr != nullptr)
            return CheckAllExpr(return_list, sub_all_expr, result);
        else if (else_body != nullptr)
            return CheckAllExprList(return_list, else_body->GetAllExprList(), result);
        else
            return nullptr;
    }
    /*
    if (all_expr.GetForExpr() != nullptr)
    {
    auto for_expr = all_expr.GetForExpr();
    auto sub_all_expr = for_expr.GetAllExpr();
    auto for_body = for_expr.GetForBody();
    if (sub_all_expr != nullptr)
    return CheckAllExpr(return_list, sub_all_expr, out result);
    else if (for_body != nullptr)
    return CheckAllExprList(return_list, for_body.GetAllExprList(), out result);
    else
    return nullptr;
    }

    if (all_expr.GetWhileExpr() != nullptr)
    {
    auto while_expr = all_expr.GetWhileExpr();
    auto sub_all_expr = while_expr.GetAllExpr();
    auto while_body = while_expr.GetWhileBody();
    if (sub_all_expr != nullptr)
    return CheckAllExpr(return_list, sub_all_expr, out result);
    else if (while_body != nullptr)
    return CheckAllExprList(return_list, while_body.GetAllExprList(), out result);
    else
    return nullptr;
    }
    */
    if (all_expr->GetDoWhileExpr() != nullptr)
    {
        auto do_while_expr = all_expr->GetDoWhileExpr();
        auto do_while_body = do_while_expr->GetDoWhileBody();
        if (do_while_body != nullptr)
            return CheckAllExprList(return_list, do_while_body->GetAllExprList(), result);
        else
            return nullptr;
    }

    if (all_expr->GetReturnExpr() != nullptr)
    {
        result = true;
        // 这里检查return
        return nullptr;
    }

    if (all_expr->GetWrapExpr() != nullptr)
    {
        auto wrap_expr = all_expr->GetWrapExpr();
        return CheckAllExprList(return_list, wrap_expr->GetAllExprList(), result);
    }

    if (all_expr->GetThrowExpr() != nullptr)
    {
        result = true;
        return nullptr;
    }

    return nullptr;
}

// 检查表达式是否有return
ABnfGuessError ALittleScriptMethodBodyDecReference::CheckAllExprList(const std::vector<ABnfGuessPtr>& return_list, std::vector<std::shared_ptr<ALittleScriptAllExprElement>> all_expr_list, bool& result)
{
    result = false;
    // 如果没有就检查子表达式
    int index = -1;
    for (int i = 0; i < all_expr_list.size(); ++i)
    {
        auto all_expr = all_expr_list[i];
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;

        bool sub_result = false;
        auto error = CheckAllExpr(return_list, all_expr_list[i], sub_result);
        if (error) return error;
        if (sub_result)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
        return nullptr;

    for (int i = index + 1; i < all_expr_list.size(); ++i)
    {
        auto all_expr = all_expr_list[i];
        if (!ALittleScriptUtility::IsLanguageEnable(all_expr->GetModifierList()))
            continue;
        return ABnfGuessError(all_expr, u8"当前分支内，从这里开始之后所有语句永远都不会执行到");
    }

    result = true;
    return nullptr;
}

// 检查函数体
ABnfGuessError ALittleScriptMethodBodyDecReference::CheckMethodBody(const std::vector<ABnfGuessPtr>& return_list, std::shared_ptr<ALittleScriptMethodNameDecElement> method_name_dec, std::shared_ptr<ALittleScriptMethodBodyDecElement> method_body_dec)
{
    // 检查return
    if (return_list.size() > 0 && !ALittleScriptUtility::IsRegister(method_name_dec))
    {
        const auto& all_expr_list = method_body_dec->GetAllExprList();
        bool result = false;
        auto error = CheckAllExprList(return_list, all_expr_list, result);
        if (error) return error;
        if (!result)
            return ABnfGuessError(method_name_dec, u8"不是所有分支都有return");
    }

    return nullptr;
}

ABnfGuessError ALittleScriptMethodBodyDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto parent = element->GetParent();

    if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent)) return nullptr;
    if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent)) return nullptr;

    std::vector<ABnfGuessPtr> return_list;
    std::shared_ptr<ALittleScriptMethodReturnDecElement> return_dec;
    std::shared_ptr<ALittleScriptMethodNameDecElement> name_dec;

    if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
    {
        auto getter_dec = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent);
        name_dec = getter_dec->GetMethodNameDec();
        if (name_dec == nullptr) return nullptr;

        auto all_type = getter_dec->GetAllType();
        if (all_type == nullptr) return nullptr;
        ABnfGuessPtr all_type_guess;
        auto error = all_type->GuessType(all_type_guess);
        if (error) return error;
        return_list.push_back(all_type_guess);
        return CheckMethodBody(return_list, name_dec, element);
    }

    if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
    {
        auto method_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent);
        name_dec = method_dec->GetMethodNameDec();
        if (name_dec == nullptr) return nullptr;
        return_dec = method_dec->GetMethodReturnDec();
    }

    if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
    {
        auto static_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent);
        name_dec = static_dec->GetMethodNameDec();
        if (name_dec == nullptr) return nullptr;
        return_dec = static_dec->GetMethodReturnDec();
    }

    if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)) {
        auto global_method_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent);
        name_dec = global_method_dec->GetMethodNameDec();
        if (name_dec == nullptr) return nullptr;
        return_dec = global_method_dec->GetMethodReturnDec();
    }

    if (name_dec == nullptr) return nullptr;

    if (return_dec != nullptr)
    {
        const auto& return_one_list = return_dec->GetMethodReturnOneDecList();
        for (size_t i = 0; i < return_one_list.size(); ++i)
        {
            auto return_one = return_one_list[i];
            auto all_type = return_one->GetAllType();
            auto return_tail = return_one->GetMethodReturnTailDec();
            if (all_type != nullptr)
            {
                ABnfGuessPtr all_type_guess;
                auto error = all_type->GuessType(all_type_guess);
                if (error) return error;
                return_list.push_back(all_type_guess);
            }
            else if (return_tail != nullptr)
            {
                if (i + 1 != return_one_list.size())
                    return ABnfGuessError(return_one, u8"返回值占位符必须定义在最后");
                ABnfGuessPtr return_tail_guess;
                auto error = return_tail->GuessType(return_tail_guess);
                if (error) return error;
                return_list.push_back(return_tail_guess);
            }
        }
    }

    return CheckMethodBody(return_list, name_dec, element);
}
