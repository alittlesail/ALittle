
#ifndef _ALITTLE_ALITTLESCRIPTLANGUAGENAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTLANGUAGENAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptLanguageNameDecElement.h"

class ALittleScriptLanguageNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptLanguageNameDecElement>
{
public:
    ALittleScriptLanguageNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptLanguageNameDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptLanguageNameDecReference(element); }
    ABnfGuessError CheckError() override;

    bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;

    int QueryClassificationTag(bool& blur) override;
};

#endif // _ALITTLE_ALITTLESCRIPTLANGUAGENAMEDECREFERENCE_H_