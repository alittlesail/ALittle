
#ifndef _ALITTLE_ALITTLESCRIPTGUESSPARAMTAIL_H_
#define _ALITTLE_ALITTLESCRIPTGUESSPARAMTAIL_H_

#include "ALittleScriptGuess.h"

class ALittleScriptGuessParamTail : public ALittleScriptGuess
{
public:
    ALittleScriptGuessParamTail(const std::string& p_value);

    bool NeedReplace() const override;
    ABnfGuessPtr ReplaceTemplate(ABnfFile* file, const std::unordered_map<std::string, ABnfGuessPtr>& fill_map) override;
    ABnfGuessPtr Clone() const override;
    bool IsChanged() const override { return false; }
};

#endif // _ALITTLE_ALITTLESCRIPTGUESSPARAMTAIL_H_
