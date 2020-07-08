
#ifndef _ALITTLE_ALITTLESCRIPTREFLECTVALUEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTREFLECTVALUEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptReflectValueElement.h"

class ALittleScriptReflectValueReference : public ALittleScriptReferenceTemplate<ALittleScriptReflectValueElement>
{
public:
    ALittleScriptReflectValueReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptReflectValueElement>(element) {}
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTREFLECTVALUEREFERENCE_H_