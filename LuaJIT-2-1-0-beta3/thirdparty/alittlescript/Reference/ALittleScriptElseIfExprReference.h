#ifndef _ALITTLE_ALITTLESCRIPTELSEIFEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTELSEIFEXPRREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptElseIfExprElement.h"

class ALittleScriptElseIfExprReference : public ALittleScriptReferenceTemplate<ALittleScriptElseIfExprElement>
{
public:
    ALittleScriptElseIfExprReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptElseIfExprElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptElseIfExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTELSEIFEXPRREFERENCE_H_