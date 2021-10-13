#include "ALittleScriptElseIfExprReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ABnfGuessError ALittleScriptElseIfExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    if (element->GetAllExpr() == nullptr && element->GetElseIfBody() == nullptr)
        return ABnfGuessError(element, u8"ifû�б��ʽ�б�");
    return nullptr;
}
