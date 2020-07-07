#include "ALittleScriptConstValueReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"

ABnfGuessError ALittleScriptConstValueReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);

    const auto& text = element->GetElementText();

    auto* index = GetIndex();

    if (element->GetNumber() != nullptr)
    {
        if (ALittleScriptUtility::IsInt(element->GetNumber()))
        {
            auto it = index->sPrimitiveGuessListMap.find("int");
            if (it != index->sPrimitiveGuessListMap.end()) guess_list = it->second;
        }
        else
        {
            auto it = index->sPrimitiveGuessListMap.find("double");
            if (it != index->sPrimitiveGuessListMap.end()) guess_list = it->second;
        }

    }
    else if (element->GetText() != nullptr)
    {
        auto it = index->sPrimitiveGuessListMap.find("string");
        if (it != index->sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else if (text == "true" || text == "false")
    {
        auto it = index->sPrimitiveGuessListMap.find("bool");
        if (it != index->sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else if (text == "null")
    {
        guess_list = index->sConstNullGuess;
    }
    else
    {
        return ABnfGuessError(element, u8"未知的常量类型:" + text);
    }

    return nullptr;
}
