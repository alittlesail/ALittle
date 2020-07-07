#ifndef _ALITTLE_ALITTLESCRIPTGENERICTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTGENERICTYPEREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptGenericTypeElement.h"

class ALittleScriptGenericTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptGenericTypeElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTGENERICTYPEREFERENCE_H_