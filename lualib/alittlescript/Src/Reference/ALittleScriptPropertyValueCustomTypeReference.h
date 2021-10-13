﻿
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUECUSTOMTYPEREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUECUSTOMTYPEREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueCustomTypeElement.h"

class ALittleScriptMethodBodyDecElement;

class ALittleScriptPropertyValueCustomTypeReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueCustomTypeElement>
{
private:
    std::string m_namespace_name;
    std::string m_key;
    ABnfElementWeakPtr m_method_dec;
    std::weak_ptr<ALittleScriptMethodBodyDecElement> m_method_body_dec;

public:
    ALittleScriptPropertyValueCustomTypeReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptPropertyValueCustomTypeReference(element); }

    int QueryClassificationTag(bool& blur) override;

private:
    void ReloadInfo();

    // 计算命名域前缀
public:
    ABnfGuessError CalcNamespaceName(std::string& namespace_name) const;

private:
    void CalcResolve(std::vector<ABnfElementPtr>& result_list) const;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;

    bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;

    ABnfElementPtr GotoDefinition() override;

    bool PeekHighlightWord() override { return true; }

    void QueryHighlightWordTag(std::vector<ALanguageHighlightWordInfo>& list) override;

    void CollectHighlight(const ABnfGuessPtr& target_guess, const ABnfElementPtr& element, std::vector<ALanguageHighlightWordInfo>& list) const;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUECUSTOMTYPEREFERENCE_H_