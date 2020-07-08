
#ifndef _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassStaticDecElement.h"

class ALittleScriptClassStaticDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassStaticDecElement>
{
public:
    ALittleScriptClassStaticDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptClassStaticDecElement>(element) {}
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_