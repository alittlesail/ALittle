
#ifndef _ALITTLE_ALITTLESCRIPTMETHODPARAMTAILDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODPARAMTAILDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodParamTailDecElement.h"

class ALittleScriptMethodParamTailDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodParamTailDecElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODPARAMTAILDECREFERENCE_H_