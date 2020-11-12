
#ifndef _ALITTLE_ALITTLESCRIPTCLASSCTORDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSCTORDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassCtorDecElement.h"

class ALittleScriptClassCtorDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassCtorDecElement>
{
public:
    ALittleScriptClassCtorDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptClassCtorDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptClassCtorDecReference(element); }
    ABnfElementPtr GotoDefinition() override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSCTORDECREFERENCE_H_