#include "ALittleScriptConstValueReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

ABnfGuessError ALittleScriptConstValueReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);

    const auto& text = element->GetElementText();

    if (element->GetNumber() != nullptr)
    {
        if (ALittleScriptUtility::IsInt(element->GetNumber()))
        {
            auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("int");
            if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
        }
        else
        {
            auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("double");
            if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
        }

    }
    else if (element->GetText() != nullptr)
    {
        auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("string");
        if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else if (text == "true" || text == "false")
    {
        auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("bool");
        if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else if (text == "null")
    {
        guess_list = ALittleScriptStatic::Inst().sConstNullGuess;
    }
    else
    {
        return ABnfGuessError(element, u8"未知的常量类型:" + text);
    }

    return nullptr;
}
