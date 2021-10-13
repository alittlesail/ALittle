#include "ALittleScriptReflectValueReference.h"

#include "../Generate/ALittleScriptReflectCustomTypeElement.h"
#include "../Generate/ALittleScriptCustomTypeElement.h"
#include "../Generate/ALittleScriptReflectValueElement.h"
#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Generate/ALittleScriptReflectValueStatElement.h"
#include "../Generate/ALittleScriptReflectCustomTypeElement.h"
#include "../Generate/ALittleScriptReflectValueStatElement.h"

#include "../Guess/ALittleScriptGuessStruct.h"
#include "../Guess/ALittleScriptGuessClass.h"
#include "../Guess/ALittleScriptGuessTemplate.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptReflectValueReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto* index = GetIndex();
    if (index == nullptr) return ABnfGuessError(element, u8"不在工程中");
    guess_list.resize(0);

    ABnfGuessPtr guess;
    if (element->GetReflectCustomType() != nullptr)
    {
        auto custom_type = element->GetReflectCustomType()->GetCustomType();
        if (custom_type == nullptr) return nullptr;

        auto error = custom_type->GuessType(guess);
        if (error) return error;
    }
    else if (element->GetReflectValueStat() != nullptr)
    {
        auto value_stat = element->GetReflectValueStat()->GetValueStat();
        if (value_stat == nullptr) return nullptr;

        auto error = value_stat->GuessType(guess);
        if (error) return error;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess))
        return index->FindALittleStructGuessList("ALittle", u8"StructInfo", guess_list);
    else if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        return index->FindALittleStructGuessList("ALittle", u8"ClassInfo", guess_list);
    else if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
    {
        const auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess_template->template_extends.lock()) || guess_template->is_class)
            return index->FindALittleStructGuessList("ALittle", u8"ClassInfo", guess_list);
        else if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_template->template_extends.lock())  || guess_template->is_struct)
            return index->FindALittleStructGuessList("ALittle", u8"StructInfo", guess_list);
    }
    return nullptr;
}

ABnfGuessError ALittleScriptReflectValueReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    ABnfGuessPtr guess;
    if (element->GetReflectCustomType() != nullptr)
    {
        auto custom_type = element->GetReflectCustomType()->GetCustomType();
        if (custom_type == nullptr) return ABnfGuessError(element, u8"请填写类型");

        auto error = custom_type->GuessType(guess);
        if (error) return error;
    }
    else if (element->GetReflectValueStat() != nullptr)
    {
        auto value_stat = element->GetReflectValueStat()->GetValueStat();
        if (value_stat == nullptr) return ABnfGuessError(element, u8"请填写表达式");

        int return_count = 0;
        std::vector<ABnfGuessPtr> guess_list;
        auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(value_stat, u8"表达式必须只能是一个返回值");

        error = value_stat->GuessType(guess);
        if (error) return error;
    }

    if (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess) || std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess))
        return nullptr;

    if (std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess))
    {
        const auto guess_template = std::dynamic_pointer_cast<ALittleScriptGuessTemplate>(guess);
        if (std::dynamic_pointer_cast<ALittleScriptGuessClass>(guess_template->template_extends.lock()) || guess_template->is_class)
            return nullptr;
        
        if (element->GetReflectCustomType() != nullptr
            && (std::dynamic_pointer_cast<ALittleScriptGuessStruct>(guess_template->template_extends.lock()) || guess_template->is_struct))
            return nullptr;
    }

    return ABnfGuessError(element, u8"反射对象必须是struct或者是class以及class对象");
}
