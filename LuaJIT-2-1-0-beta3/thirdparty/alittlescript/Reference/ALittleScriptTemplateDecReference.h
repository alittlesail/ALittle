#ifndef _ALITTLE_ALITTLESCRIPTTEMPLATEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTTEMPLATEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptTemplateDecElement.h"

class ALittleScriptTemplateDecReference : public ALittleScriptReferenceTemplate<ALittleScriptTemplateDecElement>
{
    bool MultiGuessTypes() override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTTEMPLATEDECREFERENCE_H_