
#ifndef _ALITTLE_ALITTLESCRIPTCLASSDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassDecElement.h"

class ALittleScriptClassDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassDecElement>
{
private:
    std::string m_namespace_name;

public:
    ALittleScriptClassDecReference(ABnfElementPtr element);

    ABnfGuessError CheckError() override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSDECREFERENCE_H_