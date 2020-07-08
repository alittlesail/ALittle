#ifndef _ALITTLE_ALITTLESCRIPTFORPAIRDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTFORPAIRDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptForPairDecElement.h"

class ALittleScriptForPairDecReference : public ALittleScriptReferenceTemplate<ALittleScriptForPairDecElement>
{
public:
    ALittleScriptForPairDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptForPairDecElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptForPairDecReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTFORPAIRDECREFERENCE_H_