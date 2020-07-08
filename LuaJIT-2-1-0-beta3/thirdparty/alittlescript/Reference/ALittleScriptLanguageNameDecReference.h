
#ifndef _ALITTLE_ALITTLESCRIPTLANGUAGENAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTLANGUAGENAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptLanguageNameDecElement.h"

class ALittleScriptLanguageNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptLanguageNameDecElement>
{
public:
    ALittleScriptLanguageNameDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptLanguageNameDecElement>(element) {}
    ABnfGuessError CheckError() override;

    bool QueryCompletion(std::vector<ALanguageCompletionInfo>& list) override;

    int QueryClassificationTag(bool& blur) override;
};

#endif // _ALITTLE_ALITTLESCRIPTLANGUAGENAMEDECREFERENCE_H_