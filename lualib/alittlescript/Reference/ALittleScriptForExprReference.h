#ifndef _ALITTLE_ALITTLESCRIPTFOREXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTFOREXPRREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptForExprElement.h"

class ALittleScriptForExprReference : public ALittleScriptReferenceTemplate<ALittleScriptForExprElement>
{
public:
    ALittleScriptForExprReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptForExprElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptForExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTFOREXPRREFERENCE_H_