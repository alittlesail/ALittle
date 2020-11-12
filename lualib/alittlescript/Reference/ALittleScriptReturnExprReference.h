
#ifndef _ALITTLE_ALITTLESCRIPTRETURNEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTRETURNEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptReturnExprElement.h"

class ALittleScriptReturnExprReference : public ALittleScriptReferenceTemplate<ALittleScriptReturnExprElement>
{
public:
    ALittleScriptReturnExprReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptReturnExprElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptReturnExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTRETURNEXPRREFERENCE_H_