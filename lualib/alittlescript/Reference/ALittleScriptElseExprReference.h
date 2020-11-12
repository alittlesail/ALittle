#ifndef _ALITTLE_ALITTLESCRIPTELSEEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTELSEEXPRREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptElseExprElement.h"

class ALittleScriptElseExprReference : public ALittleScriptReferenceTemplate<ALittleScriptElseExprElement>
{
public:
    ALittleScriptElseExprReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptElseExprElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptElseExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTELSEEXPRREFERENCE_H_