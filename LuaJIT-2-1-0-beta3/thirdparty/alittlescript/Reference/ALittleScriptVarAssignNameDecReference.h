#ifndef _ALITTLE_ALITTLESCRIPTVARASSIGNNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTVARASSIGNNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptVarAssignNameDecElement.h"

class ALittleScriptMethodBodyDecElement;

class ALittleScriptVarAssignNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptVarAssignNameDecElement>
{
private:
    std::string m_key;
    std::weak_ptr<ABnfElement> m_method_dec;
    std::weak_ptr<ALittleScriptMethodBodyDecElement> m_method_body_dec;

public:
    ALittleScriptVarAssignNameDecReference(ABnfElementPtr element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptVarAssignNameDecReference(element); }

private:
    void ReloadInfo();

    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;

    bool PeekHighlightWord() override;

    void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) override;

private:
    void CollectHighlight(ABnfGuessPtr target_guess, ABnfElementPtr element, std::vector<ALanguageHighlightWordInfo>& list);
};

#endif // _ALITTLE_ALITTLESCRIPTVARASSIGNNAMEDECREFERENCE_H_