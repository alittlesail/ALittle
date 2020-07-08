#ifndef _ALITTLE_ALITTLESCRIPTVALUESTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTVALUESTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptValueStatElement.h"

class ALittleScriptValueStatReference : public ALittleScriptReferenceTemplate<ALittleScriptValueStatElement>
{
public:
    ALittleScriptValueStatReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptValueStatElement>(element) {}
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTVALUESTATREFERENCE_H_