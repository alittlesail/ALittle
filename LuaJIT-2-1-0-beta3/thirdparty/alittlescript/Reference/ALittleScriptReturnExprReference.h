
#ifndef _ALITTLE_ALITTLESCRIPTRETURNEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTRETURNEXPRREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptReturnExprElement.h"

class ALittleScriptReturnExprReference : public ALittleScriptReferenceTemplate<ALittleScriptReturnExprElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTRETURNEXPRREFERENCE_H_