#include "ALittleScriptIdReference.h"

void ALittleScriptIdReference::QueryQuickInfo(std::string& info)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    auto parent = element->GetParent();
    if (parent == nullptr) return;
    parent->GetReference()->QueryQuickInfo(info);
}

inline ABnfElementPtr ALittleScriptIdReference::GotoDefinition()
{
    auto element = m_element.lock();
    if (element == nullptr) return nullptr;
    auto parent = element->GetParent();
    if (parent == nullptr) return nullptr;
    return parent->GetReference()->GotoDefinition();
}

bool ALittleScriptIdReference::QueryCompletion(std::vector<ALanguageCompletionInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    auto parent = element->GetParent();
    if (parent == nullptr) return false;
    return parent->GetReference()->QueryCompletion(list);
}

bool ALittleScriptIdReference::PeekHighlightWord()
{
    auto element = m_element.lock();
    if (element == nullptr) return false;

    auto parent = element->GetParent();
    if (parent == nullptr) return false;
    return parent->GetReference()->PeekHighlightWord();
}

void ALittleScriptIdReference::QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list)
{
    auto element = m_element.lock();
    if (element == nullptr) return;

    auto parent = element->GetParent();
    if (parent == nullptr) return;
    parent->GetReference()->QueryHighlightWordTag(list);
}
