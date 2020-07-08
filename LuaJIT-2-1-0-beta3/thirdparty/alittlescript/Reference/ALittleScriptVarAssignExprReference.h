#ifndef _ALITTLE_ALITTLESCRIPTVARASSIGNEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTVARASSIGNEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptVarAssignExprElement.h"

class ALittleScriptVarAssignExprReference : public ALittleScriptReferenceTemplate<ALittleScriptVarAssignExprElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTVARASSIGNEXPRREFERENCE_H_