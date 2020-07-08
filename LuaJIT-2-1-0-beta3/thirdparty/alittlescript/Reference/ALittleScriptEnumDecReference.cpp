#include "ALittleScriptEnumDecReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Guess/ALittleScriptGuessEnum.h"
#include "../Generate/ALittleScriptEnumNameDecElement.h"
#include "../Generate/ALittleScriptEnumBodyDecElement.h"
#include "../Generate/ALittleScriptEnumVarDecElement.h"
#include "../Generate/ALittleScriptEnumVarNameDecElement.h"

ALittleScriptEnumDecReference::ALittleScriptEnumDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptEnumDecElement>(element)
{
    m_namespace_name = ALittleScriptUtility::GetNamespaceName(element);
}

inline ABnfGuessError ALittleScriptEnumDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    guess_list.resize(0);
    auto name_dec = element->GetEnumNameDec();
    if (name_dec == nullptr)
        return ABnfGuessError(element, u8"没有定义枚举名");

    auto info = std::shared_ptr< ALittleScriptGuessEnum>(new ALittleScriptGuessEnum(m_namespace_name, name_dec->GetElementText(), element));
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}

ABnfGuessError ALittleScriptEnumDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto enum_name_dec = element->GetEnumNameDec();
    if (enum_name_dec == nullptr)
        return ABnfGuessError(element, u8"没有定义枚举名");

    auto body_dec = element->GetEnumBodyDec();
    if (body_dec == nullptr)
        return ABnfGuessError(element, u8"没有定义枚举内容");

    const auto& var_dec_list = body_dec->GetEnumVarDecList();
    std::unordered_set<std::string> name_set;
    for (auto& var_dec : var_dec_list)
    {
        auto name_dec = var_dec->GetEnumVarNameDec();
        if (name_dec == nullptr) continue;

        auto name = name_dec->GetElementText();
        if (name_set.find(name) != name_set.end())
            return ABnfGuessError(name_dec, u8"枚举字段名重复");
        name_set.insert(name);
    }

    return nullptr;
}
