
#ifndef _ALITTLE_ALITTLESCRIPTOPNEWLISTSTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTOPNEWLISTSTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptOpNewListStatElement.h"

class ALittleScriptOpNewListStatReference : public ALittleScriptReferenceTemplate<ALittleScriptOpNewListStatElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTOPNEWLISTSTATREFERENCE_H_