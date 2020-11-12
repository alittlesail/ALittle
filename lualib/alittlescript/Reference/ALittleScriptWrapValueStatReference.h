#ifndef _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptWrapValueStatElement.h"

class ALittleScriptWrapValueStatReference : public ALittleScriptReferenceTemplate<ALittleScriptWrapValueStatElement>
{
public:
    ALittleScriptWrapValueStatReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptWrapValueStatElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptWrapValueStatReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_