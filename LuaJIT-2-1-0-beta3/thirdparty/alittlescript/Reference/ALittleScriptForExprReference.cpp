#include "ALittleScriptForExprReference.h"

#include "../Generate/ALittleScriptForConditionElement.h"
#include "../Generate/ALittleScriptForStepConditionElement.h"
#include "../Generate/ALittleScriptForInConditionElement.h"
#include "../Generate/ALittleScriptForStartStatElement.h"
#include "../Generate/ALittleScriptForPairDecElement.h"
#include "../Generate/ALittleScriptVarAssignNameDecElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptForEndStatElement.h"
#include "../Generate/ALittleScriptForStepStatElement.h"

#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptOp.h"

ABnfGuessError ALittleScriptForExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto for_condition = element->GetForCondition();
    if (for_condition == nullptr) return nullptr;

    auto for_pair_dec = for_condition->GetForPairDec();
    if (for_pair_dec == nullptr) return nullptr;

    auto step_condition = for_condition->GetForStepCondition();
    auto in_condition = for_condition->GetForInCondition();
    if (step_condition != nullptr)
    {
        auto for_start_stat = step_condition->GetForStartStat();
        if (for_start_stat == nullptr) return nullptr;

        ABnfGuessPtr start_guess;
        auto error = for_pair_dec->GuessType(start_guess);
        if (error) return error;
        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(start_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(start_guess))
            return ABnfGuessError(for_pair_dec->GetVarAssignNameDec(), u8"这个变量必须是int或long类型");

        auto value_stat = for_start_stat->GetValueStat();
        if (value_stat == nullptr)
            return ABnfGuessError(for_pair_dec->GetVarAssignNameDec(), u8"没有初始化表达式");

        int return_count = 0;
        std::vector<ABnfGuessPtr> guess_list;
        error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(value_stat, u8"等号右边的表达式类型必须只能是一个返回值");

        ABnfGuessPtr guess;
        error = value_stat->GuessType(guess);
        if (error) return error;
        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(guess) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(guess) && !std::dynamic_pointer_cast<ALittleScriptGuessDouble>(guess))
            return ABnfGuessError(value_stat, u8"等号右边的表达式类型必须是int,long,double 不能是:" + guess->GetValue());

        // 结束表达式
        auto end_stat = step_condition->GetForEndStat();
        auto step_stat = step_condition->GetForStepStat();

        if (end_stat == nullptr || end_stat->GetValueStat() == nullptr) return ABnfGuessError(element, u8"必须有结束表达式");
        if (step_stat == nullptr || step_stat->GetValueStat() == nullptr) return ABnfGuessError(element, u8"必须有步长表达式");

        ABnfGuessPtr end_guess;
        error = end_stat->GetValueStat()->GuessType(end_guess);
        if (error) return error;
        if (!std::dynamic_pointer_cast<ALittleScriptGuessBool>(end_guess))
            return ABnfGuessError(end_stat, u8"for的结束条件表达式类型必须是bool, 不能是:" + end_guess->GetValue());

        // 返回值
        return_count = 0;
        guess_list.resize(0);
        error = ALittleScriptUtility::CalcReturnCount(step_stat->GetValueStat(), return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(value_stat, u8"for的步长条件表达式类型必须只能是一个返回值");

        ABnfGuessPtr step_guess;
        error = step_stat->GetValueStat()->GuessType(step_guess);
        if (error) return error;
        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(step_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessDouble>(step_guess) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(step_guess))
            return ABnfGuessError(step_stat, u8"for的步长条件表达式类型必须是int,double,long, 不能是:" + end_guess->GetValue());
    }
    else if (in_condition != nullptr)
    {
        auto value_stat = in_condition->GetValueStat();
        if (value_stat == nullptr) return nullptr;

        int return_count = 0;
        std::vector<ABnfGuessPtr> return_guess_list;
        auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, return_guess_list);
        if (error) return error;
        if (ALittleScriptUtility::IsPairsFunction(return_guess_list))
            return_count = 1;
        if (return_count != 1)
            return ABnfGuessError(value_stat, u8"for的遍历对象必须只能是一个返回值");

        const auto& pair_dec_list_temp = in_condition->GetForPairDecList();
        std::vector<std::shared_ptr<ALittleScriptForPairDecElement>> pair_dec_list;
        pair_dec_list.push_back(for_pair_dec);
        for (auto& pair_dec : pair_dec_list_temp) pair_dec_list.push_back(pair_dec);

        std::vector<ABnfGuessPtr> guess_list;
        error = value_stat->GuessTypes(guess_list);
        if (error) return error;

        // 检查List
        if (guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessList>(guess_list[0]))
        {
            auto guess = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess_list[0]);

            // for变量必须是2个
            if (pair_dec_list.size() != 2)
                return ABnfGuessError(in_condition, u8"这里参数数量必须是2个");

            // 第一个参数必须是 int或者long
            ABnfGuessPtr key_guess_type;
            error = pair_dec_list[0]->GuessType(key_guess_type);
            if (error) return error;
            if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(key_guess_type) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(key_guess_type))
                return ABnfGuessError(pair_dec_list[0], u8"这个变量必须是int或long类型");

            // 第二个参数必须和List元素相等
            ABnfGuessPtr value_guess_type;
            error = pair_dec_list[1]->GuessType(value_guess_type);
            if (error) return error;
            auto sub_type = guess->sub_type.lock();
            if (guess_list[0]->is_const && !sub_type->is_const)
            {
                sub_type = sub_type->Clone();
                sub_type->is_const = true;
                sub_type->UpdateValue();
                element->GetFile()->AddGuessType(sub_type);
            }
            error = ALittleScriptOp::GuessTypeEqual(sub_type, pair_dec_list[1], value_guess_type, false, false);
            if (error)
                return ABnfGuessError(error.element, u8"变量格式错误，不能是:" + value_guess_type->GetValue() + " :" + error.error);
            return nullptr;
        }

        // 检查Map
        if (guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess_list[0]))
        {
            auto guess_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess_list[0]);

            // for变量必须是2个
            if (pair_dec_list.size() != 2)
                return ABnfGuessError(in_condition, u8"这里参数数量必须是2个");

            // 第一个参数必须和Map的key元素相等
            ABnfGuessPtr key_guess_type;
            error = pair_dec_list[0]->GuessType(key_guess_type);
            if (error) return error;
            auto map_key_type = guess_map->key_type.lock();
            if (guess_list[0]->is_const && !map_key_type->is_const)
            {
                map_key_type = map_key_type->Clone();
                map_key_type->is_const = true;
                map_key_type->UpdateValue();
                element->GetFile()->AddGuessType(map_key_type);
            }
            error = ALittleScriptOp::GuessTypeEqual(map_key_type, pair_dec_list[0], key_guess_type, false, false);
            if (error)
                return ABnfGuessError(error.element, u8"key变量格式错误，不能是:" + key_guess_type->GetValue() + " :" + error.error);

            // 第二个参数必须和Map的value元素相等
            ABnfGuessPtr value_guess_type;
            error = pair_dec_list[1]->GuessType(value_guess_type);
            if (error) return error;
            auto map_value_type = guess_map->value_type.lock();
            if (guess_list[0]->is_const && !map_value_type->is_const)
            {
                map_value_type = map_value_type->Clone();
                map_value_type->is_const = true;
                map_value_type->UpdateValue();
                element->GetFile()->AddGuessType(map_value_type);
            }
            error = ALittleScriptOp::GuessTypeEqual(map_value_type, pair_dec_list[1], value_guess_type, false, false);
            if (error)
                return ABnfGuessError(error.element, u8"value变量格式错误，不能是:" + value_guess_type->GetValue() + " :" + error.error);
            return nullptr;
        }

        // 检查迭代函数
        if (ALittleScriptUtility::IsPairsFunction(guess_list)) return nullptr;

        return ABnfGuessError(value_stat, u8"遍历对象类型必须是List,Map或者迭代函数");
    }

    if (element->GetAllExpr() == nullptr && element->GetForBody() == nullptr)
        return ABnfGuessError(element, u8"for没有循环体");

    return nullptr;
}
