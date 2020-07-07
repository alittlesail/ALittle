
#ifndef _ALITTLE_ALITTLESCRIPTLINECOMMENTREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTLINECOMMENTREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptLineCommentElement.h"

class ALittleScriptLineCommentReference : public ALittleScriptReferenceTemplate<ALittleScriptLineCommentElement>
{
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::ALittleScriptComment;
    }

    bool CanGotoDefinition() override
    {
        return false;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTLINECOMMENTREFERENCE_H_