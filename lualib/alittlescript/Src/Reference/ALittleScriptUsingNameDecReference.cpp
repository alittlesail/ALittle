#include "ALittleScriptUsingNameDecReference.h"

#include "../Generate/ALittleScriptUsingDecElement.h"

int ALittleScriptUsingNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::DEFINE_NAME;
}

ABnfGuessError ALittleScriptUsingNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    auto parent = element->GetParent();
    if (std::dynamic_pointer_cast<ALittleScriptUsingDecElement>(parent))
        return parent->GuessTypes(guess_list);
    guess_list.resize(0);
    return nullptr;
}

ABnfGuessError ALittleScriptUsingNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetElementText().find("___") == 0)
        return ABnfGuessError(element, u8"using��������3���»��߿�ͷ");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"δ֪����");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"�ظ�����");
    return nullptr;
}
