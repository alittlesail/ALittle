
#ifndef _ALITTLE_ALITTLESCRIPTENUMNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTENUMNAMEDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptEnumNameDecElement.h"

class ALittleScriptEnumNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptEnumNameDecElement>
{
private:
    std::string m_namespace_name;
    std::string m_key;

public:
    ALittleScriptEnumNameDecReference(ABnfElementPtr element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptEnumNameDecReference(element); }

    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfElementPtr GotoDefinition() override;

    bool QueryCompletion(std::vector<ALanguageCompletionInfo>& list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTENUMNAMEDECREFERENCE_H_