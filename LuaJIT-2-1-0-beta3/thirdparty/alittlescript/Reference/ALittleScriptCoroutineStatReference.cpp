#include "ALittleScriptCoroutineStatReference.h"

#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptNamespaceElementDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"

#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"

ABnfGuessError ALittleScriptCoroutineStatReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    // 检查这次所在的函数必须要有await或者async修饰
    ABnfElementPtr parent = element;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
            if (ALittleScriptUtility::GetCoroutineType(modifier) == "await")
                return nullptr;
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
            if (ALittleScriptUtility::GetCoroutineType(modifier) == "await")
                return nullptr;
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            auto modifier = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent->GetParent())->GetModifierList();
            if (ALittleScriptUtility::GetCoroutineType(modifier) == "await")
                return nullptr;
            break;
        }
        parent = parent->GetParent();
    }

    return ABnfGuessError(element, u8"co关键字只能在await修饰的函数中使用");
}

ABnfGuessError ALittleScriptCoroutineStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    auto* index = GetIndex();
    return index->FindALittleStructGuessList("ALittle", u8"Thread", guess_list);
}
