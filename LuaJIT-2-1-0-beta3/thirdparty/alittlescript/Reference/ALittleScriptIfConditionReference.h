#ifndef _ALITTLE_ALITTLESCRIPTIFCONDITIONREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTIFCONDITIONREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptIfConditionElement.h"

class ALittleScriptIfConditionReference : public ALittleScriptReferenceTemplate<ALittleScriptIfConditionElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTIFCONDITIONREFERENCE_H_