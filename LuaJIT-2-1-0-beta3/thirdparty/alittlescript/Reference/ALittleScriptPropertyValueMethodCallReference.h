
#ifndef _ALITTLE_ALITTLESCRIPTPROPERTYVALUEMETHODCALLREFERENCE_H_
#define _ALITTLE_ALITTLESCRIPTPROPERTYVALUEMETHODCALLREFERENCE_H_

#include "ALittleScriptReferenceTemplate.h"

#include "../Generate/ALittleScriptPropertyValueMethodCallElement.h"
#include "../Guess/ALittleScriptGuessFunctor.h"

#include <unordered_map>

class ALittleScriptPropertyValueMethodCallReference : public ALittleScriptReferenceTemplate<ALittleScriptPropertyValueMethodCallElement>
{
    bool MultiGuessTypes() override
    {
        return true;
    }

public:
    ABnfGuessError GuessPreType(ABnfGuessPtr& guess);

    ABnfGuessError GuessTypes(std::vector<ABnfGuessPtr>& guess_list) override;

private:
    ABnfGuessError AnalysisTemplate(std::unordered_map<std::string, ABnfGuessPtr>& fill_map, ABnfGuessPtr left_guess, ABnfElementPtr right_src, ABnfGuessPtr right_guess, bool assign_or_call);

    ABnfGuessError CheckTemplateMap(std::unordered_map<std::string, std::shared_ptr<ALittleScriptGuessTemplate>>& src_map, std::unordered_map<std::string, ABnfGuessPtr>& fill_map, std::shared_ptr<ALittleScriptGuessFunctor>& guess);

public:
    ABnfGuessError GenerateTemplateParamList(std::vector<ABnfGuessPtr>& param_list);

    ABnfGuessError CheckError() override;
};

#endif // _ALITTLE_ALITTLESCRIPTPROPERTYVALUEMETHODCALLREFERENCE_H_