#ifndef _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptWrapValueStatElement.h"

class ALittleScriptWrapValueStatReference : public ALittleScriptReferenceTemplate<ALittleScriptWrapValueStatElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTWRAPVALUESTATREFERENCE_H_