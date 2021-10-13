﻿#ifndef _ALITTLE_ALITTLESCRIPTENUMVARDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTENUMVARDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptEnumVarDecElement.h"

class ALittleScriptEnumVarDecReference : public ALittleScriptReferenceTemplate<ALittleScriptEnumVarDecElement>
{
public:
    ALittleScriptEnumVarDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptEnumVarDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptEnumVarDecReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTENUMVARDECREFERENCE_H_