
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueElement.h"

class ALittleScriptPropertyValueReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEREFERENCE_H_