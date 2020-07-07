#ifndef _ALITTLE_ALITTLESCRIPTFOREXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTFOREXPRREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptForExprElement.h"

class ALittleScriptForExprReference : public ALittleScriptReferenceTemplate<ALittleScriptForExprElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTFOREXPRREFERENCE_H_