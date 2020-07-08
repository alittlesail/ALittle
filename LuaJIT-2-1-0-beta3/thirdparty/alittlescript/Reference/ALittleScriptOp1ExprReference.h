
#ifndef _ALITTLE_ALITTLESCRIPTOP1EXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTOP1EXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptOp1ExprElement.h"

class ALittleScriptOp1ExprReference : public ALittleScriptReferenceTemplate<ALittleScriptOp1ExprElement>
{
public:
    ALittleScriptOp1ExprReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptOp1ExprElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptOp1ExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTOP1EXPRREFERENCE_H_