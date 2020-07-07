
#ifndef _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassStaticDecElement.h"

class ALittleScriptClassStaticDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassStaticDecElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_