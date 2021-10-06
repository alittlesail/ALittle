﻿
#ifndef _ALITTLE_ALITTLESCRIPTASSERTEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTASSERTEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptAssertExprElement.h"

class ALittleScriptAssertExprReference : public ALittleScriptReferenceTemplate<ALittleScriptAssertExprElement>
{
public:
    ALittleScriptAssertExprReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptAssertExprElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptAssertExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTASSERTEXPRREFERENCE_H_