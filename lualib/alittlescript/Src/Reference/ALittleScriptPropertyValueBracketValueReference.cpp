#include "ALittleScriptPropertyValueBracketValueReference.h"

#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"
#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptPropertyValueFirstTypeElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"

#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptOp.h"

ABnfGuessError ALittleScriptPropertyValueBracketValueReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);

    // ��ȡ���ڵ�
    const auto property_value_suffix = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(element->GetParent());
    auto property_value = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(property_value_suffix->GetParent());
    auto property_value_first_type = property_value->GetPropertyValueFirstType();
    const auto& suffix_list = property_value->GetPropertyValueSuffixList();

    // ��ȡ����λ��
    int index = -1;
    for (size_t i = 0; i < suffix_list.size(); ++i)
    {
        if (suffix_list[i] == property_value_suffix)
        {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1) return ABnfGuessError(element, u8"�ڵ�ʧЧ");

    // ��ȡǰһ������
    ABnfGuessPtr pre_type;
    ABnfGuessError error;
    if (index == 0)
        error = property_value_first_type->GuessType(pre_type);
    else
        error = suffix_list[index - 1]->GuessType(pre_type);
    if (error) return error;

    // ��ȡ����
    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(pre_type))
    {
        auto sub_type = std::dynamic_pointer_cast<ALittleScriptGuessList>(pre_type)->sub_type.lock();
        if (sub_type == nullptr) return nullptr;
        if (pre_type->is_const && !sub_type->is_const)
        {
            sub_type = sub_type->Clone();
            sub_type->is_const = true;
            sub_type->UpdateValue();
            element->GetFile()->AddGuessType(sub_type);
        }
        guess_list.push_back(sub_type);
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(pre_type))
    {
        auto value_type = std::dynamic_pointer_cast<ALittleScriptGuessMap>(pre_type)->value_type.lock();
        if (value_type == nullptr) return nullptr;
        if (pre_type->is_const && !value_type->is_const)
        {
            value_type = value_type->Clone();
            value_type->is_const = true;
            value_type->UpdateValue();
            element->GetFile()->AddGuessType(value_type);
        }
        guess_list.push_back(value_type);
    }

    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueBracketValueReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    auto value_stat = element->GetValueStat();
    if (value_stat == nullptr) return ABnfGuessError(element, u8"����д����ֵ");

    // ��ȡ���ڵ�
    const auto property_value_suffix = std::dynamic_pointer_cast<ALittleScriptPropertyValueSuffixElement>(element->GetParent());
    auto property_value = std::dynamic_pointer_cast<ALittleScriptPropertyValueElement>(property_value_suffix->GetParent());
    auto property_value_first_type = property_value->GetPropertyValueFirstType();
    const auto& suffixList = property_value->GetPropertyValueSuffixList();

    // ��ȡ����λ��
    int index = -1;
    for (size_t i = 0; i < suffixList.size(); ++i)
    {
        if (suffixList[i] == property_value_suffix)
        {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1) return ABnfGuessError(element, u8"�ڵ�ʧЧ");

    // ��ȡǰһ������
    ABnfGuessPtr pre_type;
    ABnfGuessError error;
    if (index == 0)
        error = property_value_first_type->GuessType(pre_type);
    else
        error = suffixList[index - 1]->GuessType(pre_type);
    if (error) return error;

    int return_count = 0;
    std::vector<ABnfGuessPtr> guess_list;
    error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
    if (error) return error;
    if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

    ABnfGuessPtr key_guess_type;
    error = value_stat->GuessType(key_guess_type);
    if (error) return error;

    // ��ȡ����
    if (std::dynamic_pointer_cast<ALittleScriptGuessList>(pre_type))
    {
        if (!std::dynamic_pointer_cast<ALittleScriptGuessInt>(key_guess_type) && !std::dynamic_pointer_cast<ALittleScriptGuessLong>(key_guess_type))
            return ABnfGuessError(value_stat, u8"����ֵ�����ͱ�����int������long��������:" + key_guess_type->GetValue());
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessMap>(pre_type))
    {
        const auto pre_type_map = std::dynamic_pointer_cast<ALittleScriptGuessMap>(pre_type);
        error = ALittleScriptOp::GuessTypeEqual(pre_type_map->key_type.lock(), value_stat, key_guess_type, true, false);
        if (error)
            return ABnfGuessError(error.element, u8"����ֵ�����Ͳ�����:" + key_guess_type->GetValue() + " :" + error.error);
    }

    {
        guess_list.resize(0);
        error = element->GuessTypes(guess_list);
        if (error) return error;
        if (guess_list.size() == 0)
            return ABnfGuessError(element, u8"��Ԫ�ز���ֱ��ʹ��[]ȡֵ������cast");
        else if (guess_list.size() != 1)
            return ABnfGuessError(element, u8"�ظ�����");
        return nullptr;
    }
}
