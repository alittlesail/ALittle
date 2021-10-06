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
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    // ����ж�������
    auto all_type = element->GetAllType();
    if (all_type != nullptr) return all_type->GuessTypes(guess_list);

    // ���û�ж�������
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
        // ȡ�������Ķ���
        auto value_stat = in_condition->GetValueStat();
        if (value_stat == nullptr)
            return ABnfGuessError(element, u8"Forû�б��������޷��Ƶ�����");

        // ��ȡ�����б�
        const auto& pair_dec_list = in_condition->GetForPairDecList();
        // �����ǵڼ��������û���ҵ�����ô���ǵ�0����������ҵ��Ǿ�+1
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
        // ��ȡѭ�����������
        std::vector<ABnfGuessPtr> value_guess_list;
        auto error = value_stat->GuessTypes(value_guess_list);
        if (error) return error;
        // ����List
        if (value_guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessList>(value_guess_list[0]))
        {
            // ����List��keyʹ��auto����ô��Ĭ����int����
            if (index == 0)
            {
                if (value_guess_list[0]->is_const)
                {
                    const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("const int");
                    if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
                }
                else
                {
                    const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("int");
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
        // ����Map
        else if (value_guess_list.size() == 1 && std::dynamic_pointer_cast<ALittleScriptGuessMap>(value_guess_list[0]))
        {
            // �����key����ô��ȡkey������
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
            // �����value����ô��ȡvalue������
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
        // �����pairs����
        else if (ALittleScriptUtility::IsPairsFunction(value_guess_list))
        {
            guess_list.push_back(value_guess_list[2]);
        }
    }

    return nullptr;
}
