#include "ALittleScriptEnumDecReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Guess/ALittleScriptGuessEnum.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptEnumBodyDecElement.h"
#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptEnumVarNameDecElement.h"

ALittleScriptEnumDecReference::ALittleScriptEnumDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptEnumDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
}

inline ABnfGuessError ALittleScriptEnumDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");
    guess_list.resize(0);
    auto name_dec = element->GetEnumNameDec();
    if (name_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж���ö����");

    auto info = std::make_shared<ALittleScriptGuessEnum>(m_namespace_name, name_dec->GetElementText(), element);
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}

ABnfGuessError ALittleScriptEnumDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    const auto enum_name_dec = element->GetEnumNameDec();
    if (enum_name_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж���ö����");

    auto body_dec = element->GetEnumBodyDec();
    if (body_dec == nullptr)
        return ABnfGuessError(element, u8"û�ж���ö������");

    const auto& var_dec_list = body_dec->GetEnumVarDecList();
    std::unordered_set<std::string> name_set;
    for (const auto& var_dec : var_dec_list)
    {
        auto name_dec = var_dec->GetEnumVarNameDec();
        if (name_dec == nullptr) continue;

        auto name = name_dec->GetElementText();
        if (name_set.find(name) != name_set.end())
            return ABnfGuessError(name_dec, u8"ö���ֶ����ظ�");
        name_set.insert(name);
    }

    return nullptr;
}
