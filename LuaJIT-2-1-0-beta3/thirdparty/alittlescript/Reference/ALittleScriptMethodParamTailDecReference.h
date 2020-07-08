
#ifndef _ALITTLE_ALITTLESCRIPTMETHODPARAMTAILDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODPARAMTAILDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodParamTailDecElement.h"

class ALittleScriptMethodParamTailDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodParamTailDecElement>
{
public:
    ALittleScriptMethodParamTailDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptMethodParamTailDecElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptMethodParamTailDecReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODPARAMTAILDECREFERENCE_H_