
#ifndef _ALITTLE_ALITTLESCRIPTALLTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTALLTYPEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptAllTypeElement.h"

class ALittleScriptAllTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptAllTypeElement>
{
public:
    ALittleScriptAllTypeReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptAllTypeElement>(element) {}
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTALLTYPEREFERENCE_H_