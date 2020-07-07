#ifndef _ALITTLE_ALITTLESCRIPTENUMVARDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTENUMVARDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptEnumVarDecElement.h"

class ALittleScriptEnumVarDecReference : public ALittleScriptReferenceTemplate<ALittleScriptEnumVarDecElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTENUMVARDECREFERENCE_H_