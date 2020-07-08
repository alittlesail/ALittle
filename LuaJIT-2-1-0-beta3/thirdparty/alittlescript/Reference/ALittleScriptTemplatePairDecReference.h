#ifndef _ALITTLE_ALITTLESCRIPTTEMPLATEPAIRDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTTEMPLATEPAIRDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptTemplatePairDecElement.h"

class ALittleScriptTemplatePairDecReference : public ALittleScriptReferenceTemplate<ALittleScriptTemplatePairDecElement>
{
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTTEMPLATEPAIRDECREFERENCE_H_