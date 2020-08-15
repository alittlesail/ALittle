
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEMETHODTEMPLATEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEMETHODTEMPLATEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueMethodTemplateElement.h"

class ALittleScriptPropertyValueMethodTemplateReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueMethodTemplateElement>
{
public:
    ALittleScriptPropertyValueMethodTemplateReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptPropertyValueMethodTemplateElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptPropertyValueMethodTemplateReference(element); }
    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEMETHODTEMPLATEREFERENCE_H_