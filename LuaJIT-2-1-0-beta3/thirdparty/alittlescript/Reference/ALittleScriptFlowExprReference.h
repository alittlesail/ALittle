#ifndef _ALITTLE_ALITTLESCRIPTFLOWEXPRREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTFLOWEXPRREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptFlowExprElement.h"

class ALittleScriptFlowExprReference : public ALittleScriptReferenceTemplate<ALittleScriptFlowExprElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTFLOWEXPRREFERENCE_H_