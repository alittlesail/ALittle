#include "ALittleScriptGenericTypeReference.h"

#include "../Generate/ALittleScriptGenericListTypeElement.h"
#include "../Generate/ALittleScriptAllTypeElement.h"
#include "../Generate/ALittleScriptGenericMapTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorTypeElement.h"
#include "../Generate/ALittleScriptCoroutineModifierElement.h"
#include "../Generate/ALittleScriptGenericFunctorParamTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorParamOneTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorParamTailElement.h"
#include "../Generate/ALittleScriptGenericFunctorReturnTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorReturnOneTypeElement.h"
#include "../Generate/ALittleScriptGenericFunctorReturnTailElement.h"

#include "../Guess/ALittleScriptGuessList.h"
#include "../Guess/ALittleScriptGuessMap.h"
#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessParamTail.h"
#include "../Guess/ALittleScriptGuessReturnTail.h"
#include "../Index/ALittleScriptFileClass.h"

ABnfGuessError ALittleScriptGenericTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);

    // ����List
    if (element->GetGenericListType() != nullptr)
    {
        auto dec = element->GetGenericListType();
        auto all_type = dec->GetAllType();
        if (all_type == nullptr) return nullptr;

        ABnfGuessPtr guess;
        auto error = all_type->GuessType(guess);
        if (error) return error;

        auto info = std::static_pointer_cast<ABnfGuess>(std::make_shared<ALittleScriptGuessList>(guess, false, false));
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    // ����Map
    else if (element->GetGenericMapType() != nullptr)
    {
        auto dec = element->GetGenericMapType();
        const auto& all_type_list = dec->GetAllTypeList();
        if (all_type_list.size() != 2) return nullptr;

        ABnfGuessPtr key_guess;
        auto error = all_type_list[0]->GuessType(key_guess);
        if (error) return error;

        ABnfGuessPtr value_guess;
        error = all_type_list[1]->GuessType(value_guess);
        if (error) return error;

        auto info = std::static_pointer_cast<ABnfGuess>(
	        std::make_shared<ALittleScriptGuessMap>(key_guess, value_guess, false));
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }
    // ������
    else if (element->GetGenericFunctorType() != nullptr)
    {
        auto dec = element->GetGenericFunctorType();

        auto info = std::make_shared<ALittleScriptGuessFunctor>(element);
        // �����ǲ���const
        info->const_modifier = dec->GetAllTypeConst() != nullptr;
        // �����ǲ���await
        info->await_modifier = (dec->GetCoroutineModifier() != nullptr && dec->GetCoroutineModifier()->GetElementText() == "await");

        // �������
        auto param_type = dec->GetGenericFunctorParamType();
        if (param_type != nullptr)
        {
            const auto& param_one_list = param_type->GetGenericFunctorParamOneTypeList();
            for (size_t i = 0; i < param_one_list.size(); ++i)
            {
                auto param_one = param_one_list[i];
                auto all_type = param_one->GetAllType();
                if (all_type != nullptr)
                {
                    ABnfGuessPtr guess;
                    auto error = all_type->GuessType(guess);
                    if (error) return error;
                    info->param_list.push_back(guess);
                    info->param_nullable_list.push_back(false);
                    info->param_name_list.push_back(guess->GetValue());
                }
                else
                {
                    auto param_tail = param_one->GetGenericFunctorParamTail();
                    if (param_tail == nullptr)
                        return ABnfGuessError(param_one, u8"δ֪����");
                    if (i + 1 != param_one_list.size())
                        return ABnfGuessError(param_one, u8"����ռλ�����붨�������");
                    auto cache = std::static_pointer_cast<ABnfGuess>(
	                    std::make_shared<ALittleScriptGuessParamTail>(param_tail->GetElementText()));
                    info->param_tail = cache;
                    element->GetFile()->AddGuessType(cache);
                }
            }
        }

        // ������ֵ
        auto return_type = dec->GetGenericFunctorReturnType();
        if (return_type != nullptr)
        {
            const auto& return_one_list = return_type->GetGenericFunctorReturnOneTypeList();
            for (size_t i = 0; i < return_one_list.size(); ++i)
            {
                auto return_one = return_one_list[i];
                auto all_type = return_one->GetAllType();
                if (all_type != nullptr)
                {
                    ABnfGuessPtr guess;
                    auto error = all_type->GuessType(guess);
                    if (error) return error;
                    info->return_list.push_back(guess);
                }
                else
                {
                    auto return_tail = return_one->GetGenericFunctorReturnTail();
                    if (return_tail == nullptr)
                        return ABnfGuessError(return_one, u8"δ֪����");
                    if (i + 1 != return_one_list.size())
                        return ABnfGuessError(return_one, u8"����ֵռλ�����붨�������");
                    auto cache = std::static_pointer_cast<ABnfGuess>(
	                    std::make_shared<ALittleScriptGuessParamTail>(return_tail->GetElementText()));
                    info->return_tail = cache;
                    element->GetFile()->AddGuessType(cache);
                }
            }
        }
        info->UpdateValue();
        element->GetFile()->AddGuessType(info);
        guess_list.push_back(info);
    }

    return nullptr;
}

ABnfGuessError ALittleScriptGenericTypeReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    
    // ����List
    if (element->GetGenericListType() != nullptr)
    {
        auto dec = element->GetGenericListType();
        const auto all_type = dec->GetAllType();
        if (all_type == nullptr) return ABnfGuessError(element, u8"û�ж���Ԫ������");
    }
    // ����Map
    else if (element->GetGenericMapType() != nullptr)
    {
        auto dec = element->GetGenericMapType();
        const auto& all_type_list = dec->GetAllTypeList();
        if (all_type_list.size() != 2) return ABnfGuessError(element, u8"û�ж�������Ԫ������");
    }
    // ������
    else if (element->GetGenericFunctorType() != nullptr)
    {
        auto dec = element->GetGenericFunctorType();
        if (dec->GetStringList().size() == 0) return ABnfGuessError(element, u8"û�ж��庯������");
    }

    return nullptr;
}
