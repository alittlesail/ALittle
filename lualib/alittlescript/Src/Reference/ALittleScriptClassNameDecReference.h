
#ifndef _ALITTLE_ALITTLESCRIPTCLASSNAMEDECREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTCLASSNAMEDECREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptClassNameDecElement.h"

class ALittleScriptClassNameDecReference : public ALittleScriptReferenceTemplate<ALittleScriptClassNameDecElement>
{
private:
    std::string m_namespace_name;
    std::string m_key;
public:
    ALittleScriptClassNameDecReference(const ABnfElementPtr& element);
    static ABnfReference* Create(const ABnfElementPtr& element) { return new ALittleScriptClassNameDecReference(element); }

    int QueryClassificationTag(bool& blur) override;

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

    ABnfGuessError CheckError() override;

    ABnfElementPtr GotoDefinition() override;

    // 输入智能补全
    bool QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list) override;
};

#endif // _ALITTLE_ALITTLESCRIPTCLASSNAMEDECREFERENCE_H_