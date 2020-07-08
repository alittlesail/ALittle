
#ifndef _ALITTLE_ALITTLESCRIPTCONSTVALUEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCONSTVALUEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptConstValueElement.h"

class ALittleScriptConstValueReference : public ALittleScriptReferenceTemplate<ALittleScriptConstValueElement>
{
public:
    ALittleScriptConstValueReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptConstValueElement>(element) {}
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTCONSTVALUEREFERENCE_H_