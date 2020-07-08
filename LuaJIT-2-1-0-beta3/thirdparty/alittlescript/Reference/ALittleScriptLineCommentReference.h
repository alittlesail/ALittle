
#ifndef _ALITTLE_ALITTLESCRIPTLINECOMMENTREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTLINECOMMENTREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptLineCommentElement.h"

class ALittleScriptLineCommentReference : public ALittleScriptReferenceTemplate<ALittleScriptLineCommentElement>
{
public:
    ALittleScriptLineCommentReference(ABnfElementPtr element) : ALittleScriptReferenceTemplate<ALittleScriptLineCommentElement>(element) {}
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptLineCommentReference(element); }
    int QueryClassificationTag(bool& blur) override
    {
        blur = false;
        return ALittleScriptColorType::COMMENT;
    }

    bool CanGotoDefinition() override
    {
        return false;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTLINECOMMENTREFERENCE_H_