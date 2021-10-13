﻿#ifndef _ALITTLE_ALITTLESCRIPTUSINGDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTUSINGDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptUsingDecElement.h"

class ALittleScriptUsingDecReference : public ALittleScriptReferenceTemplate<ALittleScriptUsingDecElement>
{
private:
    std::string m_namespace_name;

public:
    ALittleScriptUsingDecReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptUsingDecReference(element); }

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTUSINGDECREFERENCE_H_