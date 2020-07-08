
#ifndef _ALITTLE_ALITTLESCRIPTCLASSMETHODDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSMETHODDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassMethodDecElement.h"

class ALittleScriptClassMethodDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassMethodDecElement>
{
public:
    ALittleScriptClassMethodDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptClassMethodDecElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptClassMethodDecReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSMETHODDECREFERENCE_H_

