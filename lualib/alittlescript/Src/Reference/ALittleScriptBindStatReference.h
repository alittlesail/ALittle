
#ifndef _ALITTLE_ALITTLESCRIPTBINDSTATREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTBINDSTATREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptBindStatElement.h"

class ALittleScriptBindStatReference : public ALittleScriptReferenceTemplate<ALittleScriptBindStatElement>
{
public:
    ALittleScriptBindStatReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptBindStatElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptBindStatReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTBINDSTATREFERENCE_H_