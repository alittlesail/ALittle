#include "ALittleScriptConstValueReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

ABnfGuessError ALittleScriptConstValueReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);

    const auto& text = element->GetElementText();

    if (element->GetNumber() != nullptr)
    {
        if (ALittleScriptUtility::IsInt(element->GetNumber()))
        {
            const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("int");
            if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
        }
        else
        {
            const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("double");
            if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
        }

    }
    else if (element->GetText() != nullptr)
    {
        const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("string");
        if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else if (text == "true" || text == "false")
    {
        const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find("bool");
        if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else if (text == "null")
    {
        guess_list = ALittleScriptStatic::Inst().sConstNullGuess;
    }
    else
    {
        return ABnfGuessError(element, u8"δ֪�ĳ�������:" + text);
    }

    return nullptr;
}
