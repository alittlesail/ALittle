
#ifndef _ALITTLE_ALITTLESCRIPTALLTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTALLTYPEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptAllTypeElement.h"

class ALittleScriptAllTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptAllTypeElement>
{
public:
    ALittleScriptAllTypeReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptAllTypeElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptAllTypeReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTALLTYPEREFERENCE_H_