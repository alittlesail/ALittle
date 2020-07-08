
#ifndef _ALITTLE_ALITTLESCRIPTASSERTEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTASSERTEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptAssertExprElement.h"

class ALittleScriptAssertExprReference : public ALittleScriptReferenceTemplate<ALittleScriptAssertExprElement>
{
public:
    ALittleScriptAssertExprReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptAssertExprElement>(element) {}
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTASSERTEXPRREFERENCE_H_