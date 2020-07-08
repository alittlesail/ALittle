#ifndef _ALITTLE_ALITTLESCRIPTVALUEFACTORSTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTVALUEFACTORSTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptValueFactorStatElement.h"

class ALittleScriptValueFactorStatReference : public ALittleScriptReferenceTemplate<ALittleScriptValueFactorStatElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTVALUEFACTORSTATREFERENCE_H_