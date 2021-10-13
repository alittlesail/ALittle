#include "ALittleScriptPathsValueReference.h"

#include "../Generate/ALittleScriptTextElement.h"

#include "../Guess/ALittleScriptGuessList.h"
#include "../Index/ALittleScriptIndex.h"
#include "../Index/ALittleScriptUtility.h"
#include "../Index/ALittleScriptFileClass.h"

ABnfGuessError ALittleScriptPathsValueReference::GuessTypes(std::vector<ABnfGuessPtr>& guess_list)
{
    const auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");

    element->GetFile()->AddGuessType(ALittleScriptStatic::Inst().sStringListListGuess);
    guess_list.push_back(ALittleScriptStatic::Inst().sStringListListGuess);
    return nullptr;
}

ABnfGuessError ALittleScriptPathsValueReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(nullptr, u8"节点失效");
    auto text = element->GetText();
    if (text == nullptr) return ABnfGuessError(element, u8"请填写路径来获取子文件夹以及文件的路径");

    // 检查路径是否存在
    auto path = element->GetModulePath() + text->GetElementString();
    ALittleScriptUtility::TrimLeft(path);
    ALittleScriptUtility::TrimRight(path);
    if (!ALittleScriptUtility::IsDirExist(path))
        return ABnfGuessError(element, u8"填写的路径不存在:" + path);
    return nullptr;
}
