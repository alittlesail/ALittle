#ifndef _ALITTLE_ALITTLESCRIPTSTRUCTVARDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTSTRUCTVARDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptStructVarDecElement.h"

class ALittleScriptStructVarDecReference : public ALittleScriptReferenceTemplate<ALittleScriptStructVarDecElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTSTRUCTVARDECREFERENCE_H_