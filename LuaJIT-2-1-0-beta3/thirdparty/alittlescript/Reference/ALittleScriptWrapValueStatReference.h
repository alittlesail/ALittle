#ifndef _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptWrapValueStatElement.h"

class ALittleScriptWrapValueStatReference : public ALittleScriptReferenceTemplate<ALittleScriptWrapValueStatElement>
{
public:
    ALittleScriptWrapValueStatReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptWrapValueStatElement>(element) {}
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_