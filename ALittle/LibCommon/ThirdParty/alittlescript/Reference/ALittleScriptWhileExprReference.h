#ifndef _ALITTLE_ALITTLESCRIPTWHILEEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTWHILEEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptWhileExprElement.h"

class ALittleScriptWhileExprReference : public ALittleScriptReferenceTemplate<ALittleScriptWhileExprElement>
{
public:
    ALittleScriptWhileExprReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptWhileExprElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptWhileExprReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTWHILEEXPRREFERENCE_H_