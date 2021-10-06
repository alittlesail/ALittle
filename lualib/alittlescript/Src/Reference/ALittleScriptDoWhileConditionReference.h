﻿
#ifndef _ALITTLE_ALITTLESCRIPTDOWHILECONDITIONREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTDOWHILECONDITIONREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptDoWhileConditionElement.h"

class ALittleScriptDoWhileConditionReference : public ALittleScriptReferenceTemplate<ALittleScriptDoWhileConditionElement>
{
public:
    ALittleScriptDoWhileConditionReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptDoWhileConditionElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptDoWhileConditionReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTDOWHILECONDITIONREFERENCE_H_