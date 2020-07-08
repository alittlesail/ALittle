#include "ALittleScriptPropertyValueThisTypeReference.h"

#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptClassElementDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"

#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptFileClass.h"
#include "../Guess/ALittleScriptGuessPrimitive.h"

ALittleScriptPropertyValueThisTypeReference::ALittleScriptPropertyValueThisTypeReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueThisTypeElement>(element)
{
    ReloadInfo();
}

void ALittleScriptPropertyValueThisTypeReference::ReloadInfo()
{
    m_class_dec = std::shared_ptr<ALittleScriptClassDecElement>();
    m_class_ctor_dec = std::shared_ptr<ALittleScriptClassCtorDecElement>();
    m_class_setter_dec = std::shared_ptr<ALittleScriptClassSetterDecElement>();
    m_class_method_dec = std::shared_ptr<ALittleScriptClassMethodDecElement>();
    m_class_static_dec = std::shared_ptr<ALittleScriptClassStaticDecElement>();

    ABnfElementPtr parent = m_element.lock();
    while (true)
    {
        if (parent == nullptr) break;

        if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent)) {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent)) {
            m_class_dec = std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent);
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent)) {
            m_class_ctor_dec = std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent)) {
            auto class_getter_dec = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent);
            m_class_getter_dec = class_getter_dec;
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(class_getter_dec->GetParent())->GetModifierList();
            m_is_const = ALittleScriptUtility::IsConst(modifier);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent)) {
            auto class_setter_dec = std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent);
            m_class_setter_dec = class_setter_dec;
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(class_setter_dec->GetParent())->GetModifierList();
            m_is_const = ALittleScriptUtility::IsConst(modifier);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent)) {
            auto class_method_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent);
            m_class_method_dec = class_method_dec;
            const auto& modifier = std::dynamic_pointer_cast<ALittleScriptClassElementDecElement>(class_method_dec->GetParent())->GetModifierList();
            m_is_const = ALittleScriptUtility::IsConst(modifier);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent)) {
            m_class_static_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent);
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)) {
            m_global_method_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent);
        }

        parent = parent->GetParent();
    }
}

void ALittleScriptPropertyValueThisTypeReference::CalcResolve(std::vector<ABnfElementPtr>& result_list)
{
    result_list.resize(0);
    auto class_dec = m_class_dec.lock();
    auto global_method_dec = m_global_method_dec.lock();
    auto class_static_dec = m_class_static_dec.lock();
    if (class_dec != nullptr && global_method_dec == nullptr && class_static_dec == nullptr)
        result_list.push_back(class_dec);
}

ABnfGuessError ALittleScriptPropertyValueThisTypeReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    
    guess_list.resize(0);

    std::vector<ABnfElementPtr> result_list;
    CalcResolve(result_list);
    for (auto& result : result_list)
    {
        if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(result))
        {
            ABnfGuessPtr guess;
            auto error = result->GuessType(guess);
            if (error) return error;
            if (m_is_const && !guess->is_const)
            {
                if (std::dynamic_pointer_cast<ALittleScriptGuessPrimitive>(guess))
                {
                    auto it = ALittleScriptStatic::Inst().sPrimitiveGuessMap.find("const " + guess->GetValue());
                    if (it != ALittleScriptStatic::Inst().sPrimitiveGuessMap.end()) guess = it->second;
                    else return ABnfGuessError(element, u8"找不到const " + guess->GetValue());
                }
                else
                {
                    guess = guess->Clone();
                    guess->is_const = true;
                    guess->UpdateValue();
                    element->GetFile()->AddGuessType(guess);
                }
            }
            guess_list.push_back(guess);
        }
    }

    return nullptr;
}

ABnfGuessError ALittleScriptPropertyValueThisTypeReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"重复定义");
    return nullptr;
}
