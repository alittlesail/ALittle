
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueDotIdElement.h"

class ALittleScriptPropertyValueDotIdReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueDotIdElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    bool QueryCompletion(std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDREFERENCE_H_