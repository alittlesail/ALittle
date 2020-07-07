
#ifndef _ALITTLE_ALITTLESCRIPTOPASSIGNEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTOPASSIGNEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptOpAssignExprElement.h"

class ALittleScriptOpAssignExprReference : public ALittleScriptReferenceTemplate<ALittleScriptOpAssignExprElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTOPASSIGNEXPRREFERENCE_H_