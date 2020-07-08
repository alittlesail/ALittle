
#ifndef _ALITTLE_ALITTLESCRIPTCOROUTINESTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCOROUTINESTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptCoroutineStatElement.h"

class ALittleScriptCoroutineStatReference : public ALittleScriptReferenceTemplate<ALittleScriptCoroutineStatElement>
{
public:
    ALittleScriptCoroutineStatReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptCoroutineStatElement>(element) {}

    ABnfGuessError CheckError() override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTCOROUTINESTATREFERENCE_H_