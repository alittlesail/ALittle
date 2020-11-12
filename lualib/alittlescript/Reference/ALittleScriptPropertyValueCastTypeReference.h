
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUECASTTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUECASTTYPEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueCastTypeElement.h"

class ALittleScriptPropertyValueCastTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueCastTypeElement>
{
public:
    ALittleScriptPropertyValueCastTypeReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueCastTypeElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptPropertyValueCastTypeReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUECASTTYPEREFERENCE_H_