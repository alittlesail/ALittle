#ifndef _ALITTLE_ALITTLESCRIPTUSINGNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTUSINGNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptUsingNameDecElement.h"

class ALittleScriptUsingNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptUsingNameDecElement>
{
    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTUSINGNAMEDECREFERENCE_H_