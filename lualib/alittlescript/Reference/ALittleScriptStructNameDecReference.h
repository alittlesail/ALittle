
#ifndef _ALITTLE_ALITTLESCRIPTSTRUCTNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTSTRUCTNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptStructNameDecElement.h"

class ALittleScriptStructNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptStructNameDecElement>
{
private:
    std::string m_namespace_name;
    std::string m_key;

public:
    ALittleScriptStructNameDecReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptStructNameDecReference(element); }

    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfElementPtr GotoDefinition() override;

    bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTSTRUCTNAMEDECREFERENCE_H_