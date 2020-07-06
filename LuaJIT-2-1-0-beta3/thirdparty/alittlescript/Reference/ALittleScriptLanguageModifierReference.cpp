
#include "ALittleScriptLanguageModifierReference.h"

#include "../Generate/ALittleScriptLanguageBodyDecElement.h"
#include "../Generate/ALittleScriptLanguageNameDecElement.h"

#include "../../alanguage/Index/ABnfFile.h"
#include "../../alanguage/Index/ABnfProject.h"

#include "../Index/ALittleScriptProjectClass.h"

ABnfGuessError ALittleScriptLanguageModifierReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    auto body_dec = element->GetLanguageBodyDec();
    if (body_dec == nullptr)
        return ABnfGuessError(element, u8"请定义你限定的语言范围");

    if (body_dec->GetLanguageNameDecList().size() == 0)
        return ABnfGuessError(element, u8"请定义你限定的语言范围");

    return nullptr;
}

bool ALittleScriptLanguageModifierReference::IsLanguageEnable()
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    if (!m_init)
    {
        m_init = true;

        auto body_dec = element->GetLanguageBodyDec();
        if (body_dec == nullptr) return false;

        const auto& name_list = body_dec->GetLanguageNameDecList();
        for (auto& name : name_list)
            m_name_set.insert(name->GetElementText());
    }

    auto* project = dynamic_cast<ALittleScriptProjectClass*>(element->GetFile()->GetProject());

    return m_name_set.find(project->GetTargetLanguage()) != m_name_set.end();
}
