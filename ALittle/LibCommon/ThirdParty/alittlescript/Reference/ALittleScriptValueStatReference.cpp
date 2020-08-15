#include "ALittleScriptValueStatReference.h"

#include "../Generate/ALittleScriptOpNewStatElement.h"
#include "../Generate/ALittleScriptOpNewListStatElement.h"
#include "../Generate/ALittleScriptValueOpStatElement.h"
#include "../Generate/ALittleScriptBindStatElement.h"
#include "../Generate/ALittleScriptTcallStatElement.h"
#include "../Generate/ALittleScriptOp2StatElement.h"
#include "../Generate/ALittleScriptIfExprElement.h"
#include "../Generate/ALittleScriptElseIfExprElement.h"
#include "../Generate/ALittleScriptWhileExprElement.h"
#include "../Generate/ALittleScriptDoWhileExprElement.h"

#include "../Guess/ALittleScriptGuessPrimitive.h"
#include "../Index/ALittleScriptOp.h"

ABnfGuessError ALittleScriptValueStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    if (element->GetOpNewStat() != nullptr)
        return element->GetOpNewStat()->GuessTypes(guess_list);
    else if (element->GetOpNewListStat() != nullptr)
        return element->GetOpNewListStat()->GuessTypes(guess_list);
    else if (element->GetValueOpStat() != nullptr)
        return ALittleScriptOp::GuessTypes(element->GetValueOpStat(), guess_list);
    else if (element->GetBindStat() != nullptr)
        return element->GetBindStat()->GuessTypes(guess_list);
    else if (element->GetTcallStat() != nullptr)
        return element->GetTcallStat()->GuessTypes(guess_list);
    else if (element->GetOp2Stat() != nullptr)
    {
        guess_list.resize(0);
        ABnfGuessPtr guess;
        auto error = ALittleScriptOp::GuessType(element->GetOp2Stat(), guess);
        if (error) return error;
        guess_list.push_back(guess);
        return nullptr;
    }

    guess_list.resize(0);
    return nullptr;
}

ABnfGuessError ALittleScriptValueStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto parent = element->GetParent();
    if (std::dynamic_pointer_cast<ALittleScriptIfExprElement>(parent)
        || std::dynamic_pointer_cast<ALittleScriptElseIfExprElement>(parent)
        || std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(parent)
        || std::dynamic_pointer_cast<ALittleScriptDoWhileExprElement>(parent))
    {
        std::vector<ABnfGuessPtr> guess_list;
        auto error = element->GuessTypes(guess_list);
        if (error) return error;
        if (guess_list.size() == 0) return nullptr;

        if (!std::dynamic_pointer_cast<ALittleScriptGuessBool>(guess_list[0]) && guess_list[0]->GetValue() != "null")
            return ABnfGuessError(element, u8"条件语句中的表达式的类型必须是bool或者null");
    }

    return nullptr;
}
