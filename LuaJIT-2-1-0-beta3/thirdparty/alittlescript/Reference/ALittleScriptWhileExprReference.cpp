#include "ALittleScriptWhileExprReference.h"

#include "../Generate/ALittleScriptValueStatElement.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ABnfGuessError ALittleScriptWhileExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");

    if (element->GetAllExpr() == nullptr && element->GetWhileBody() == nullptr)
        return ABnfGuessError(element, u8"while没有循环体");

    return nullptr;
}
