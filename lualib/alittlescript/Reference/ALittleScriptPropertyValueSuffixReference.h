
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUESUFFIXREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUESUFFIXREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueSuffixElement.h"

class ALittleScriptPropertyValueSuffixReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueSuffixElement>
{
public:
    ALittleScriptPropertyValueSuffixReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueSuffixElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptPropertyValueSuffixReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUESUFFIXREFERENCE_H_