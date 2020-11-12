#include "ALittleScriptFlowExprReference.h"

#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptForExprElement.h"
#include "../Generate/ALittleScriptWhileExprElement.h"
#include "../Generate/ALittleScriptDoWhileExprElement.h"

ABnfGuessError ALittleScriptFlowExprReference::CheckError()
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    // 获取对应的函数对象
    ABnfElementPtr parent = element;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            break;
        }

        if (std::dynamic_pointer_cast<ALittleScriptForExprElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptWhileExprElement>(parent)
            || std::dynamic_pointer_cast<ALittleScriptDoWhileExprElement>(parent))
        {
            return nullptr;
        }
        parent = parent->GetParent();
    }

    return ABnfGuessError(element, u8"break和continue只能在for,while,do while中");
}
