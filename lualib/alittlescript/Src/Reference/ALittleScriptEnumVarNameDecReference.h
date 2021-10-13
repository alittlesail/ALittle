#ifndef _ALITTLE_ALITTLESCRIPTENUMVARNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTENUMVARNAMEDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptEnumVarNameDecElement.h"

class ALittleScriptEnumVarNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptEnumVarNameDecElement>
{
public:
    ALittleScriptEnumVarNameDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptEnumVarNameDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptEnumVarNameDecReference(element); }
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::VAR_NAME;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTENUMVARNAMEDECREFERENCE_H_