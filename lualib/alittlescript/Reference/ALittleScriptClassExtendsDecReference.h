
#ifndef _ALITTLE_ALITTLESCRIPTCLASSEXTENDSDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSEXTENDSDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassExtendsDecElement.h"

class ALittleScriptClassExtendsDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassExtendsDecElement>
{
private:
    std::string m_namespace_name;
    std::string m_key;

public:
    ALittleScriptClassExtendsDecReference(ABnfElementPtr p_element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptClassExtendsDecReference(element); }

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSEXTENDSDECREFERENCE_H_