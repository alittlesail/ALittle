#ifndef _ALITTLE_ALITTLESCRIPTVALUESTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTVALUESTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptValueStatElement.h"

class ALittleScriptValueStatReference : public ALittleScriptReferenceTemplate<ALittleScriptValueStatElement>
{
public:
    ALittleScriptValueStatReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptValueStatElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptValueStatReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTVALUESTATREFERENCE_H_