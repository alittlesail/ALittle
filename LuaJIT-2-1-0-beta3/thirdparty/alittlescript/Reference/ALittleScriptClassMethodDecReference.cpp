#include "ALittleScriptClassMethodDecReference.h"

#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptMethodReturnDecElement.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptClassMethodDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    if (element->GetMethodNameDec() == nullptr)
        return ABnfGuessError(element, u8"没有函数名");

    if (element->GetMethodBodyDec() == nullptr)
        return ABnfGuessError(element, u8"没有函数体");

    auto parent = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(element->GetParent());
    if (parent == nullptr)
        return ABnfGuessError(element, u8"ALittleScriptClassMethodDecElement的父节点不是ALittleScriptClassElementDecElement");

    auto co_text = ALittleScriptUtility::GetCoroutineType(parent->GetModifierList());

    int return_count = 0;
    auto return_dec = element->GetMethodReturnDec();
    if (return_dec != nullptr) return_count = return_dec->GetMethodReturnOneDecList().size();

    if (co_text == "async" && return_count > 0)
        return ABnfGuessError(return_dec, u8"带async修饰的函数，不能有返回值");
    return nullptr;
}
