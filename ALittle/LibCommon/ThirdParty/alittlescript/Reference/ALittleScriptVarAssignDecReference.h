#ifndef _ALITTLE_ALITTLESCRIPTVARASSIGNDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTVARASSIGNDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptVarAssignDecElement.h"

class ALittleScriptClassDecElement;
class ALittleScriptTemplateDecElement;

class ALittleScriptVarAssignDecReference : public ALittleScriptReferenceTemplate<ALittleScriptVarAssignDecElement>
{
private:
    std::string m_namespace_name;
    std::weak_ptr<ALittleScriptClassDecElement> m_class_dec;
    std::weak_ptr<ALittleScriptTemplateDecElement> m_template_param_dec;

public:
    ALittleScriptVarAssignDecReference(ABnfElementPtr element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptVarAssignDecReference(element); }

    std::shared_ptr<ALittleScriptClassDecElement> GetClassDec();

    std::shared_ptr<ALittleScriptTemplateDecElement> GetTemplateDec();

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTVARASSIGNDECREFERENCE_H_