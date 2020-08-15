﻿
#ifndef _ALITTLE_ALITTLESCRIPTNAMESPACENAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTNAMESPACENAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptNamespaceNameDecElement.h"

class ALittleScriptNamespaceNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptNamespaceNameDecElement>
{
private:
    std::string m_key;

public:
    ALittleScriptNamespaceNameDecReference(ABnfElementPtr element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptNamespaceNameDecReference(element); }

    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;

    ABnfElementPtr GotoDefinition() override;

    bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTNAMESPACENAMEDECREFERENCE_H_