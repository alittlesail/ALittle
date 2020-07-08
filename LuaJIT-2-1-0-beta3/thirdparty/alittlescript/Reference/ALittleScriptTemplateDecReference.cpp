#include "ALittleScriptTemplateDecReference.h"

#include "../Generate/ALittleScriptTemplatePairDecElement.h"

bool ALittleScriptTemplateDecReference::MultiGuessTypes()
{
    return true;
}

ABnfGuessError ALittleScriptTemplateDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    guess_list.resize(0);
    const auto& pair_dec_list = element->GetTemplatePairDecList();
    for (auto& pair_dec : pair_dec_list)
    {
        ABnfGuessPtr guess;
        auto error = pair_dec->GuessType(guess);
        if (error) return error;
        guess_list.push_back(guess);
    }

    return nullptr;
}
