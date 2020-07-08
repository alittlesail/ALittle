#include "ALittleScriptStructVarDecReference.h"

#include "../Generate/ALittleScriptAllTypeElement.h"

ABnfGuessError ALittleScriptStructVarDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    auto all_type = element->GetAllType();
    if (all_type != nullptr) return all_type->GuessTypes(guess_list);
    guess_list.resize(0);
    return nullptr;
}
