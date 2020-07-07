#include "ALittleScriptEnumVarDecReference.h"

#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"

#include "../Generate/ALittleScriptNumberElement.h"

ABnfGuessError ALittleScriptEnumVarDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    auto* index = GetIndex();
    if (element->GetText() != nullptr)
    {
        auto it = index->sPrimitiveGuessListMap.find("string");
        if (it != index->sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
    else
    {
        auto it = index->sPrimitiveGuessListMap.find("int");
        if (it != index->sPrimitiveGuessListMap.end()) guess_list = it->second;
    }
        
    return nullptr;
}

ABnfGuessError ALittleScriptEnumVarDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    if (element->GetNumber() == nullptr) return nullptr;

    if (!ALittleScriptUtility::IsInt(element->GetNumber()))
        return ABnfGuessError(element->GetNumber(), u8"枚举值必须是整数");
    return nullptr;
}
