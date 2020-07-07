#include "ALittleScriptPrimitiveTypeReference.h"

#include "../Index/ALittleScriptIndex.h"

ABnfGuessError ALittleScriptPrimitiveTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto* index = GetIndex();
    if (index == nullptr) return  ABnfGuessError(nullptr, u8"不在工程中");
    auto it = index->sPrimitiveGuessListMap.find(element->GetElementText());
    if (it != index->sPrimitiveGuessListMap.end())
    {
        guess_list = it->second;
        return nullptr;
    }
    guess_list.resize(0);
    return nullptr;
}
