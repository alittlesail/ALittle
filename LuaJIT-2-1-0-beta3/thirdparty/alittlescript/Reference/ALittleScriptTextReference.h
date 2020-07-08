#ifndef _ALITTLE_ALITTLESCRIPTTEXTREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTTEXTREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptTextElement.h"

class ALittleScriptTextReference : public ALittleScriptReferenceTemplate<ALittleScriptTextElement>
{
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::ALittleScriptText;
    }

    bool CanGotoDefinition() override
    {
        return false;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTTEXTREFERENCE_H_