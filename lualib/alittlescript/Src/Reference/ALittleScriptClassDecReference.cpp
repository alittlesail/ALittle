#include "ALittleScriptClassDecReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptClassNameDecElement.h"
#include "../Generate/ALittleScriptTemplateDecElement.h"
#include "../Guess/ALittleScriptGuessClass.h"

ALittleScriptClassDecReference::ALittleScriptClassDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptClassDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
}

ABnfGuessError ALittleScriptClassDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto name_dec = element->GetClassNameDec();
    if (name_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж�������");

    const auto body_dec = element->GetClassBodyDec();
    if (body_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж�������");

    return nullptr;
}

ABnfGuessError ALittleScriptClassDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);

    auto name_dec = element->GetClassNameDec();
    if (name_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж�������");

    const auto body_dec = element->GetClassBodyDec();
    if (body_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж�������");

    auto namespace_element_dec = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(element->GetParent());
    if (namespace_element_dec == nullptr)
        return ABnfGuessError(element, u8"ALittleScriptClassDecReference�ĸ��ڵ㲻��ALittleScriptNamespaceElementDecElement");

    const bool is_native = ALittleScriptUtility::IsNative(namespace_element_dec->GetModifierList());
    auto info = std::make_shared<ALittleScriptGuessClass>(m_namespace_name, name_dec->GetElementText(), element, "",
                                                          false, is_native);
    auto template_dec = element->GetTemplateDec();
    if (template_dec != nullptr)
    {
        std::vector<ABnfGuessPtr> guess_list_temp;
        auto error = template_dec->GuessTypes(guess_list_temp);
        if (error) return error;

        info->template_list.resize(0);
        for (auto& guess : guess_list_temp) info->template_list.push_back(guess);
    }
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}
