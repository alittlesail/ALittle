#ifndef _ALITTLE_ALITTLESCRIPTIFEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTIFEXPRREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptIfExprElement.h"

class ALittleScriptIfExprReference : public ALittleScriptReferenceTemplate<ALittleScriptIfExprElement>
{
public:
    ALittleScriptIfExprReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptIfExprElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptIfExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTIFEXPRREFERENCE_H_