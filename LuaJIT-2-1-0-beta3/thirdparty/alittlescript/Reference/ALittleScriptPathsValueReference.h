
#ifndef _ALITTLE_ALITTLESCRIPTPATHSVALUEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPATHSVALUEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPathsValueElement.h"

class ALittleScriptPathsValueReference : public ALittleScriptReferenceTemplate<ALittleScriptPathsValueElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTPATHSVALUEREFERENCE_H_