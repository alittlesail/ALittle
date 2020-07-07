
#ifndef _ALITTLE_ALITTLESCRIPTNUMBERREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTNUMBERREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptNumberElement.h"

class ALittleScriptNumberReference : public ALittleScriptReferenceTemplate<ALittleScriptNumberElement>
{
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        ALittleScriptColorType::ALittleScriptDefault;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTNUMBERREFERENCE_H_