#ifndef _ALITTLE_ALITTLESCRIPTSTRUCTVARNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTSTRUCTVARNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptStructVarNameDecElement.h"

class ALittleScriptStructVarNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptStructVarNameDecElement>
{
public:
    ALittleScriptStructVarNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptStructVarNameDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptStructVarNameDecReference(element); }
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::VAR_NAME;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTSTRUCTVARNAMEDECREFERENCE_H_