
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueDotIdElement.h"

class ALittleScriptPropertyValueDotIdReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueDotIdElement>
{
public:
    ALittleScriptPropertyValueDotIdReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueDotIdElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptPropertyValueDotIdReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_