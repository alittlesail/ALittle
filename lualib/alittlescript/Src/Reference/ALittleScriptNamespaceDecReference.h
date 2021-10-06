﻿
#ifndef _ALITTLE_ALITTLESCRIPTNAMESPACEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTNAMESPACEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptNamespaceDecElement.h"

class ALittleScriptNamespaceDecReference : public ALittleScriptReferenceTemplate<ALittleScriptNamespaceDecElement>
{
public:
    ALittleScriptNamespaceDecReference(const ABnfElementPtr& element) : ALittleScriptReferenceTemplate<ALittleScriptNamespaceDecElement>(element) {}
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptNamespaceDecReference(element); }

    ABnfGuessError CheckError() override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    int QueryClassificationTag(bool& blur) override;
};

#endif // _ALITTLE_ALITTLESCRIPTNAMESPACEDECREFERENCE_H_