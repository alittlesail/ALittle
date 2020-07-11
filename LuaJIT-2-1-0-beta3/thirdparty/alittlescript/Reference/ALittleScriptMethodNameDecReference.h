
#ifndef _ALITTLE_ALITTLESCRIPTMETHODNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodNameDecElement.h"

class ALittleScriptMethodNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodNameDecElement>
{
private:
    std::string m_namespace_name;
    std::string m_key;

public:
    ALittleScriptMethodNameDecReference(ABnfElementPtr element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptMethodNameDecReference(element); }

    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;

    bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) override;

    ABnfElementPtr GotoDefinition() override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODNAMEDECREFERENCE_H_