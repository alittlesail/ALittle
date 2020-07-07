#ifndef _ALITTLE_ALITTLESCRIPTFORPAIRDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTFORPAIRDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptForPairDecElement.h"

class ALittleScriptForPairDecReference : public ALittleScriptReferenceTemplate<ALittleScriptForPairDecElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTFORPAIRDECREFERENCE_H_