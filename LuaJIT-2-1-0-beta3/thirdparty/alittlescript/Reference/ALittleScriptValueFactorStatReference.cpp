#include "ALittleScriptValueFactorStatReference.h"

#include "../Generate/ALittleScriptPropertyValueElement.h"
#include "../Generate/ALittleScriptReflectValueElement.h"
#include "../Generate/ALittleScriptWrapValueStatElement.h"
#include "../Generate/ALittleScriptMethodParamTailDecElement.h"
#include "../Generate/ALittleScriptConstValueElement.h"
#include "../Generate/ALittleScriptCoroutineStatElement.h"
#include "../Generate/ALittleScriptPathsValueElement.h"

ABnfGuessError ALittleScriptValueFactorStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    if (element->GetPropertyValue() != nullptr)
        return element->GetPropertyValue()->GuessTypes(guess_list);
    else if (element->GetReflectValue() != nullptr)
        return element->GetReflectValue()->GuessTypes(guess_list);
    else if (element->GetConstValue() != nullptr)
        return element->GetConstValue()->GuessTypes(guess_list);
    else if (element->GetWrapValueStat() != nullptr)
        return element->GetWrapValueStat()->GuessTypes(guess_list);
    else if (element->GetMethodParamTailDec() != nullptr)
        return element->GetMethodParamTailDec()->GuessTypes(guess_list);
    else if (element->GetCoroutineStat() != nullptr)
        return element->GetCoroutineStat()->GuessTypes(guess_list);
    else if (element->GetPathsValue() != nullptr)
        return element->GetPathsValue()->GuessTypes(guess_list);
    guess_list.resize(0);
    return nullptr;
}
