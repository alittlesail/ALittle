#include "ALittleScriptClassExtendsDecReference.h"

#include "../Generate/ALittleScriptNamespaceNameDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptFileClass.h"

ALittleScriptClassExtendsDecReference::ALittleScriptClassExtendsDecReference(ABnfElementPtr p_element) : ALittleScriptReferenceTemplate<ALittleScriptClassExtendsDecElement>(p_element)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    if (element->GetNamespaceNameDec() != nullptr)
        m_namespace_name = element->GetNamespaceNameDec()->GetElementText();
    else
        m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);

    m_key = "";
    if (element->GetClassNameDec() != nullptr)
        m_key = element->GetClassNameDec()->GetElementText();
}

ABnfGuessError ALittleScriptClassExtendsDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"½ÚµãÊ§Ð§");
    auto class_name_dec = element->GetClassNameDec();
    if (class_name_dec == nullptr)
    {
        guess_list.resize(0);
        return nullptr;
    }

    return class_name_dec->GuessTypes(guess_list);
}

bool ALittleScriptClassExtendsDecReference::QueryCompletion(std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;
    {
        auto* index = GetIndex();
        std::vector<std::shared_ptr<ABnfElement>> dec_list;
        index->FindALittleNameDecList(
            ABnfElementType::CLASS_NAME, element->GetFile(), m_namespace_name, u8"", true, dec_list);

        for (auto& dec : dec_list)
            list.emplace_back(dec->GetElementText(), ALittleScriptIconType::CLASS);
    }
    return true;
}
