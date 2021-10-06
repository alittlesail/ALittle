#include "ALittleScriptNamespaceDecReference.h"

#include "../Generate/ALittleScriptNamespaceNameDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Guess/ALittleScriptGuessNamespace.h"

ABnfGuessError ALittleScriptNamespaceDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    return ALittleScriptUtility::CheckError(element, element->GetModifierList());
}

ABnfGuessError ALittleScriptNamespaceDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);
    auto name_dec = element->GetNamespaceNameDec();
    if (name_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж���������");

    auto info = std::static_pointer_cast<ABnfGuess>(
	    std::make_shared<ALittleScriptGuessNamespace>(name_dec->GetElementText(), element));
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}

int ALittleScriptNamespaceDecReference::QueryClassificationTag(bool& blur)
{
    auto element = m_element.lock();
    if (element == nullptr) return 0;
    blur = !ALittleScriptUtility::IsLanguageEnable(element->GetModifierList());
    return 0;
}
