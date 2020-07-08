
#ifndef _ALITTLE_ALITTLESCRIPTCLASSVARDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSVARDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassVarDecElement.h"

class ALittleScriptClassVarDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassVarDecElement>
{
public:
    ALittleScriptClassVarDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptClassVarDecElement>(element) {}
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSVARDECREFERENCE_H_