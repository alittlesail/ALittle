#include "ALittleScriptWrapValueStatReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptWrapValueStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    const auto value_stat = element->GetValueStat();
    if (value_stat != nullptr)
    {
        int return_count = 0;
        auto error = ALittleScriptUtility::CalcReturnCount(value_stat, return_count, guess_list);
        if (error) return error;
        if (return_count != 1) return ABnfGuessError(value_stat, u8"���ʽ����ֻ����һ������ֵ");
        return nullptr;
    }
    guess_list.resize(0);
    return nullptr;
}

ABnfGuessError ALittleScriptWrapValueStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    if (element->GetValueStat() == nullptr) return ABnfGuessError(element, u8"���ﲻ��Ϊ��");
    return nullptr;
}
