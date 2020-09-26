#ifndef _ALITTLE_ALITTLESCRIPTTHROWEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTTHROWEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptThrowExprElement.h"

class ALittleScriptThrowExprReference : public ALittleScriptReferenceTemplate<ALittleScriptThrowExprElement>
{
public:
    ALittleScriptThrowExprReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptThrowExprElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptThrowExprReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTTHROWEXPRREFERENCE_H_