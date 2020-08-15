#include "ALittleScriptMethodParamTailDecReference.h"

#include "../Generate/ALittleScriptMethodParamDecElement.h"
#include "../Generate/ALittleScriptClassMethodDecElement.h"
#include "../Generate/ALittleScriptClassStaticDecElement.h"
#include "../Generate/ALittleScriptClassCtorDecElement.h"
#include "../Generate/ALittleScriptGlobalMethodDecElement.h"
#include "../Generate/ALittleScriptMethodParamOneDecElement.h"

#include "../Guess/ALittleScriptGuessParamTail.h"
#include "../Index/ALittleScriptFileClass.h"

ABnfGuessError ALittleScriptMethodParamTailDecReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto info = ABnfGuessPtr(new ALittleScriptGuessParamTail(element->GetElementText()));
    info->UpdateValue();
    element->GetFile()->AddGuessType(info);
    guess_list.push_back(info);
    return nullptr;
}

ABnfGuessError ALittleScriptMethodParamTailDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    auto parent = element->GetParent();
    if (std::dynamic_pointer_cast<ALittleScriptMethodParamDecElement>(parent)) return nullptr;

    while (parent != nullptr)
    {
        std::shared_ptr<ALittleScriptMethodParamDecElement> param_dec;
        if (std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent)) {
            param_dec = std::dynamic_pointer_cast<ALittleScriptClassMethodDecElement>(parent)->GetMethodParamDec();
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent)) {
            param_dec = std::dynamic_pointer_cast<ALittleScriptClassStaticDecElement>(parent)->GetMethodParamDec();
        }
        else if (std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent)) {
            param_dec = std::dynamic_pointer_cast<ALittleScriptClassCtorDecElement>(parent)->GetMethodParamDec();
        }
        else if (std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)) {
            param_dec = std::dynamic_pointer_cast<ALittleScriptGlobalMethodDecElement>(parent)->GetMethodParamDec();
        }

        if (param_dec != nullptr)
        {
            const auto& param_one_list = param_dec->GetMethodParamOneDecList();
            if (param_one_list.size() == 0)
                return ABnfGuessError(element, u8"参数占位符未定义");
            auto param_tail = param_one_list[param_one_list.size() - 1]->GetMethodParamTailDec();
            if (param_tail == nullptr)
                return ABnfGuessError(element, u8"参数占位符未定义");
            break;
        }

        parent = parent->GetParent();
    }
    return nullptr;
}
