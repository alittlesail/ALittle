#include "ALittleScriptWhileExprReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ABnfGuessError ALittleScriptWhileExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");

    if (element->GetAllExpr() == nullptr && element->GetWhileBody() == nullptr)
        return ABnfGuessError(element, u8"whileû��ѭ����");

    return nullptr;
}
