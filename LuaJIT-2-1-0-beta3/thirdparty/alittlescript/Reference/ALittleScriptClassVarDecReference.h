
#ifndef _ALITTLE_ALITTLESCRIPTCLASSVARDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSVARDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassVarDecElement.h"

class ALittleScriptClassVarDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassVarDecElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSVARDECREFERENCE_H_