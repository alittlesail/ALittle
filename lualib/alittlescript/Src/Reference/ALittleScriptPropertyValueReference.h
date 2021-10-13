
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueElement.h"

class ALittleScriptPropertyValueReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueElement>
{
public:
    ALittleScriptPropertyValueReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptPropertyValueReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEREFERENCE_H_