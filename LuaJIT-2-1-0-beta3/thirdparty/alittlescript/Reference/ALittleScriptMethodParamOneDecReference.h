
#ifndef _ALITTLE_ALITTLESCRIPTMETHODPARAMONEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTMETHODPARAMONEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptMethodParamOneDecElement.h"

class ALittleScriptMethodParamOneDecReference : public ALittleScriptReferenceTemplate<ALittleScriptMethodParamOneDecElement>
{
public:
    ALittleScriptMethodParamOneDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptMethodParamOneDecElement>(element) {}
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTMETHODPARAMONEDECREFERENCE_H_