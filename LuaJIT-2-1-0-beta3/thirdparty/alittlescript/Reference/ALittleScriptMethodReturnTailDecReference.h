
#ifndef _ALITTLE_ALITTLESCRIPTMETHODRETURNTAILDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODRETURNTAILDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodReturnTailDecElement.h"

class ALittleScriptMethodReturnTailDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodReturnTailDecElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODRETURNTAILDECREFERENCE_H_