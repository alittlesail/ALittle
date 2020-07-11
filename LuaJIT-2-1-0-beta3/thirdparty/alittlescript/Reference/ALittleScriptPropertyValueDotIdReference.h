
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueDotIdElement.h"

class ALittleScriptPropertyValueDotIdReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueDotIdElement>
{
public:
    ALittleScriptPropertyValueDotIdReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueDotIdElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptPropertyValueDotIdReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_