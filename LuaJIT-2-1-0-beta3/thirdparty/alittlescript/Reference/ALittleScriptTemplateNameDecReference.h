#ifndef _ALITTLE_ALITTLESCRIPTTEMPLATENAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTTEMPLATENAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptTemplateNameDecElement.h"

class ALittleScriptTemplateNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptTemplateNameDecElement>
{
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::ALittleScriptCustomName;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTTEMPLATENAMEDECREFERENCE_H_