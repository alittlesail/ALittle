
#ifndef _ALITTLE_ALITTLESCRIPTSTRUCTDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTSTRUCTDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptStructDecElement.h"

class ALittleScriptStructDecReference : public ALittleScriptReferenceTemplate<ALittleScriptStructDecElement>
{
public:
    ALittleScriptStructDecReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptStructDecReference(element); }

private:
    std::string m_namespace_name;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTSTRUCTDECREFERENCE_H_