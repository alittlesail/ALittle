#ifndef _ALITTLE_ALITTLESCRIPTVARASSIGNEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTVARASSIGNEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptVarAssignExprElement.h"

class ALittleScriptVarAssignExprReference : public ALittleScriptReferenceTemplate<ALittleScriptVarAssignExprElement>
{
public:
    ALittleScriptVarAssignExprReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptVarAssignExprElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptVarAssignExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTVARASSIGNEXPRREFERENCE_H_