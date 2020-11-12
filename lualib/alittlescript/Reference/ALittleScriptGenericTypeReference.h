#ifndef _ALITTLE_ALITTLESCRIPTGENERICTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTGENERICTYPEREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptGenericTypeElement.h"

class ALittleScriptGenericTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptGenericTypeElement>
{
public:
    ALittleScriptGenericTypeReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptGenericTypeElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptGenericTypeReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTGENERICTYPEREFERENCE_H_