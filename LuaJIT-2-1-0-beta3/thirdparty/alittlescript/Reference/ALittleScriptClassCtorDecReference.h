
#ifndef _ALITTLE_ALITTLESCRIPTCLASSCTORDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSCTORDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassCtorDecElement.h"

class ALittleScriptClassCtorDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassCtorDecElement>
{
public:
    ABnfElementPtr GotoDefinition() override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSCTORDECREFERENCE_H_