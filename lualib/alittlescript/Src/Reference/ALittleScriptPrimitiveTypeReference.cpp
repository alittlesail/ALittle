#include "ALittleScriptPrimitiveTypeReference.h"

#include "../Index/ALittleScriptIndex.h"

ABnfGuessError ALittleScriptPrimitiveTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    const auto it = ALittleScriptStatic::Inst().sPrimitiveGuessListMap.find(element->GetElementText());
    if (it != ALittleScriptStatic::Inst().sPrimitiveGuessListMap.end())
    {
        guess_list = it->second;
        return nullptr;
    }
    guess_list.resize(0);
    return nullptr;
}
