
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEBRACKETVALUEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEBRACKETVALUEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueBracketValueElement.h"

class ALittleScriptPropertyValueBracketValueReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueBracketValueElement>
{
public:
    ALittleScriptPropertyValueBracketValueReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueBracketValueElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptPropertyValueBracketValueReference(element); }
    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEBRACKETVALUEREFERENCE_H_