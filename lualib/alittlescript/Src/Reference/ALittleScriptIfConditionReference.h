﻿#ifndef _ALITTLE_ALITTLESCRIPTIFCONDITIONREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTIFCONDITIONREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptIfConditionElement.h"

class ALittleScriptIfConditionReference : public ALittleScriptReferenceTemplate<ALittleScriptIfConditionElement>
{
public:
    ALittleScriptIfConditionReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptIfConditionElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptIfConditionReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTIFCONDITIONREFERENCE_H_