#include "ALittleScriptForPairDecReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptForConditionElement.h"
#include "../Generate/ALittleScriptForStepConditionElement.h"
#include "../Generate/ALittleScriptForStartStatElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptForInConditionElement.h"

#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptForPairDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    // 如果有定义类型
    auto all_type = element->GetAllType();
    if (all_type != nullptr) return all_type->GuessTypes(guess_list);

    // 如果没有定义类型
    auto parent = element->GetParent();
    if (std::dynamic_pointer_cast<ALittleScriptForConditionElement>(parent))
    {
        auto for_condition = std::dynamic_pointer_cast<ALittleScriptForConditionElement>(parent);
        auto step_condition = for_condition->GetForStepCondition();
        if (step_condition != nullptr)
        {
            auto start_stat = step_condition->GetForStartStat();
            if (start_stat != nullptr)
            {
                auto value_stat = start_stat->GetValueStat();
                if (value_stat != nullptr)
                    return value_stat->GuessTypes(guess_list);
            }
        }
        else
        {
            parent = for_condition->GetForInCondition();
        }
    }

    guess_list.resize(0);
    if (std::dynamic_pointer_cast<ALittleScriptForInConditionElement>(parent))
    {
        auto in_condition = std::dynamic_pointer_cast<ALittleScriptForInConditionElement>(parent);
        // 取出遍历的对象
        auto value_stat = in_condition->GetValueStat();
        if (value_stat == nullptr)
            return ABnfGuessError(element, u8"For没有遍历对象，无法推导类型");

        // 获取定义列表
        const auto& pair_dec_list = in_condition->GetForPairDecList();
        // 查找是第几个，如果没有找到，那么就是第0个，如果有找到那就+1
        int index = -1;
        for (int i = 0; i < static_cast<int>(pair_dec_list.size()); ++i)
        {
            if (pair_dec_list[i] == element)
            {
                index = i;
                break;
            }
        }
        if (index < 0)
            index = 0;
        else
            index += 1;
        // 获取循环对象的类型
        std::vector<ABnfGuessPtr> value_guess_list;
        auto error = value_stat->GuessTypes(value_guess_list);
        if (error) return error;
        // 处理List
        if (value_guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessList>(value_guess_list[0]))
        {
            // 对于List的key使用auto，那么就默认是int类型
            if (index == 0)
            {
                if (value_guess_list[0]->is_const)
                {
                    auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("const int");
                    if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
                }
                else
                {
                    auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("int");
                    if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
                }
                return nullptr;
            }
            else if (index == 1)
            {
                auto sub_type = std::dynamic_pointer_cast<ALittleScriptGuessList>(value_guess_list[0])->sub_type.lock();
                if (value_guess_list[0]->is_const && !sub_type->is_const)
                {
                    sub_type = sub_type->Clone();
                    sub_type->is_const = true;
                    sub_type->UpdateValue();
                    element->GetFile()->AddGuessType(sub_type);
                }
                guess_list.push_back(sub_type);
            }
        }
        // 处理Map
        else if (value_guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessMap>(value_guess_list[0]))
        {
            // 如果是key，那么就取key的类型
            if (index == 0)
            {
                auto key_type = std::dynamic_pointer_cast<ALittleScriptGuessMap>(value_guess_list[0])->key_type.lock();
                if (value_guess_list[0]->is_const && !key_type->is_const)
                {
                    key_type = key_type->Clone();
                    key_type->is_const = true;
                    key_type->UpdateValue();
                    element->GetFile()->AddGuessType(key_type);
                }
                guess_list.push_back(key_type);
            }
            // 如果是value，那么就取value的类型
            else if (index == 1)
            {
                auto value_type = std::dynamic_pointer_cast<ALittleScriptGuessMap>(value_guess_list[0])->value_type.lock();
                if (value_guess_list[0]->is_const && !value_type->is_const)
                {
                    value_type = value_type->Clone();
                    value_type->is_const = true;
                    value_type->UpdateValue();
                    element->GetFile()->AddGuessType(value_type);
                }
                guess_list.push_back(value_type);
            }
        }
        // 如果是pairs函数
        else if (ALittleScriptUtility::IsPairsFunction(value_guess_list))
        {
            guess_list.push_back(value_guess_list[2]);
        }
    }

    return nullptr;
}
