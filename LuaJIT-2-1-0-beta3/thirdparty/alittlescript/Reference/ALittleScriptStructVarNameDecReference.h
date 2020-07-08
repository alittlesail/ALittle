#ifndef _ALITTLE_ALITTLESCRIPTSTRUCTVARNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTSTRUCTVARNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptStructVarNameDecElement.h"

class ALittleScriptStructVarNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptStructVarNameDecElement>
{
public:
    ALittleScriptStructVarNameDecReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptStructVarNameDecElement>(element) {}
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::ALittleScriptVarName;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTSTRUCTVARNAMEDECREFERENCE_H_