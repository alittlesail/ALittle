#include "ALittleScriptKeyReference.h"

#include "../Index/ALittleScriptIndex.h"

int ALittleScriptKeyReference::QueryClassificationTag(bool& blur)
{
    auto element = m_element.lock();
    if (element == nullptr) return 0;

    blur = false;
    auto text = element->GetElementText();

    if (ALittleScriptStatic::Inst().sCtrlKeyWord.find(text) != ALittleScriptStatic::Inst().sCtrlKeyWord.end())
        return ALittleScriptColorType::CTRL_KEYWORD;
    return ALittleScriptColorType::KEYWORD;
}

ABnfElementPtr ALittleScriptKeyReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    auto parent = element->GetParent();
    if (parent == nullptr) return nullptr;
    return parent->GetReference()->GotoDefinition();
}

bool ALittleScriptKeyReference::CanGotoDefinition()
{
    return false;
}
