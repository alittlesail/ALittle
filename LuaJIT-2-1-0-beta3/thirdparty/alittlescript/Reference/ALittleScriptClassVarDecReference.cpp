#include "ALittleScriptClassVarDecReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptClassVarValueDecElement.h"
#include "../Generate/ALittleScriptConstValueElement.h"
#include "../Generate/ALittleScriptOpNewStatElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"

ABnfGuessError ALittleScriptClassVarDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto all_type = element->GetAllType();
    if (all_type != nullptr)
    {
        auto error = all_type->GuessTypes(guess_list);
        if (error) return error;
        auto class_element_dec = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(element->GetParent());
        if (class_element_dec == nullptr) return ABnfGuessError(element, u8"父节点不是ALittleScriptClassElementDecElement类型");

        bool is_native = ALittleScriptUtility::IsNative(class_element_dec->GetModifierList());
        for (int i = 0; i < guess_list.size(); ++i)
        {
            auto guess = std::dynamic_pointer_cast<ALittleScriptGuessList>(guess_list[i]);
            if (guess != nullptr && guess->is_native != is_native)
            {
                guess->is_native = is_native;
                guess->UpdateValue();
            }
        }
        return nullptr;
    }

    guess_list.resize(0);
    return nullptr;
}

ABnfGuessError ALittleScriptClassVarDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"重复定义");

    // 检查赋值表达式
    auto value_dec = element->GetClassVarValueDec();
    if (value_dec != nullptr)
    {
        auto const_value = value_dec->GetConstValue();
        if (const_value != nullptr)
        {
            ABnfGuessPtr guess;
            error = const_value->GuessType(guess);
            if (error) return error;

            error = ALittleScriptOp::GuessTypeEqual(guess_list[0], const_value, guess, true, false);
            if (error)
                return ABnfGuessError(error.element, u8"等号左边的变量和表达式的类型不同:" + error.error);
        }

        auto op_new_stat = value_dec->GetOpNewStat();
        if (op_new_stat != nullptr)
        {
            ABnfGuessPtr guess;
            error = op_new_stat->GuessType(guess);
            if (error) return error;

            if (!std::dynamic_pointer_cast<ALittleScriptGuessList>(guess) && !std::dynamic_pointer_cast<ALittleScriptGuessMap>(guess))
                return ABnfGuessError(op_new_stat, u8"成员变量初始化只能赋值List或者Map或者常量");

            error = ALittleScriptOp::GuessTypeEqual(guess_list[0], op_new_stat, guess, true, false);
            if (error)
                return ABnfGuessError(error.element, u8"等号左边的变量和表达式的类型不同:" + error.error);
        }
    }

    return nullptr;

}
