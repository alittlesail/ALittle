
#ifndef _ALITTLE_ALITTLESCRIPTMETHODRETURNTAILDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODRETURNTAILDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodReturnTailDecElement.h"

class ALittleScriptMethodReturnTailDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodReturnTailDecElement>
{
public:
    ALittleScriptMethodReturnTailDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptMethodReturnTailDecElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptMethodReturnTailDecReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODRETURNTAILDECREFERENCE_H_