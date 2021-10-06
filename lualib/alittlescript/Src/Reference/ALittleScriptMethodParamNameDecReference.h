
#ifndef _ALITTLE_ALITTLESCRIPTMETHODPARAMNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODPARAMNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodParamNameDecElement.h"

class ALittleScriptMethodParamNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodParamNameDecElement>
{
public:
    ALittleScriptMethodParamNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptMethodParamNameDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptMethodParamNameDecReference(element); }
    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODPARAMNAMEDECREFERENCE_H_