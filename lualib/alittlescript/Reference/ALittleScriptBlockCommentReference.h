
#ifndef _ALITTLE_ALITTLESCRIPTBLOCKCOMMENTREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTBLOCKCOMMENTREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptBlockCommentElement.h"

class ALittleScriptBlockCommentReference : public ALittleScriptReferenceTemplate<ALittleScriptBlockCommentElement>
{
public:
    ALittleScriptBlockCommentReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptBlockCommentElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptBlockCommentReference(element); }
    int QueryClassificationTag(bool& blur) override
    {
        const auto element = m_element.lock();
        if (element == nullptr) return 0;
        blur = false;
        return ALittleScriptColorType::COMMENT;
    }

    bool CanGotoDefinition() override
    {
        return false;
    }
};

#endif // _ALITTLE_ALITTLESCRIPTBLOCKCOMMENTREFERENCE_H_
