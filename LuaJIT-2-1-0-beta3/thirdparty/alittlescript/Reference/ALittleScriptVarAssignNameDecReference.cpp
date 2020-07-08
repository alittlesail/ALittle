#include "ALittleScriptVarAssignNameDecReference.h"

#include "../Generate/ALittleScriptNamespaceDecElement.h"
#include "../Generate/ALittleScriptClassDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptClassSetterDecElement.h"
#include "../Generate/ALittleScriptClassGetterDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptVarAssignDecElement.h"
#include "../Generate/ALittleScriptForPairDecElement.h"
#include "../Generate/ALittleScriptPropertyValueCustomTypeElement.h"
#include "../Generate/ALittleScriptMethodBodyDecElement.h"
#include "../Generate/ALittleScriptMethodParamNameDecElement.h"

#include "../Guess/ALittleScriptGuessFunctor.h"
#include "../Guess/ALittleScriptGuessNamespaceName.h"
#include "../Guess/ALittleScriptGuessClassName.h"
#include "../Guess/ALittleScriptGuessStructName.h"
#include "../Guess/ALittleScriptGuessEnumName.h"

#include "../Index/ALittleScriptUtility.h"

ALittleScriptVarAssignNameDecReference::ALittleScriptVarAssignNameDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptVarAssignNameDecElement>(element)
{
    m_key = element->GetElementText();
}

void ALittleScriptVarAssignNameDecReference::ReloadInfo()
{
    m_method_dec = std::shared_ptr<ALittleScriptMethodBodyDecElement>();
    ABnfElementPtr parent = m_element.lock();
    while (parent != nullptr)
    {
        if (std::dynamic_pointer_cast<ALittleScriptNamespaceDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassDecElement>(parent))
        {
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent)->GetMethodBodyDec();
            break;

        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent)->GetMethodBodyDec();
            break;
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent))
        {
            m_method_dec = parent;
            m_method_body_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)->GetMethodBodyDec();
            break;
        }

        parent = parent->GetParent();
    }
}

int ALittleScriptVarAssignNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    auto element = m_element.lock();
    if (element == nullptr) return 0;

    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return 0;
    if (std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess))
    {
        auto guess_functor = std::dynamic_pointer_cast<ALittleScriptGuessFunctor>(guess);
        auto guess_functor_element = guess_functor->GetElement();
        if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassGetterDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptClassSetterDecElement>(guess_functor_element)
            || std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(guess_functor_element))
            return ALittleScriptColorType::METHOD_NAME;
    }
    else if (std::dynamic_pointer_cast<ALittleScriptGuessNamespaceName>(guess)
        || std::dynamic_pointer_cast<ALittleScriptGuessClassName>(guess)
        || std::dynamic_pointer_cast<ALittleScriptGuessStructName>(guess)
        || std::dynamic_pointer_cast<ALittleScriptGuessEnumName>(guess))
    {
        return ALittleScriptColorType::CUSTOM_NAME;
    }

    return ALittleScriptColorType::VAR_NAME;
}

ABnfGuessError ALittleScriptVarAssignNameDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto parent = element->GetParent();
    if (std::dynamic_pointer_cast<ALittleScriptVarAssignDecElement>(parent)) {
        return parent->GuessTypes(guess_list);
    }
    else if (std::dynamic_pointer_cast<ALittleScriptForPairDecElement>(parent)) {
        return parent->GuessTypes(guess_list);
    }
    guess_list.resize(0);
    return nullptr;
}

ABnfGuessError ALittleScriptVarAssignNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    if (element->GetElementText().find("___") == 0)
        return ABnfGuessError(element, u8"变量名不能以3个下划线开头");

    std::vector<ABnfGuessPtr> guess_list;
    auto error = element->GuessTypes(guess_list);
    if (error) return error;
    if (guess_list.size() == 0)
        return ABnfGuessError(element, u8"未知类型");
    else if (guess_list.size() != 1)
        return ABnfGuessError(element, u8"重复定义");

    if (m_method_dec.lock() == nullptr)
        ReloadInfo();

    // 处理参数
    auto method_dec = m_method_dec.lock();
    if (method_dec != nullptr)
    {
        std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>> dec_list;
        ALittleScriptUtility::FindMethodParamNameDecList(method_dec, m_key, dec_list);
        if (dec_list.size() > 0)
            return ABnfGuessError(element, u8"重复定义");
    }
    // 处理表达式定义
    {
        std::vector<std::shared_ptr<ALittleScriptVarAssignNameDecElement>> dec_list;
        ALittleScriptUtility::FindVarAssignNameDecList(element, m_key, dec_list);
        if (dec_list.size() > 0)
            return ABnfGuessError(element, u8"重复定义");
    }

    return nullptr;
}

bool ALittleScriptVarAssignNameDecReference::PeekHighlightWord()
{
    return true;
}

void ALittleScriptVarAssignNameDecReference::QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    if (m_method_dec.lock() == nullptr)
        ReloadInfo();

    ABnfGuessPtr guess;
    auto error = element->GuessType(guess);
    if (error) return;

    CollectHighlight(guess, m_method_body_dec.lock(), list);

    // 处理参数
    auto method_dec = m_method_dec.lock();
    if (method_dec != nullptr)
    {
        std::vector<std::shared_ptr<ALittleScriptMethodParamNameDecElement>> dec_list;
        ALittleScriptUtility::FindMethodParamNameDecList(method_dec, m_key, dec_list);
        for (auto& dec : dec_list)
        {
            ALanguageHighlightWordInfo info;
            info.line_start = dec->GetStartLine();
            info.char_start = dec->GetStartCol();
            info.line_end = dec->GetEndLine();
            info.char_end = dec->GetEndCol();
            list.push_back(info);
        }
    }
}

void ALittleScriptVarAssignNameDecReference::CollectHighlight(ABnfGuessPtr target_guess, ABnfElementPtr element, std::vector<ALanguageHighlightWordInfo>& list)
{
    if (std::dynamic_pointer_cast<ALittleScriptPropertyValueCustomTypeElement>(element)
        || std::dynamic_pointer_cast<ALittleScriptVarAssignNameDecElement>(element))
    {
        if (element->GetElementText() != m_key) return;

        ABnfGuessPtr guess;
        auto error = element->GuessType(guess);
        if (error) return;
        if (guess->GetValue() == target_guess->GetValue())
        {
            ALanguageHighlightWordInfo info;
            info.line_start = element->GetStartLine();
            info.char_start = element->GetStartCol();
            info.line_end = element->GetEndLine();
            info.char_end = element->GetEndCol();
            list.push_back(info);
        }
        return;
    }

    auto node = std::dynamic_pointer_cast<ABnfNodeElement>(element);
    if (node)
    {
        const auto& childs = node->GetChilds();
        for (auto& child : childs)
            CollectHighlight(target_guess, child, list);
    }
}
