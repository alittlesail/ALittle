
#ifndef _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassStaticDecElement.h"

class ALittleScriptClassStaticDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassStaticDecElement>
{
public:
    ALittleScriptClassStaticDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptClassStaticDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptClassStaticDecReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSSTATICDECREFERENCE_H_