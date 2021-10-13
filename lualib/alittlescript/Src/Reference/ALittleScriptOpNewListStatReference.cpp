#include "ALittleScriptOpNewListStatReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"

#include "../Guess/ALittleScriptGuessList.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptOpNewListStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"List�б���Ϊ��");

    ABnfGuessPtr guess;
    auto error = value_stat_list[0]->GuessType(guess);
    if (error) return error;
    auto info = std::static_pointer_cast<ABnfGuess>(std::make_shared<ALittleScriptGuessList>(guess, false, false));
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}

ABnfGuessError ALittleScriptOpNewListStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto& value_stat_list = element->GetValueStatList();
    if (value_stat_list.size() == 0)
        return ABnfGuessError(element, u8"���ַ�ʽ������д������������ʹ��new List�ķ�ʽ");

    // �б����������Ԫ�ص����ͱ���͵�һ��Ԫ��һ��
    ABnfGuessPtr value_stat_first;
    auto error = value_stat_list[0]->GuessType(value_stat_first);
    if (error) return error;
    for (size_t i = 1; i < value_stat_list.size(); ++i)
    {
        auto value_stat = value_stat_list[i];
        int return_count = 0;
        std::vector<ABnfGuessPtr> guess_list;
        error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");

        ABnfGuessPtr guess;
        error = value_stat->GuessType(guess);
        if (error) return error;
        if (value_stat_first->GetValue() != guess->GetValue())
            return ABnfGuessError(value_stat_list[i], u8"�б��ڵ�Ԫ�����ͣ�����͵�һ��Ԫ������һ��");
    }
    return nullptr;
}
