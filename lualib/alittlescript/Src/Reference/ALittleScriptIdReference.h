﻿#ifndef _ALITTLE_ALITTLESCRIPTIDREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTIDREFERENCE_H_

#include "ALittleScriptCustomTypeCommonReference.h"

#include "../Generate/ALittleScriptIdElement.h"

class ALittleScriptIdReference : public ALittleScriptReferenceTemplate<ALittleScriptIdElement>
{
public:
    ALittleScriptIdReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptIdElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptIdReference(element); }

    void QueryQuickInfo(std::string& info) override;

    ABnfElementPtr GotoDefinition() override;

    bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;

    bool PeekHighlightWord() override;

    void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTIDREFERENCE_H_