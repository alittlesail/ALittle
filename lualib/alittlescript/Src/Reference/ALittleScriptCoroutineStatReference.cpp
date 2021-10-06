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
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"�ڵ�ʧЧ");
    // ���������ڵĺ�������Ҫ��await����async����
    ABnfElementPtr parent = element;
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
        {
            break;
        }
        
        if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent))
        {
            break;
        }
        
        if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
        {
            break;
        }
        
        if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
        {
            break;
        }
        
        if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
            if (ALittleScriptUtility::GetCoroutineType(modifier) == "await")
                return nullptr;
            break;
        }
        
        if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(parent->GetParent())->GetModifierList();
            if (ALittleScriptUtility::GetCoroutineType(modifier) == "await")
                return nullptr;
            break;
        }
        
        if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptNamespaceElementDecElement>(parent->GetParent())->GetModifierList();
            if (ALittleScriptUtility::GetCoroutineType(modifier) == "await")
                return nullptr;
            break;
        }
        parent = parent->GetParent();
    }

    return ABnfGuessError(element, u8"co�ؼ���ֻ����await���εĺ�����ʹ��");
}

ABnfGuessError ALittleScriptCoroutineStatReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"�ڵ�ʧЧ");

    auto* index = GetIndex();
    return index->FindALittleStructGuessList("ALittle", u8"Thread", guess_list);
}
