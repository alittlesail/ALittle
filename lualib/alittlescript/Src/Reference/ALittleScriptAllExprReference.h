﻿
#ifndef _ALITTLE_ALITTLESCRIPTALLEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTALLEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptAllExprElement.h"

class ALittleScriptAllExprReference : public ALittleScriptReferenceTemplate<ALittleScriptAllExprElement>
{
public:
    ALittleScriptAllExprReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptAllExprElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptAllExprReference(element); }
    ABnfGuessError CheckError() override;

    int QueryClassificationTag(bool& blur) override;
};

#endif // _ALITTLE_ALITTLESCRIPTALLEXPRREFERENCE_H_