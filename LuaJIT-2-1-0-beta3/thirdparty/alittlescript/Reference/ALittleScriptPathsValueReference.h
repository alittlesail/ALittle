
#ifndef _ALITTLE_ALITTLESCRIPTPATHSVALUEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPATHSVALUEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPathsValueElement.h"

class ALittleScriptPathsValueReference : public ALittleScriptReferenceTemplate<ALittleScriptPathsValueElement>
{
public:
    ALittleScriptPathsValueReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptPathsValueElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptPathsValueReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTPATHSVALUEREFERENCE_H_