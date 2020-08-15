
#ifndef _ALITTLE_ALITTLESCRIPTPRIMITIVETYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPRIMITIVETYPEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPrimitiveTypeElement.h"

class ALittleScriptPrimitiveTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptPrimitiveTypeElement>
{
public:
    ALittleScriptPrimitiveTypeReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptPrimitiveTypeElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptPrimitiveTypeReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTPRIMITIVETYPEREFERENCE_H_