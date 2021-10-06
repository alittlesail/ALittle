﻿#ifndef _ALITTLE_ALITTLESCRIPTFLOWEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTFLOWEXPRREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptFlowExprElement.h"

class ALittleScriptFlowExprReference : public ALittleScriptReferenceTemplate<ALittleScriptFlowExprElement>
{
public:
    ALittleScriptFlowExprReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptFlowExprElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptFlowExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTFLOWEXPRREFERENCE_H_