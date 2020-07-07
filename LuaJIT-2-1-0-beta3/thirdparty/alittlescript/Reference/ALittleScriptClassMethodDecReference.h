
#ifndef _ALITTLE_ALITTLESCRIPTCLASSMETHODDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSMETHODDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassMethodDecElement.h"

class ALittleScriptClassMethodDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassMethodDecElement>
{
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSMETHODDECREFERENCE_H_

