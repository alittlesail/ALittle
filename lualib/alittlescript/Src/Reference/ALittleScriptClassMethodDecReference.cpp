#include "ALittleScriptClassMethodDecReference.h"

#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptMethodReturnDecElement.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptClassMethodDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetMethodNameDec() == nullptr)
        return ABnfGuessError(element, u8"û�к�����");

    if (element->GetMethodBodyDec() == nullptr)
        return ABnfGuessError(element, u8"û�к�����");

    auto parent = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(element->GetParent());
    if (parent == nullptr)
        return ABnfGuessError(element, u8"ALittleScriptClassMethodDecElement�ĸ��ڵ㲻��ALittleScriptClassElementDecElement");

    const auto co_text = ALittleScriptUtility::GetCoroutineType(parent->GetModifierList());

    int return_count = 0;
    auto return_dec = element->GetMethodReturnDec();
    if (return_dec != nullptr) return_count = static_cast<int>(return_dec->GetMethodReturnOneDecList().size());

    if (co_text == "async" && return_count > 0)
        return ABnfGuessError(return_dec, u8"��async���εĺ����������з���ֵ");
    return nullptr;
}
