#ifndef _ALITTLE_ALITTLESCRIPTENUMVARNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTENUMVARNAMEDECREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptEnumVarNameDecElement.h"

class ALittleScriptEnumVarNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptEnumVarNameDecElement>
{
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::ALittleScriptVarName;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTENUMVARNAMEDECREFERENCE_H_