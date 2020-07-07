
#ifndef _ALITTLE_ALITTLESCRIPTELSEIFCONDITIONREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTELSEIFCONDITIONREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptElseIfConditionElement.h"

class ALittleScriptElseIfConditionReference : public ALittleScriptReferenceTemplate<ALittleScriptElseIfConditionElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTELSEIFCONDITIONREFERENCE_H_