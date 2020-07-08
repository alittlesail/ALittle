
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDNAMEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDNAMEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueDotIdNameElement.h"

class ALittleScriptGuessClass;
class ALittleScriptMethodBodyDecElement;

class ALittleScriptPropertyValueDotIdNameReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueDotIdNameElement>
{
private:
    std::string m_namespace_name;
    std::string m_key;

    std::vector<ABnfElementWeakPtr> m_getter_list;
    std::vector<ABnfElementWeakPtr> m_setter_list;
    std::weak_ptr<ALittleScriptGuessClass> m_class_guess;

    ABnfElementWeakPtr m_method_dec;
    std::weak_ptr<ALittleScriptMethodBodyDecElement> m_method_body_dec;

public:
    ALittleScriptPropertyValueDotIdNameReference(ABnfElementPtr element);
    static ABnfReference* Create(ABnfElementPtr element) { return new ALittleScriptPropertyValueDotIdNameReference(element); }

private:
    void ReloadInfo();


    ABnfGuessError ReplaceTemplate(ABnfGuessPtr guess, ABnfGuessPtr& result);

    ABnfGuessError CalcResolve(std::vector<ABnfElementPtr>& result_list, ABnfGuessPtr& pre_type);

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError CheckError() override;

    bool QueryCompletion(std::vector<ALanguageCompletionInfo>& list) override;

    ABnfElementPtr GotoDefinition() override;

    bool PeekHighlightWord() override;

    void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) override;

    void CollectHighlight(ABnfGuessPtr target_guess, ABnfElementPtr element, std::vector<ALanguageHighlightWordInfo>& list);
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEDOTIDNAMEREFERENCE_H_