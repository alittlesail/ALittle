
#ifndef _ALITTLE_ALITTLESCRIPTENUMDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTENUMDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptEnumDecElement.h"

class ALittleScriptEnumDecReference : public ALittleScriptReferenceTemplate<ALittleScriptEnumDecElement>
{
private:
    std::string m_namespace_name;

public:
    ALittleScriptEnumDecReference(ABnfElementPtr element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptEnumDecReference(element); }

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTENUMDECREFERENCE_H_