
#ifndef _ALITTLE_ALITTLESCRIPTCUSTOMTYPECOMMONREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCUSTOMTYPECOMMONREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptCoroutineStatElement.h"

class ALittleScriptClassDecElement;
class ALittleScriptTemplateDecElement;
class ALittleScriptCustomTypeElement;

class ALittleScriptCustomTypeCommonReference : public ALittleScriptReferenceTemplate<ABnfElement>
{
protected:
    std::string m_namespace_name;
    std::string m_key;
    std::weak_ptr<ALittleScriptClassDecElement> m_class_dec;
    std::weak_ptr<ALittleScriptTemplateDecElement> m_template_param_dec;
    std::weak_ptr<ALittleScriptCustomTypeElement> m_custom_type;

    ALittleScriptCustomTypeCommonReference(std::shared_ptr<ALittleScriptCustomTypeElement> custom_type, ABnfElementPtr element);

    std::shared_ptr<ALittleScriptClassDecElement> GetClassDec();

    // 获取函数模板
    std::shared_ptr<ALittleScriptTemplateDecElement> GetMethodTemplateDec();

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfElementPtr GotoDefinition() override;

    bool QueryCompletion(ABnfElementPtr select, std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTCUSTOMTYPECOMMONREFERENCE_H_