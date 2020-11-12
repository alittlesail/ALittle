#include "ALittleScriptElseIfExprReference.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ABnfGuessError ALittleScriptElseIfExprReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    if (element->GetAllExpr() == nullptr && element->GetElseIfBody() == nullptr)
        return ABnfGuessError(element, u8"if没有表达式列表");
    return nullptr;
}
